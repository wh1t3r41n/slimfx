// sfx_texture.c
#include "sfx_gfx.h"
#include "internal/sfx_gl.h"

#include <stdlib.h>

struct sfx_texture {
    GLuint id;
    int    w, h;
    GLenum fmt;
    GLenum internal;
    GLenum type;
};

static GLenum sfx__translate_fmt(sfx_texture_format_t f, GLenum* internal, GLenum* type) {
    switch (f) {
        case SFX_FMT_RGBA8:  *internal = SFX_GL_RGBA;        *type = SFX_GL_UNSIGNED_BYTE; return SFX_GL_RGBA;
        case SFX_FMT_RGB8:   *internal = SFX_GL_RGB;         *type = SFX_GL_UNSIGNED_BYTE; return SFX_GL_RGB;
        case SFX_FMT_R8:     *internal = SFX_GL_RED;         *type = SFX_GL_UNSIGNED_BYTE; return SFX_GL_RED;
        case SFX_FMT_RG8:    *internal = SFX_GL_RG;          *type = SFX_GL_UNSIGNED_BYTE; return SFX_GL_RG;
        case SFX_FMT_DEPTH24:*internal = SFX_GL_DEPTH_COMPONENT24; *type = SFX_GL_UNSIGNED_INT; return SFX_GL_DEPTH_COMPONENT;
    }
    *internal = SFX_GL_RGBA; *type = SFX_GL_UNSIGNED_BYTE;
    return SFX_GL_RGBA;
}

static GLenum sfx__translate_filter(sfx_texture_filter_t f) {
    switch (f) {
        case SFX_FILTER_NEAREST:        return SFX_GL_NEAREST;
        case SFX_FILTER_LINEAR:         return SFX_GL_LINEAR;
        case SFX_FILTER_LINEAR_MIPMAP:  return SFX_GL_LINEAR_MIPMAP_LINEAR;
    }
    return SFX_GL_LINEAR;
}

static GLenum sfx__translate_wrap(sfx_texture_wrap_t w) {
    return w == SFX_WRAP_CLAMP ? SFX_GL_CLAMP_TO_EDGE : SFX_GL_REPEAT;
}

sfx_result_t sfx_texture_create_2d(int w, int h, sfx_texture_format_t fmt,
                                   const void* pixels,
                                   sfx_texture_filter_t filter,
                                   sfx_texture_wrap_t   wrap,
                                   sfx_texture_t** out) {
    if (!out || w <= 0 || h <= 0) return SFX_ERR_INVALID_ARG;
    sfx_texture_t* t = (sfx_texture_t*)calloc(1, sizeof(*t));
    if (!t) return SFX_ERR_OUT_OF_MEMORY;
    t->w = w; t->h = h;
    t->fmt = sfx__translate_fmt(fmt, &t->internal, &t->type);

    glGenTextures(1, &t->id);
    glBindTexture(SFX_GL_TEXTURE_2D, t->id);
    glTexImage2D(SFX_GL_TEXTURE_2D, 0, (GLint)t->internal, w, h, 0, t->fmt, t->type, pixels);
    glTexParameteri(SFX_GL_TEXTURE_2D, SFX_GL_TEXTURE_MIN_FILTER, (GLint)sfx__translate_filter(filter));
    glTexParameteri(SFX_GL_TEXTURE_2D, SFX_GL_TEXTURE_MAG_FILTER, (GLint)sfx__translate_filter(filter));
    glTexParameteri(SFX_GL_TEXTURE_2D, SFX_GL_TEXTURE_WRAP_S,     (GLint)sfx__translate_wrap(wrap));
    glTexParameteri(SFX_GL_TEXTURE_2D, SFX_GL_TEXTURE_WRAP_T,     (GLint)sfx__translate_wrap(wrap));
    if (filter == SFX_FILTER_LINEAR_MIPMAP) glGenerateMipmap(SFX_GL_TEXTURE_2D);
    glBindTexture(SFX_GL_TEXTURE_2D, 0);
    *out = t;
    return SFX_OK;
}

void sfx_texture_destroy(sfx_texture_t* t) {
    if (!t) return;
    if (t->id) glDeleteTextures(1, &t->id);
    free(t);
}

int sfx_texture_width (const sfx_texture_t* t) { return t ? t->w : 0; }
int sfx_texture_height(const sfx_texture_t* t) { return t ? t->h : 0; }

// Internal
GLuint sfx__texture_id(const sfx_texture_t* t) { return t ? t->id : 0; }