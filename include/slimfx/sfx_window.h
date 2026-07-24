// sfx_window.h -- window + GL context + input + main loop helper
#ifndef SFX_WINDOW_H
#define SFX_WINDOW_H

#include "sfx_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sfx_window sfx_window_t;

typedef struct sfx_window_desc {
    const char* title;
    int         width;
    int         height;
    int         resizable;        // 0 or 1
    int         samples;          // MSAA: 1, 2, 4, 8, 16 (0 -> 1)
    int         vsync;            // 0 or 1
} sfx_window_desc_t;

typedef struct sfx_input_state {
    // Key state snapshot (filled by sfx_window_poll). 1 = pressed, 0 = released.
    // Indexed by GLFW key codes (we re-export a minimal subset below).
    uint8_t keys[512];
    // Mouse buttons: 0 left, 1 right, 2 middle
    uint8_t mouse_buttons[8];
    double mouse_x, mouse_y;
    double scroll_x, scroll_y;
} sfx_input_state_t;

// Minimal key codes mirroring GLFW for the demo. We can extend later.
typedef enum sfx_key {
    SFX_KEY_UNKNOWN = 0,
    SFX_KEY_SPACE   = 32,
    SFX_KEY_ESCAPE  = 256,
    SFX_KEY_ENTER   = 257,
    SFX_KEY_TAB     = 258,
    SFX_KEY_BACKSPACE = 259,
    SFX_KEY_RIGHT = 262,
    SFX_KEY_LEFT  = 263,
    SFX_KEY_DOWN  = 264,
    SFX_KEY_UP    = 265,
    SFX_KEY_A = 65, SFX_KEY_B, SFX_KEY_C, SFX_KEY_D, SFX_KEY_E, SFX_KEY_F,
    SFX_KEY_G, SFX_KEY_H, SFX_KEY_I, SFX_KEY_J, SFX_KEY_K, SFX_KEY_L,
    SFX_KEY_M, SFX_KEY_N, SFX_KEY_O, SFX_KEY_P, SFX_KEY_Q, SFX_KEY_R,
    SFX_KEY_S, SFX_KEY_T, SFX_KEY_U, SFX_KEY_V, SFX_KEY_W, SFX_KEY_X,
    SFX_KEY_Y, SFX_KEY_Z,
} sfx_key_t;

SFX_API sfx_result_t sfx_window_create(const sfx_window_desc_t* desc, sfx_window_t** out);
SFX_API void          sfx_window_destroy(sfx_window_t* w);

SFX_API int           sfx_window_should_close(const sfx_window_t* w);
SFX_API void          sfx_window_set_should_close(sfx_window_t* w, int value);

SFX_API void          sfx_window_poll(sfx_window_t* w);
SFX_API void          sfx_window_swap_buffers(sfx_window_t* w);
SFX_API void          sfx_window_get_size(const sfx_window_t* w, int* width, int* height);
SFX_API float         sfx_window_get_time(void);   // seconds since process start
SFX_API double        sfx_window_get_fps(const sfx_window_t* w); // smoothed

SFX_API const sfx_input_state_t* sfx_window_get_input(const sfx_window_t* w);

// Sets a user-data pointer (used by gfx layer for the GL context owner).
SFX_API void          sfx_window_set_user_data(sfx_window_t* w, void* user);
SFX_API void*         sfx_window_get_user_data(const sfx_window_t* w);

#ifdef __cplusplus
}
#endif

#endif // SFX_WINDOW_H