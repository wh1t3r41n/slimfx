// sfx_gl_api.h -- minimal public GL helpers so examples don't need glad directly
#ifndef SFX_GL_API_H
#define SFX_GL_API_H

#include "sfx_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SFX_API void sfx_gl_clear(float r, float g, float b, float a);
SFX_API void sfx_gl_set_viewport(int x, int y, int w, int h);
SFX_API const char* sfx_gl_version_string(void);
SFX_API const char* sfx_gl_renderer_string(void);

#ifdef __cplusplus
}
#endif

#endif // SFX_GL_API_H