#include "gui_init.hpp"
#include "main_screen.hpp"

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
