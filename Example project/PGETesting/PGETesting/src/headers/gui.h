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
public:

    void create();

    bool run();
};