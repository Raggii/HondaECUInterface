#ifndef MAIN_SCREEN_HXX
#define MAIN_SCREEN_HXX

#include "lvgl.h" // Ensure this points to your local lvgl.h

namespace MyApp {

/**
 * @brief Creates and returns a pointer to the main screen.
 * @return lv_obj_t* Pointer to the created main screen.
 */
class MainScreen {
public:
    static lv_obj_t* create();
};

} // namespace MyApp

#endif // MAIN_SCREEN_HXX
