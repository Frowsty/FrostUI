#define OLC_PGE_APPLICATION
#define OLC_GFX_OPENGL33

#include "headers/olcPixelGameEngine.h"
#include "headers/olcPGEX_FrostUI.h"

class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "Example";
    }

    olcPGEX_FrostUI frost_ui;

    int i = 0;
    int j = 0;

    bool checkbox_state = false;
    bool last_cb_state = checkbox_state;

public:
    bool OnUserCreate() override
    {
        // Create all windows
        auto main_window = frost_ui.create_window("main_window", { 10, 25 }, { 490, 250 }, "New Window");
        auto new_window1 = frost_ui.create_window("new_window", { 520, 25 }, { 490, 250 }, "New Window");
        auto new_window2 = frost_ui.create_window("new_window2", { 520, 300 }, { 490, 250 }, "New Window");
        auto new_window3 = frost_ui.create_window("new_window3", { 10, 300 }, { 490, 250 }, "New Window");
        auto new_window4 = frost_ui.create_window("new_window4", { 300, 200 }, { 490, 250 }, "New Window");

        // Setting some colors
        main_window->set_background_color(olc::WHITE);
        main_window->set_border_color(olc::GREY);
        main_window->set_top_border_thickness(20);
        main_window->set_border_thickness(5);

        // Setting some colors
        new_window1->set_background_color(olc::WHITE);
        new_window1->set_border_color(olc::GREY);
        new_window1->set_top_border_thickness(20);
        new_window1->set_border_thickness(5);

        // Setting some colors
        new_window2->set_background_color(olc::WHITE);
        new_window2->set_border_color(olc::GREY);
        new_window2->set_top_border_thickness(20);
        new_window2->set_border_thickness(5);

        // Setting some colors
        new_window3->set_background_color(olc::WHITE);
        new_window3->set_border_color(olc::GREY);
        new_window3->set_top_border_thickness(20);
        new_window3->set_border_thickness(5);

        // Setting some colors
        new_window4->set_background_color(olc::WHITE);
        new_window4->set_border_color(olc::GREY);
        new_window4->set_top_border_thickness(20);
        new_window4->set_border_thickness(5);

        // Create groups for respective tabs
        frost_ui.add_group("tab_1");
        frost_ui.add_group("tab_2");
        frost_ui.add_group("tab_3");

        // Set the active window (window that will be used to add elements)
        frost_ui.set_active_window("main_window");

        // Tabs example
        int tab_size = main_window->get_window_space().x / 3;
        frost_ui.add_button("tab1", "Tab 1", { 0, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_1"); });
        frost_ui.add_button("tab2", "Tab 2", { tab_size, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_2"); });
        frost_ui.add_button("tab3", "Tab 3", { tab_size * 2, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_3"); });

        // Set the active group to tab_1 (every element that is added to the UI instance will now be a part of this group)
        frost_ui.set_active_group("tab_1");

        frost_ui.add_label("label_1", "Test label", { 200, 40 });
        auto temp_var = frost_ui.find_element("label_1");
        if (!frost_ui.find_window("main_window"))
            temp_var->set_text_color(olc::WHITE);
        else
            temp_var->set_text_color(olc::BLACK);
        frost_ui.find_element("label_1")->set_centered(false);

        // Nesting buttons in the tab_1 group
        frost_ui.add_button("id1", "Test Button", { 5, 25 }, { 100, 20 }, [&]
            {
                i++;
                auto temp = frost_ui.find_element("id1");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(i) + " Times");
                if (!frost_ui.find_element("id2"))
                {
                    frost_ui.add_button("id2", "Reset", { 5, 50 }, { 100, 20 }, [&]
                        {
                            i = 0;
                            auto temp = frost_ui.find_element("id1");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button");
                            frost_ui.remove_element("id2");
                        });
                }
            });

        frost_ui.clear_active_group();

        frost_ui.add_checkbox("id5", "HELLO WORLD", { 5, 75 }, { 15, 15 }, &checkbox_state);
        frost_ui.find_element("id5")->set_text_color(olc::BLACK);
        frost_ui.find_element("id5")->set_checkbox_orientation("down");
        
        // Change the active group to tab_2 (every element will be automatically added to this group)
        frost_ui.set_active_group("tab_2");
        // Nesting buttons in the tab_2 group
        frost_ui.add_button("id3", "Test Button 2", { 5, 25 }, { 100, 20 }, [&]
            {
                j++;
                auto temp = frost_ui.find_element("id3");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(j) + " Times");
                if (!frost_ui.find_element("id4"))
                    frost_ui.add_button("id4", "Reset 2", { 5, 50 }, { 100, 20 }, [&]
                        {
                            j = 0;
                            auto temp = frost_ui.find_element("id3");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button 2");
                            frost_ui.remove_element("id4");
                        });
            });

        // set the active group to tab_1 (this will act as the default group to be rendered)
        frost_ui.set_active_group("tab_1");

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        if (GetKey(olc::SHIFT).bPressed)
            frost_ui.find_window("main_window")->close_window(false);
        if (GetKey(olc::ENTER).bPressed)
            frost_ui.find_window("new_window")->close_window(false);

        if (checkbox_state != last_cb_state)
            std::cout << checkbox_state << "\n";

        last_cb_state = checkbox_state;

        frost_ui.run();



        return true;
    }
};


int main()
{
    Example demo;
    if (demo.Construct(1024, 720, 1, 1))
        demo.Start();

    return 0;
}