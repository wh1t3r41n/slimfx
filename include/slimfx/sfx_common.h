// sfx_common.h -- shared types, error codes, export macros
#ifndef SFX_COMMON_H
#define SFX_COMMON_H

#include <stdint.h>
#include <stddef.h>

#if defined(_WIN32) || defined(_WIN64)
#  if defined(SFX_BUILD_DLL)
#    define SFX_API __declspec(dllexport)
#  elif defined(SFX_USE_DLL)
#    define SFX_API __declspec(dllimport)
#  else
#    define SFX_API
#  endif
#else
#  if defined(__GNUC__) && (__GNUC__ >= 4)
#    define SFX_API __attribute__((visibility("default")))
#  else
#    define SFX_API
#  endif
#endif

typedef enum sfx_result {
    SFX_OK                   = 0,
    SFX_ERR_INVALID_ARG      = -1,
    SFX_ERR_OUT_OF_MEMORY    = -2,
    SFX_ERR_BACKEND          = -3,  // GLFW / GL failure
    SFX_ERR_NOT_INITIALIZED  = -4,
    SFX_ERR_ALREADY          = -5,
    SFX_ERR_PLATFORM         = -6,
} sfx_result_t;

typedef struct sfx_version {
    int major;
    int minor;
    int patch;
} sfx_version_t;

SFX_API sfx_version_t sfx_get_version(void);

#endif // SFX_COMMON_H