// sfx_gl_api.c -- public minimal GL helpers
#include "sfx_gl_api.h"
#include "internal/sfx_gl.h"

void sfx_gl_clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(SFX_GL_COLOR_BUFFER_BIT | SFX_GL_DEPTH_BUFFER_BIT);
}

void sfx_gl_set_viewport(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}

const char* sfx_gl_version_string(void) {
    return (const char*)glGetString(SFX_GL_VERSION);
}

const char* sfx_gl_renderer_string(void) {
    return (const char*)glGetString(SFX_GL_RENDERER);
}