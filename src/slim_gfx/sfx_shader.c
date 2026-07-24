// sfx_shader.c -- GLSL 330 shader compile/link
#include "sfx_gfx.h"
#include "internal/sfx_gl.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct sfx_shader {
    GLenum stage;
    GLuint id;
    char  log[1024];
    int   has_log;
};

sfx_result_t sfx_shader_create(sfx_shader_stage_t stage, const char* source, sfx_shader_t** out) {
    if (!out || !source) return SFX_ERR_INVALID_ARG;
    sfx_shader_t* s = (sfx_shader_t*)calloc(1, sizeof(*s));
    if (!s) return SFX_ERR_OUT_OF_MEMORY;

    s->stage = (stage == SFX_STAGE_VERTEX) ? SFX_GL_VERTEX_SHADER : SFX_GL_FRAGMENT_SHADER;
    s->id    = glCreateShader(s->stage);
    glShaderSource(s->id, 1, &source, NULL);
    glCompileShader(s->id);

    GLint ok = 0;
    glGetShaderiv(s->id, SFX_GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(s->id, SFX_GL_INFO_LOG_LENGTH, &len);
        if (len > 0 && len < (int)sizeof(s->log)) {
            glGetShaderInfoLog(s->id, (GLsizei)sizeof(s->log), NULL, s->log);
            s->has_log = 1;
        }
        glDeleteShader(s->id);
        free(s);
        return SFX_ERR_BACKEND;
    }
    *out = s;
    return SFX_OK;
}

void sfx_shader_destroy(sfx_shader_t* s) {
    if (!s) return;
    if (s->id) glDeleteShader(s->id);
    free(s);
}

sfx_result_t sfx_shader_get_log(const sfx_shader_t* s, char* out, int out_size) {
    if (!s || !out || out_size <= 0) return SFX_ERR_INVALID_ARG;
    if (s->has_log) {
        strncpy(out, s->log, (size_t)out_size - 1);
        out[out_size - 1] = 0;
    } else {
        out[0] = 0;
    }
    return SFX_OK;
}

// Internal accessors
GLenum sfx__shader_stage(const sfx_shader_t* s) { return s ? s->stage : 0; }
GLuint sfx__shader_id   (const sfx_shader_t* s) { return s ? s->id    : 0; }