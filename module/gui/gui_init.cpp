#include "gui_init.hpp"
#include <SDL2/SDL.h>

extern "C" {
#include "lvgl.h"
#include "sdl/sdl.h"
}

static const int SDL_WINDOW_WIDTH  = 480;
static const int SDL_WINDOW_HEIGHT = 320;

void gui_init(void)
{
    lv_init();
    sdl_init();  // Provided by lv_drivers

    static lv_disp_draw_buf_t disp_buf;
    // Just one buffer; use more if needed
    static lv_color_t buf1[SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT];
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.flush_cb = sdl_display_flush;  // Provided by lv_drivers
    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res  = SDL_WINDOW_WIDTH;
    disp_drv.ver_res  = SDL_WINDOW_HEIGHT;

    lv_disp_drv_register(&disp_drv);
}

void gui_deinit(void)
{
    SDL_Quit();
}
