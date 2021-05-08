#pragma once
#include "headers/olcPGEX_FrostUI.h"
#include "generator.h"

class GUI
{
private:
    int password_length;

public:

    Gen generator;

    olc::FrostUI frost_ui;

    void create();

    void run();
};