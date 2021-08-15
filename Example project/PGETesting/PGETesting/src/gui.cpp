#define OLC_PGEX_FUI
#include "headers/gui.h"


void GUI::create()
{
    button_normal.Load("textures/button.jpg");
    texture_position.push_back({ 55, 60 });
    texture_position.push_back({ 55, 170 });

    frost_ui.add_groupbox("groupbox1", "", { 0, 0 }, { 200, 250 });

    frost_ui.add_dropdown("resolution", "Resolution: ", { 80, 10 }, { 100, 20 });
    frost_ui.find_element("resolution")->add_item("1920x1080");
    frost_ui.find_element("resolution")->add_item("1280x720");
    frost_ui.find_element("resolution")->add_item("800x600");
    frost_ui.find_element("resolution")->add_item("640x360");
    frost_ui.find_element("resolution")->add_item("640x360");
    frost_ui.find_element("resolution")->add_item("1920x1080");
    frost_ui.find_element("resolution")->add_item("1280x720");
    frost_ui.find_element("resolution")->add_item("800x600");
    frost_ui.find_element("resolution")->add_item("640x360");
    frost_ui.find_element("resolution")->add_item("640x360");
    frost_ui.find_element("resolution")->set_default_item(0);
    frost_ui.find_element("resolution")->set_animation_speed(1000);
    frost_ui.find_element("resolution")->set_max_display_items(2);

    frost_ui.add_dropdown("quality", "Quality: ", { 80, 40 }, { 100, 20 });
    frost_ui.find_element("quality")->add_item("High");
    frost_ui.find_element("quality")->add_item("Medium");
    frost_ui.find_element("quality")->add_item("Low");
    frost_ui.find_element("quality")->add_item("High");
    frost_ui.find_element("quality")->add_item("Medium");
    frost_ui.find_element("quality")->add_item("Low");
    frost_ui.find_element("quality")->add_item("High");
    frost_ui.find_element("quality")->add_item("Medium");
    frost_ui.find_element("quality")->add_item("Low");
    frost_ui.find_element("quality")->set_default_item(0);
    frost_ui.find_element("quality")->set_animation_speed(1000);
    frost_ui.find_element("quality")->set_max_display_items(5);

    frost_ui.add_checkbox("fullscreen", "Fullscreen: ", { 80, 70 }, { 20, 20 }, &fullscreen);

    frost_ui.add_inputfield("custom_title", "Custom title: ", { 80, 100 }, { 100, 20 });

    frost_ui.add_button("launch", "Launch game", { 10, 130 }, { 180, 20 }, [&]
        {
            auto res = frost_ui.find_element("resolution")->get_selected_item();
            auto qual = frost_ui.find_element("quality")->get_selected_item();
            auto title = frost_ui.find_element("custom_title")->get_inputfield_value();
            switch (res)
            {
            case 0:
                screen_width = 1920;
                screen_height = 1080;
                break;
            case 1:
                screen_width = 1280;
                screen_height = 720;
                break;
            case 2:
                screen_width = 800;
                screen_height = 600;
                break;
            case 3:
                screen_width = 640;
                screen_height = 360;
                break;
            }

            switch (qual)
            {
            case 0:
                quality = 0;
                break;
            case 1:
                quality = 1;
                break;
            case 2:
                quality = 2;
                break;
            }

            json settings;

            settings["resolution_width"] = screen_width;
            settings["resolution_height"] = screen_height;
            settings["quality"] = quality;
            settings["fullscreen"] = fullscreen;
            settings["custom_title"] = title;

            std::ofstream file("settings.json");

            file << settings.dump(4);

            run_return = false;
        });
    //frost_ui.find_element("launch")->add_texture(button_normal.Decal(), texture_position, { 295, 65 }, { 0.6f, 0.4f });

    frost_ui.add_int_slider("slider", "Testing: ", { 80, 160 }, { 100, 10 }, { -5, 5 }, &slider_value_int);

    frost_ui.add_float_slider("slider1", "Testing 2: ", { 80, 190 }, { 100, 10 }, { -155, 372 }, &slider_value_float);
}

bool GUI::run()
{
    frost_ui.run();

    return run_return;
}