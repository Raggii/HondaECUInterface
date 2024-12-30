#include "main_screen.h++"

namespace MyApp {

lv_obj_t* MainScreen::create()
{
    // Create a new screen
    lv_obj_t* screen = lv_obj_create(NULL); // NULL can be replaced with lv_scr_act() if needed

    // Create a label on the screen
    lv_obj_t* label = lv_label_create(screen);
    lv_label_set_text(label, "Hello from LVGL v8.3!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    return screen;
}

} // namespace MyApp
