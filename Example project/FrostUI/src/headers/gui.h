#pragma once
#include "olcPGEX_FrostUI.h"

class GUI
{
private:
    olc::FrostUI frost_ui;

    int slider_value = 0;
public:

    void create();

    void run();
};