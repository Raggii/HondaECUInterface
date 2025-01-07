#pragma once

extern "C" {
#include "lvgl.h"
}
#include "logging.hpp"

namespace MyApp
{
    /**
     * Create and return the main screen (an LVGL object).
     */
    lv_obj_t* create_main_screen();
}
