#define OLC_PGEX_FUI
#include "headers/gui.h"

void GUI::create()
{
    auto main_window = frost_ui.create_window("main_window", "Login window", { 0, 0 }, { 250, 170 });

    frost_ui.set_active_window("main_window");
    frost_ui.add_groupbox("groupbox2", "", { 5, 5 }, { 230, 135 });

    auto groupbox_pos = frost_ui.find_groupbox("groupbox2")->get_position();

    frost_ui.add_inputfield("input_username", "Username: ", { groupbox_pos.x + 70, groupbox_pos.y + 20 }, { 150, 20 });
    frost_ui.add_inputfield("input_password", "Password: ", { groupbox_pos.x + 70, groupbox_pos.y + 60 }, { 150, 20 });

    // set inputfield text_scaling
    frost_ui.find_element("input_username")->inputfield_scale({ 1.0f, 1.25f });
    frost_ui.find_element("input_password")->inputfield_scale({ 1.0f, 1.25f });

    frost_ui.add_label("login_status", "Status: ", { groupbox_pos.x + 70, groupbox_pos.y + 120 });
    frost_ui.add_label("login_status2", "Waiting...", { groupbox_pos.x + 130, groupbox_pos.y + 120 });

    frost_ui.add_button("login_button", "LOGIN", { groupbox_pos.x + 70, groupbox_pos.y + 90 }, { 151, 20 }, [&]
        {
            auto username = frost_ui.find_element("input_username")->get_inputfield_value();
            auto password = frost_ui.find_element("input_password")->get_inputfield_value();

            if (username == "testing" && password == "testing123")
            {
                frost_ui.find_element("login_status2")->set_text("Successful!");
                frost_ui.find_element("login_status2")->set_text_color(olc::GREEN);
            }
            else
            {
                frost_ui.find_element("login_status2")->set_text("Unsuccessful!");
                frost_ui.find_element("login_status2")->set_text_color(olc::RED);
            }
        }
    );
}

void GUI::run()
{
    frost_ui.run();
}