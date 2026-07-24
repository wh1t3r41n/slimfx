// sfx_pipeline.c -- GL program + VAO + fixed-function state
#include "sfx_gfx.h"
#include "internal/sfx_gl.h"
#include "sfx_shader.h"   // internal accessors

#include <stdlib.h>
#include <string.h>

// Forward decls of internal accessors
GLenum sfx__shader_stage(const sfx_shader_t* s);
GLuint sfx__shader_id   (const sfx_shader_t* s);

#define MAX_ATTRS 16

struct sfx_pipeline {
    GLuint program;
    GLuint vao;
    size_t vertex_stride;
    int    has_attr[MAX_ATTRS];
    int    attr_count;
    int    depth_test, depth_write, cull_back, blend;
};

static GLint sfx__size_of(sfx_vertex_format_t f) {
    switch (f) {
        case SFX_FMT_FLOAT:       return 1;
        case SFX_FMT_FLOAT2:      return 2;
        case SFX_FMT_FLOAT3:      return 3;
        case SFX_FMT_FLOAT4:      return 4;
        case SFX_FMT_BYTE4_NORM:  return 4;
    }
    return 0;
}

static GLenum sfx__gl_type_of(sfx_vertex_format_t f) {
    switch (f) {
        case SFX_FMT_FLOAT:       return SFX_GL_FLOAT;
        case SFX_FMT_FLOAT2:      return SFX_GL_FLOAT;
        case SFX_FMT_FLOAT3:      return SFX_GL_FLOAT;
        case SFX_FMT_FLOAT4:      return SFX_GL_FLOAT;
        case SFX_FMT_BYTE4_NORM:  return SFX_GL_UNSIGNED_BYTE;
    }
    return SFX_GL_FLOAT;
}

static GLboolean sfx__gl_norm_of(sfx_vertex_format_t f) {
    return f == SFX_FMT_BYTE4_NORM ? SFX_GL_TRUE : SFX_GL_FALSE;
}

static sfx_result_t sfx__link(GLuint vs, GLuint fs, GLuint* out_prog) {
    GLuint p = glCreateProgram();
    if (vs) glAttachShader(p, vs);
    if (fs) glAttachShader(p, fs);
    glLinkProgram(p);
    GLint ok = 0;
    glGetProgramiv(p, SFX_GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        GLsizei n = 0;
        glGetProgramInfoLog(p, sizeof(log), &n, log);
        fprintf(stderr, "[slimfx] program link error: %s\n", log);
        glDeleteProgram(p);
        return SFX_ERR_BACKEND;
    }
    *out_prog = p;
    return SFX_OK;
}

sfx_result_t sfx_pipeline_create(const sfx_pipeline_desc_t* desc, sfx_pipeline_t** out) {
    if (!desc || !desc->vs || !desc->fs || !out) return SFX_ERR_INVALID_ARG;
    sfx_pipeline_t* p = (sfx_pipeline_t*)calloc(1, sizeof(*p));
    if (!p) return SFX_ERR_OUT_OF_MEMORY;
    p->depth_test  = desc->depth_test  ? 1 : 0;
    p->depth_write = desc->depth_write ? 1 : 0;
    p->cull_back   = desc->cull_back   ? 1 : 0;
    p->blend       = desc->blend       ? 1 : 0;
    p->vertex_stride = desc->vertex_stride;

    GLuint vs = sfx__shader_id(desc->vs);
    GLuint fs = sfx__shader_id(desc->fs);
    sfx_result_t r = sfx__link(vs, fs, &p->program);
    if (r != SFX_OK) { free(p); return r; }

    glGenVertexArrays(1, &p->vao);
    glBindVertexArray(p->vao);

    // Set up vertex attribute pointers based on location query.
    int location = 0;
    for (int i = 0; i < MAX_ATTRS; ++i) {
        const sfx_vertex_attr_t* a = &desc->attrs[i];
        if (!a->name) break;
        GLint loc = glGetAttribLocation(p->program, a->name);
        if (loc < 0) {
            // attribute not used by shader -- skip silently
            continue;
        }
        glEnableVertexAttribArray((GLuint)loc);
        glVertexAttribPointer((GLuint)loc, sfx__size_of(a->format),
                              sfx__gl_type_of(a->format),
                              sfx__gl_norm_of(a->format),
                              (GLsizei)desc->vertex_stride,
                              (const void*)a->offset);
        p->has_attr[loc] = 1;
    }

    glBindVertexArray(0);
    p->attr_count = MAX_ATTRS;
    *out = p;
    return SFX_OK;
}

void sfx_pipeline_destroy(sfx_pipeline_t* p) {
    if (!p) return;
    if (p->program) glDeleteProgram(p->program);
    if (p->vao)     glDeleteVertexArrays(1, &p->vao);
    free(p);
}

// Internal
GLuint sfx__pipeline_program(const sfx_pipeline_t* p) { return p ? p->program : 0; }
GLuint sfx__pipeline_vao    (const sfx_pipeline_t* p) { return p ? p->vao     : 0; }
int    sfx__pipeline_state  (const sfx_pipeline_t* p, int* dt, int* dw, int* cb, int* bl) {
    if (!p) return 0;
    if (dt) *dt = p->depth_test;
    if (dw) *dw = p->depth_write;
    if (cb) *cb = p->cull_back;
    if (bl) *bl = p->blend;
    return 1;
}