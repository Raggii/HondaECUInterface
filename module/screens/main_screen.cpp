#include "main_screen.hpp"

namespace MyApp
{
    lv_obj_t* create_main_screen()
    {
        // Create a blank screen object
        lv_obj_t* scr = lv_obj_create(NULL);

        // Create a label on that screen
        lv_obj_t* label = lv_label_create(scr);
        lv_label_set_text(label, "Hello, LVGL + SDL!");
        lv_obj_center(label);

        // Return the screen so we can load it later
        return scr;
    }
}
