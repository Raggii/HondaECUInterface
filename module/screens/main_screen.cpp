#include "main_screen.hpp"
#include <stdio.h>  // for printf

namespace MyApp
{
    static bool button_pressed = false;

    static void btn_event_handler(lv_event_t* e) {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_PRESSED) {
            button_pressed = true;
            printf("Button pressed!\n");
            fflush(stdout);
        }
        else if(code == LV_EVENT_RELEASED) {
            if(button_pressed) {
                printf("Button clicked!\n");
                fflush(stdout);
                button_pressed = false;  // Reset press state after a click is processed
            }
            printf("Button released!\n");
            fflush(stdout);
        }
    }

    lv_obj_t* create_main_screen()
    {
        // Create a blank screen object
        lv_obj_t* scr = lv_obj_create(NULL);

        // Create a label on that screen
        lv_obj_t* label = lv_label_create(scr);
        lv_label_set_text(label, "Hello, LVGL + SDL!");
        lv_obj_center(label);

        // Create a button
        lv_obj_t* btn = lv_btn_create(scr);
        lv_obj_set_size(btn, 120, 50);
        lv_obj_align(btn, LV_ALIGN_CENTER, 0, 50);  // Position the button below the label

        // Attach the event callback to the button
        lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_ALL, NULL);

        // Add a label on the button
        lv_obj_t* btn_label = lv_label_create(btn);
        lv_label_set_text(btn_label, "Click me");
        lv_obj_center(btn_label);

        // Return the screen so we can load it later
        return scr;
    }
}
