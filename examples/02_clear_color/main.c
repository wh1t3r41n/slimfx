// 02_clear_color -- uses slim_core public API only
#include <sfx_window.h>
#include <sfx_gl_api.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    sfx_window_desc_t desc = {
        .title = "slimfx :: 02 clear color",
        .width = 960, .height = 540,
        .resizable = 1, .samples = 4, .vsync = 1
    };
    sfx_window_t* win = NULL;
    if (sfx_window_create(&desc, &win) != SFX_OK) return 1;

    fprintf(stderr, "[slimfx] GL: %s | %s\n",
            sfx_gl_version_string(), sfx_gl_renderer_string());

    while (!sfx_window_should_close(win)) {
        sfx_window_poll(win);

        const sfx_input_state_t* in = sfx_window_get_input(win);
        if (in && in->keys[SFX_KEY_ESCAPE]) sfx_window_set_should_close(win, 1);

        float t = sfx_window_get_time();
        sfx_gl_clear(
            0.5f + 0.5f * sinf(t),
            0.5f + 0.5f * sinf(t + 2.094f),
            0.5f + 0.5f * sinf(t + 4.188f),
            1.0f
        );

        sfx_window_swap_buffers(win);
    }
    sfx_window_destroy(win);
    return 0;
}