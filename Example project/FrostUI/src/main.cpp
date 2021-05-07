#define OLC_PGE_APPLICATION
#define OLC_GFX_OPENGL33
#define OLC_PGEX_FUI

#include "headers/olcPixelGameEngine.h"
#include "headers/olcPGEX_FrostUI.h"

//#define STANDALONE

class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "FrostUI Example Program";
    }

    olc::FrostUI frost_ui;
public:
    bool OnUserCreate() override
    {
        
        // Create all windows
#ifndef STANDALONE
        auto main_window = frost_ui.create_window("main_window", "Login window", { 0, 0 }, { 250, 170 });

        //main_window->disable_dragging(true);

        frost_ui.set_active_window("main_window");
        frost_ui.add_groupbox("groupbox2", "", { 5, 5 }, { 230, 135 });
#else
        frost_ui.add_groupbox("groupbox2", "", { 0, 0 }, { 230, 135 });
#endif
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
        
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
#ifndef STANDALONE
        if (GetKey(olc::SHIFT).bPressed)
            frost_ui.find_window("main_window")->close_window(false);
#endif
        frost_ui.run();
        

        return true;
    }
};


int main()
{
    Example demo;
#ifndef STANDALONE
    if (demo.Construct(400, 300, 1, 1))
        demo.Start();
#else
    if (demo.Construct(230, 135, 2, 2, false, true))
        demo.Start();
#endif
    return 0;
}