// sfx_gfx.h -- Vulkan-simplified graphics on GL 3.3 Core.
// Designed to be small, explicit, and easy to write by hand.
#ifndef SFX_GFX_H
#define SFX_GFX_H

#include "sfx_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---- Buffer (one type, Vulkan-style usage flag) ---------------------------
typedef struct sfx_buffer sfx_buffer_t;

typedef enum sfx_buffer_usage {
    SFX_USAGE_STATIC  = 0,  // uploaded once, drawn many
    SFX_USAGE_DYNAMIC = 1,  // updated occasionally
    SFX_USAGE_STREAM  = 2,  // updated every frame
} sfx_buffer_usage_t;

SFX_API sfx_result_t sfx_buffer_create(sfx_buffer_usage_t usage, size_t size,
                                       const void* data, sfx_buffer_t** out);
SFX_API void          sfx_buffer_destroy(sfx_buffer_t* b);
SFX_API size_t        sfx_buffer_size(const sfx_buffer_t* b);
SFX_API sfx_result_t  sfx_buffer_set_data(sfx_buffer_t* b, size_t offset,
                                          size_t size, const void* data);

// ---- Texture ---------------------------------------------------------------
typedef struct sfx_texture sfx_texture_t;

typedef enum sfx_texture_format {
    SFX_FMT_RGBA8 = 0,
    SFX_FMT_RGB8,
    SFX_FMT_R8,
    SFX_FMT_RG8,
    SFX_FMT_DEPTH24,
} sfx_texture_format_t;

typedef enum sfx_texture_filter {
    SFX_FILTER_NEAREST = 0,
    SFX_FILTER_LINEAR,
    SFX_FILTER_LINEAR_MIPMAP,
} sfx_texture_filter_t;

typedef enum sfx_texture_wrap {
    SFX_WRAP_REPEAT = 0,
    SFX_WRAP_CLAMP,
} sfx_texture_wrap_t;

SFX_API sfx_result_t sfx_texture_create_2d(int w, int h, sfx_texture_format_t fmt,
                                           const void* pixels,
                                           sfx_texture_filter_t filter,
                                           sfx_texture_wrap_t   wrap,
                                           sfx_texture_t** out);
SFX_API void         sfx_texture_destroy(sfx_texture_t* t);
SFX_API int          sfx_texture_width(const sfx_texture_t* t);
SFX_API int          sfx_texture_height(const sfx_texture_t* t);

// ---- Shader (raw GLSL 330 for now; SFX-lang compiler lands in step B) -----
typedef struct sfx_shader sfx_shader_t;

typedef enum sfx_shader_stage {
    SFX_STAGE_VERTEX   = 0,
    SFX_STAGE_FRAGMENT = 1,
} sfx_shader_stage_t;

SFX_API sfx_result_t sfx_shader_create(sfx_shader_stage_t stage, const char* source, sfx_shader_t** out);
SFX_API void         sfx_shader_destroy(sfx_shader_t* s);
SFX_API sfx_result_t sfx_shader_get_log(const sfx_shader_t* s, char* out, int out_size);  // compile log

// ---- Pipeline --------------------------------------------------------------
typedef struct sfx_pipeline sfx_pipeline_t;

typedef enum sfx_vertex_format {
    SFX_FMT_FLOAT = 0,
    SFX_FMT_FLOAT2,
    SFX_FMT_FLOAT3,
    SFX_FMT_FLOAT4,
    SFX_FMT_BYTE4_NORM,   // 4 bytes, normalized [0..1]
} sfx_vertex_format_t;

// Describes one vertex attribute. Multiple attributes in order form the layout.
typedef struct sfx_vertex_attr {
    const char*        name;     // used for binding (location = ?)
    sfx_vertex_format_t format;
    size_t             offset;   // bytes from start of vertex
} sfx_vertex_attr_t;

typedef struct sfx_pipeline_desc {
    sfx_shader_t*        vs;
    sfx_shader_t*        fs;
    const sfx_vertex_attr_t* attrs;  // array, NULL-terminated (last entry has name==NULL)
    size_t               vertex_stride;
    int                  depth_test;     // 0/1
    int                  depth_write;    // 0/1
    int                  cull_back;      // 0/1
    int                  blend;          // 0/1 (alpha blend)
} sfx_pipeline_desc_t;

SFX_API sfx_result_t sfx_pipeline_create(const sfx_pipeline_desc_t* desc, sfx_pipeline_t** out);
SFX_API void         sfx_pipeline_destroy(sfx_pipeline_t* p);

// ---- Pass (encoder) --------------------------------------------------------
typedef struct sfx_pass sfx_pass_t;

typedef struct sfx_pass_desc {
    float clear_r, clear_g, clear_b, clear_a;
    int   clear;       // 0 = no clear
} sfx_pass_desc_t;

SFX_API sfx_pass_t*  sfx_pass_begin(sfx_pass_desc_t* desc);
SFX_API void         sfx_pass_bind_pipeline(sfx_pass_t* p, sfx_pipeline_t* pl);
SFX_API void         sfx_pass_bind_vertex_buffer(sfx_pass_t* p, sfx_buffer_t* vbo, size_t offset);
SFX_API void         sfx_pass_bind_index_buffer(sfx_pass_t* p, sfx_buffer_t* ibo, int index32);
SFX_API void         sfx_pass_bind_texture(sfx_pass_t* p, sfx_texture_t* tex, int slot);
SFX_API void         sfx_pass_set_uniform_float(sfx_pass_t* p, const char* name, float v);
SFX_API void         sfx_pass_set_uniform_vec2 (sfx_pass_t* p, const char* name, float x, float y);
SFX_API void         sfx_pass_set_uniform_vec3 (sfx_pass_t* p, const char* name, float x, float y, float z);
SFX_API void         sfx_pass_set_uniform_vec4 (sfx_pass_t* p, const char* name, float x, float y, float z, float w);
SFX_API void         sfx_pass_set_uniform_mat4 (sfx_pass_t* p, const char* name, const float* m16);
SFX_API void         sfx_pass_draw(sfx_pass_t* p, int vertex_count, int instance_count);
SFX_API void         sfx_pass_draw_indexed(sfx_pass_t* p, int index_count, int instance_count);
SFX_API void         sfx_pass_end(sfx_pass_t* p);

#ifdef __cplusplus
}
#endif

#endif // SFX_GFX_H