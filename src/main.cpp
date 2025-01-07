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

    // Initialize a variable to keep track of the last log time.
    uint32_t last_log_time = SDL_GetTicks();

    while(true) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                goto quit;
            }
        }

        // Handle LVGL timers and tasks.
        lv_timer_handler();

        // Get the current time in milliseconds.
        uint32_t current_time = SDL_GetTicks();

        // Check if 3 seconds (3000 milliseconds) have passed since the last log.
        if(current_time - last_log_time >= 3000) {
            LOG_ERROR("Logging message every 3 seconds");
            LOG_RAINBOW("Logging message every 3 seconds");
            LOG_WARNING("Logging message every 3 seconds");
            last_log_time = current_time;
        }

        SDL_Delay(5);
    }

quit:
    gui_deinit();
    return 0;
}
