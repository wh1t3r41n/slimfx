// 01_hello_window -- minimal slimfx window: title + FPS in window title
#include "../../include/slimfx/sfx_window.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    sfx_window_desc_t desc = {
        .title = "slimfx :: 01 hello window",
        .width = 960, .height = 540,
        .resizable = 1, .samples = 4, .vsync = 1
    };

    sfx_window_t* win = NULL;
    sfx_result_t r = sfx_window_create(&desc, &win);
    if (r != SFX_OK) {
        fprintf(stderr, "sfx_window_create failed: %d\n", r);
        return 1;
    }

    while (!sfx_window_should_close(win)) {
        sfx_window_poll(win);

        // ESC to close
        const sfx_input_state_t* in = sfx_window_get_input(win);
        if (in && in->keys[SFX_KEY_ESCAPE]) {
            sfx_window_set_should_close(win, 1);
        }

        // Update title with FPS every ~0.25s
        static float last = 0.f;
        float now = sfx_window_get_time();
        if (now - last > 0.25f) {
            last = now;
            char title[128];
            snprintf(title, sizeof(title), "slimfx :: 01 hello window  [%.1f FPS]",
                     sfx_window_get_fps(win));
            // GLFW owns the title; we re-set it via the public desc? no -- expose later.
            // For now we just print to stderr.
            fprintf(stderr, "%s\n", title);
        }

        sfx_window_swap_buffers(win);
    }

    sfx_window_destroy(win);
    return 0;
}