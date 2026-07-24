// sfx_buffer.c -- GL 3.3 Core buffer object wrapper
#include "sfx_gfx.h"
#include "internal/sfx_gl.h"

#include <stdlib.h>
#include <string.h>

struct sfx_buffer {
    GLuint  id;
    GLenum  target;  // GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
    GLenum  usage;   // GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW
    size_t  size;
};

static GLenum sfx__translate_usage(sfx_buffer_usage_t u) {
    switch (u) {
        case SFX_USAGE_STATIC:  return SFX_GL_STATIC_DRAW;
        case SFX_USAGE_DYNAMIC: return SFX_GL_DYNAMIC_DRAW;
        case SFX_USAGE_STREAM:  return SFX_GL_STREAM_DRAW;
    }
    return SFX_GL_STATIC_DRAW;
}

sfx_result_t sfx_buffer_create(sfx_buffer_usage_t usage, size_t size,
                               const void* data, sfx_buffer_t** out) {
    if (!out || size == 0) return SFX_ERR_INVALID_ARG;
    sfx_buffer_t* b = (sfx_buffer_t*)calloc(1, sizeof(*b));
    if (!b) return SFX_ERR_OUT_OF_MEMORY;
    b->target = SFX_GL_ARRAY_BUFFER;
    b->usage  = sfx__translate_usage(usage);
    b->size   = size;
    glGenBuffers(1, &b->id);
    glBindBuffer(b->target, b->id);
    glBufferData(b->target, (GLsizeiptr)size, data, b->usage);
    glBindBuffer(b->target, 0);
    *out = b;
    return SFX_OK;
}

void sfx_buffer_destroy(sfx_buffer_t* b) {
    if (!b) return;
    if (b->id) glDeleteBuffers(1, &b->id);
    free(b);
}

size_t sfx_buffer_size(const sfx_buffer_t* b) { return b ? b->size : 0; }

sfx_result_t sfx_buffer_set_data(sfx_buffer_t* b, size_t offset, size_t size, const void* data) {
    if (!b || !data || offset + size > b->size) return SFX_ERR_INVALID_ARG;
    glBindBuffer(b->target, b->id);
    glBufferSubData(b->target, (GLintptr)offset, (GLsizeiptr)size, data);
    glBindBuffer(b->target, 0);
    return SFX_OK;
}

// Internal: target/handle accessors (used by sfx_pass)
GLenum       sfx__buffer_target(const sfx_buffer_t* b) { return b ? b->target : 0; }
GLuint       sfx__buffer_id    (const sfx_buffer_t* b) { return b ? b->id     : 0; }
void         sfx__buffer_set_target(sfx_buffer_t* b, GLenum target) { if (b) b->target = target; }