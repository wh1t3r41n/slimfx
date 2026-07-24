// sfx_window.c -- GLFW-backed window + our own GL 3.3 Core loader
#include "sfx_window.h"
#include "internal/sfx_gl.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct sfx_window {
    GLFWwindow*    handle;
    int            width;
    int            height;
    int            should_close;
    sfx_input_state_t input;
    void*          user;

    double         fps_ema;
    double         last_time;
};

static void sfx__glfw_error_cb(int code, const char* description) {
    fprintf(stderr, "[slimfx] GLFW error %d: %s\n", code, description);
}

static void sfx__key_cb(GLFWwindow* w, int key, int scancode, int action, int mods) {
    (void)scancode; (void)mods;
    sfx_window_t* s = (sfx_window_t*)glfwGetWindowUserPointer(w);
    if (!s) return;
    if (key < 0 || key >= (int)sizeof(s->input.keys)) return;
    if (action == GLFW_PRESS)   s->input.keys[key] = 1;
    if (action == GLFW_RELEASE) s->input.keys[key] = 0;
}

static void sfx__mouse_btn_cb(GLFWwindow* w, int button, int action, int mods) {
    (void)mods;
    sfx_window_t* s = (sfx_window_t*)glfwGetWindowUserPointer(w);
    if (!s) return;
    if (button < 0 || button >= (int)sizeof(s->input.mouse_buttons)) return;
    if (action == GLFW_PRESS)   s->input.mouse_buttons[button] = 1;
    if (action == GLFW_RELEASE) s->input.mouse_buttons[button] = 0;
}

static void sfx__cursor_pos_cb(GLFWwindow* w, double x, double y) {
    sfx_window_t* s = (sfx_window_t*)glfwGetWindowUserPointer(w);
    if (!s) return;
    s->input.mouse_x = x;
    s->input.mouse_y = y;
}

static void sfx__scroll_cb(GLFWwindow* w, double sx, double sy) {
    sfx_window_t* s = (sfx_window_t*)glfwGetWindowUserPointer(w);
    if (!s) return;
    s->input.scroll_x = sx;
    s->input.scroll_y = sy;
}

static void sfx__size_cb(GLFWwindow* w, int width, int height) {
    sfx_window_t* s = (sfx_window_t*)glfwGetWindowUserPointer(w);
    if (!s) return;
    s->width = width;
    s->height = height;
    glViewport(0, 0, width, height);
}

static int sfx__glfw_inited = 0;
static int sfx__glfw_refcount = 0;

static sfx_result_t sfx__ensure_glfw(void) {
    if (sfx__glfw_inited) { sfx__glfw_refcount++; return SFX_OK; }
    glfwSetErrorCallback(sfx__glfw_error_cb);
    if (!glfwInit()) return SFX_ERR_BACKEND;
    sfx__glfw_inited = 1;
    sfx__glfw_refcount = 1;
    return SFX_OK;
}

static void sfx__release_glfw(void) {
    if (!sfx__glfw_inited) return;
    if (--sfx__glfw_refcount > 0) return;
    glfwTerminate();
    sfx__glfw_inited = 0;
}

sfx_version_t sfx_get_version(void) {
    sfx_version_t v = { 0, 1, 0 };
    return v;
}

sfx_result_t sfx_window_create(const sfx_window_desc_t* desc, sfx_window_t** out) {
    if (!desc || !out) return SFX_ERR_INVALID_ARG;

    sfx_result_t r = sfx__ensure_glfw();
    if (r != SFX_OK) return r;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, desc->resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, desc->samples > 0 ? desc->samples : 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    GLFWwindow* h = glfwCreateWindow(
        desc->width  > 0 ? desc->width  : 1280,
        desc->height > 0 ? desc->height : 720,
        desc->title  ? desc->title : "slimfx",
        NULL, NULL
    );
    if (!h) {
        sfx__release_glfw();
        return SFX_ERR_BACKEND;
    }

    sfx_window_t* w = (sfx_window_t*)calloc(1, sizeof(*w));
    if (!w) {
        glfwDestroyWindow(h);
        sfx__release_glfw();
        return SFX_ERR_OUT_OF_MEMORY;
    }
    w->handle   = h;
    w->width    = desc->width  > 0 ? desc->width  : 1280;
    w->height   = desc->height > 0 ? desc->height : 720;
    w->last_time = glfwGetTime();

    glfwSetWindowUserPointer(h, w);
    glfwMakeContextCurrent(h);
    glfwSwapInterval(desc->vsync ? 1 : 0);

    // Our own GL 3.3 Core loader.
    if (!sfx_gl_load((GLADloadfunc)glfwGetProcAddress)) {
        glfwDestroyWindow(h);
        free(w);
        sfx__release_glfw();
        return SFX_ERR_BACKEND;
    }

    fprintf(stderr, "[slimfx] OpenGL %s | %s\n",
            (const char*)glGetString(SFX_GL_VERSION),
            (const char*)glGetString(SFX_GL_RENDERER));

    glfwSetKeyCallback(h, sfx__key_cb);
    glfwSetMouseButtonCallback(h, sfx__mouse_btn_cb);
    glfwSetCursorPosCallback(h, sfx__cursor_pos_cb);
    glfwSetScrollCallback(h, sfx__scroll_cb);
    glfwSetFramebufferSizeCallback(h, sfx__size_cb);

    glViewport(0, 0, w->width, w->height);
    glEnable(SFX_GL_DEPTH_TEST);
    glEnable(SFX_GL_CULL_FACE);
    glCullFace(SFX_GL_BACK);
    glFrontFace(SFX_GL_CCW);

    *out = w;
    return SFX_OK;
}

void sfx_window_destroy(sfx_window_t* w) {
    if (!w) return;
    if (w->handle) glfwDestroyWindow(w->handle);
    free(w);
    sfx__release_glfw();
}

int sfx_window_should_close(const sfx_window_t* w) {
    return w ? (w->should_close || glfwWindowShouldClose(w->handle)) : 1;
}

void sfx_window_set_should_close(sfx_window_t* w, int value) {
    if (!w) return;
    w->should_close = value ? 1 : 0;
    glfwSetWindowShouldClose(w->handle, value ? GLFW_TRUE : GLFW_FALSE);
}

void sfx_window_poll(sfx_window_t* w) {
    if (!w) return;
    glfwPollEvents();
}

void sfx_window_swap_buffers(sfx_window_t* w) {
    if (!w) return;
    glfwSwapBuffers(w->handle);

    double now = glfwGetTime();
    double dt = now - w->last_time;
    w->last_time = now;
    if (dt > 0.0) {
        double inst = 1.0 / dt;
        if (w->fps_ema <= 0.0) w->fps_ema = inst;
        else w->fps_ema = w->fps_ema * 0.9 + inst * 0.1;
    }
}

void sfx_window_get_size(const sfx_window_t* w, int* width, int* height) {
    if (!w) return;
    if (width)  *width  = w->width;
    if (height) *height = w->height;
}

float sfx_window_get_time(void) {
    return (float)glfwGetTime();
}

double sfx_window_get_fps(const sfx_window_t* w) {
    return w ? w->fps_ema : 0.0;
}

const sfx_input_state_t* sfx_window_get_input(const sfx_window_t* w) {
    return w ? &w->input : NULL;
}

void sfx_window_set_user_data(sfx_window_t* w, void* user) {
    if (w) w->user = user;
}

void* sfx_window_get_user_data(const sfx_window_t* w) {
    return w ? w->user : NULL;
}