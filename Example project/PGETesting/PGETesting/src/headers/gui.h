#pragma once
#include "olcPGEX_FrostUI.h"
#include "json.hpp"

using json = nlohmann::json;

class GUI
{
private:
    olc::FrostUI frost_ui;

    bool run_return = true;

    // settings
    int screen_width = 200;
    int screen_height = 250;
    int quality = 0;
    bool fullscreen = false;

    int slider_value_int = -5;
    float slider_value_float = -132.0f;

    olc::Renderable button_normal;
    std::vector<olc::vi2d> texture_position;
public:

    void create();

    bool run();
};