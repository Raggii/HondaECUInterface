#include "gui_init.hpp"
#include "main_screen.hpp"
#include "logging.hpp"

#include <SDL2/SDL.h>
extern "C" {
#include "lvgl.h"
}

int main()
{
    gui_init();

    lv_obj_t* screen = MyApp::create_main_screen();
    lv_scr_load(screen);

    while(true) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            // Log mouse button down events
            // if(e.type == SDL_MOUSEBUTTONDOWN) {
            //     printf("Mouse button pressed at (%d, %d)\n", e.button.x, e.button.y);
            //     fflush(stdout);
            // }
            // // Log mouse button up events
            // if(e.type == SDL_MOUSEBUTTONUP) {
            //     printf("Mouse button released at (%d, %d)\n", e.button.x, e.button.y);
            //     fflush(stdout);
            // }
            if(e.type == SDL_QUIT) {
                goto quit;
            }
        }

        lv_timer_handler();
        SDL_Delay(5);
    }


quit:
    gui_deinit();
    return 0;
}
