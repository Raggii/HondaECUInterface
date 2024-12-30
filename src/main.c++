#include <cstdio>     // For printf (optional)
#include <unistd.h>
#include "lvgl.h"
#include "main_screen.h++"

// If using C++ and LVGL headers are not wrapped in extern "C"
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h" // Ensure lv_conf.h is included correctly

#ifdef __cplusplus
}
#endif

/* Forward declaration of the flush callback */
static void my_disp_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);

int main(void)
{
    // Initialize LVGL
    lv_init();

    // Initialize your hardware here (e.g., display, input devices)
    // For example, initialize an SDL display driver if on desktop
    // init_display();

    // 1. Initialize a display buffer
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[LV_HOR_RES_MAX * 10];  // Buffer for 10 lines
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LV_HOR_RES_MAX * 10);

    // 2. Initialize a display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);        // Basic initialization

    disp_drv.hor_res = LV_HOR_RES_MAX;  // Set horizontal resolution
    disp_drv.ver_res = LV_VER_RES_MAX;  // Set vertical resolution
    disp_drv.flush_cb = my_disp_flush_cb; // Set the flush callback
    disp_drv.draw_buf = &draw_buf;          // Assign the display buffer

    // Register the display driver
    lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

    // 3. Create and load the main screen
    lv_obj_t* main_scr = MyApp::MainScreen::create();
    lv_scr_load(main_scr);

    // 4. Create a simple tick interface (required by LVGL)
    // For example, if using SDL:
    // lv_tick_inc(5); // Increment the tick by 5 ms
    // Alternatively, set up a timer or thread to call lv_tick_inc periodically

    // 5. Main loop
    while (true)
    {
        lv_task_handler();              // Handle LVGL tasks
        // Implement a small delay here to prevent hogging the CPU
        // For example, using sleep or platform-specific delay functions
        // On Unix/Linux:
        usleep(5000); // Sleep for 5 ms
    }

    return 0;
}

/**
 * @brief Flush callback for the display driver.
 * This function should copy the rendered pixels from `color_p` to your display.
 * After flushing, you must call `lv_disp_flush_ready(disp_drv)`.
 */
static void my_disp_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    // Implement the actual flush logic here
    // For example, on embedded systems, write the pixels to the framebuffer

    // Example pseudo-code:
    // display_copy_pixels(area, color_p);

    // Indicate that flushing is done
    lv_disp_flush_ready(disp_drv);
}
