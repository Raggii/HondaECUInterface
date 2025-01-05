#include "gui_init.h++"

#include <SDL2/SDL.h>
extern "C" {
#include "lvgl.h"
}

// Change to change resolution
static const int SDL_WINDOW_WIDTH  = 480;
static const int SDL_WINDOW_HEIGHT = 320;

static SDL_Window*   gWindow   = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Texture*  gTexture  = nullptr;

/**
 * @brief Flush callback for LVGL. Copies pixels to the SDL texture.
 */
static void my_disp_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    int32_t area_width  = area->x2 - area->x1 + 1;
    // int32_t area_height = area->y2 - area->y1 + 1;

    uint8_t* texture_pixels = nullptr;
    int texture_pitch       = 0;
    SDL_LockTexture(gTexture, nullptr, (void**)&texture_pixels, &texture_pitch);

    for(int y = area->y1; y <= area->y2; y++) {
        uint8_t* row_in_texture = texture_pixels + (y * texture_pitch) + (area->x1 * 2);
        memcpy(row_in_texture, color_p, area_width * 2);
        color_p += area_width;
    }

    SDL_UnlockTexture(gTexture);

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);

    lv_disp_flush_ready(disp_drv);
}

/**
 * @brief Initialize SDL (window, renderer, texture) for a given size.
 */
static void init_sdl(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("LVGL + SDL Example",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width, height,
                               0);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    // For 16-bit color: SDL_PIXELFORMAT_RGB565
    gTexture = SDL_CreateTexture(gRenderer,
                                 SDL_PIXELFORMAT_RGB565,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 width,
                                 height);
}

void gui_init(void)
{
    lv_init();
    init_sdl(SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT);

    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf1[SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT]; // Single buffer

    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, SDL_WINDOW_WIDTH * SDL_WINDOW_HEIGHT);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.flush_cb = my_disp_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res  = SDL_WINDOW_WIDTH;
    disp_drv.ver_res  = SDL_WINDOW_HEIGHT;

    lv_disp_drv_register(&disp_drv);
}

void gui_deinit(void)
{
    SDL_DestroyTexture(gTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
