#define OLC_PGE_APPLICATION
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
    FUI_Window main_window{ this, "main_window", { 10, 25 }, { 490, 250 }, "New Window"};
    FUI_Window new_window{ this, "new_window", { 520, 25 }, { 490, 250 }, "New Window" };

    int i = 0;
    int j = 0;

public:
    bool OnUserCreate() override
    {
        // Setting some colors
        main_window.set_background_color(olc::WHITE);
        main_window.set_border_color(olc::GREY);
        main_window.set_top_border_thickness(20);
        main_window.set_border_thickness(5);

        // Setting some colors
        new_window.set_background_color(olc::WHITE);
        new_window.set_border_color(olc::GREY);
        new_window.set_top_border_thickness(20);
        new_window.set_border_thickness(5);

        frost_ui.add_window(&main_window); // Add window to UI Handler
        frost_ui.add_window(&new_window); // Add window to UI Handler
        // Create groups for respective tabs
        frost_ui.add_group("tab_1");
        frost_ui.add_group("tab_2");
        frost_ui.add_group("tab_3");

        // Create a close button with a manual parent ID 
        // you can manually pass parent ID instead of using set_active_window which will default all element to the active window
        // The following button will not have a group attached which means it will be rendered despite a specific group being the render target
        // We don't want to have a group assigned to the close button since we want to render it at all times
        /*frost_ui.add_button("main_window", "exit_button", "X", { main_window.get_size().x - 20 - (main_window.get_border_thickness() / 3), -20 }, { 20, 20 }, [&] 
            {
                main_window.close_window(true);
            });
        frost_ui.find_element("exit_button")->set_text_color(olc::BLACK);
        */
        // Set the active window (window that will be used to add elements)
        frost_ui.set_active_window(main_window.get_id());

        // Tabs example
        int tab_size = main_window.get_window_space().x / 3;
        std::cout << tab_size * 3;
        frost_ui.add_button("tab1", "Tab 1", { 0, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_1"); });
        frost_ui.add_button("tab2", "Tab 2", { tab_size, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_2"); });
        frost_ui.add_button("tab3", "Tab 3", { tab_size * 2, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_3"); });

        // Set the active group to tab_1 (every element that is added to the UI instance will now be a part of this group)
        frost_ui.set_active_group("tab_1");
        // Nesting buttons in the tab_1 group
        frost_ui.add_button("id1", "Test Button", { 5, 25 }, { 100, 20 }, [&]
            {
                i++;
                auto temp = frost_ui.find_element("id1");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(i) + " Times");
                if (!frost_ui.find_element("id2"))
                {
                    auto temp_group = frost_ui.get_active_group();
                    frost_ui.clear_active_group();
                    frost_ui.add_button("id2", "Reset", { 5, 50 }, { 100, 20 }, [&]
                        {
                            i = 0;
                            auto temp = frost_ui.find_element("id1");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button");
                            frost_ui.remove_element("id2");
                        });
                    frost_ui.set_active_group(temp_group);
                }
            });

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
            main_window.close_window(false);
        if (GetKey(olc::ENTER).bPressed)
            new_window.close_window(false);

        frost_ui.run();

        return true;
    }
};


int main()
{
    Example demo;
    if (demo.Construct(1024, 512, 1, 1))
        demo.Start();

    return 0;
}