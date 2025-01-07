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
    static lv_color_t buf1[SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT];
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res  = SDL_WINDOW_WIDTH;
    disp_drv.ver_res  = SDL_WINDOW_HEIGHT;

    lv_disp_drv_register(&disp_drv);

    // Initialize and register mouse input device AFTER registering display driver
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read; 
    lv_indev_drv_register(&indev_drv);
}


void gui_deinit(void)
{
    SDL_Quit();
}
