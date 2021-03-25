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
    FUI_Window main_window{ this, "main_window", { 50, 25 }, { 400, 250 }, "New Window"};

    int i = 0;

public:
    bool OnUserCreate() override
    {

        // Setting some colors
        main_window.set_background_color(olc::WHITE);
        main_window.set_border_color(olc::GREY);
        main_window.set_border_thickness(20);

        frost_ui.add_window(&main_window); // Add window to UI Handler
        // Create a standalone button relative to main_window (Used as exit button in this regard) (add_button allows you to manually set parent or use set_active_window)
        frost_ui.add_button("main_window", "exit_button", "X", { main_window.get_size().x - 20 - (main_window.get_border_thickness() / 3),  -20 }, { 20, 20 }, [&] 
            {
                main_window.close_window(true);
            });
        frost_ui.set_active_window(main_window.get_id()); // Set the active window (window that will be used to add elements)

        // Nesting buttons
        frost_ui.add_button("id1", "Test Button", { 5, 5 }, { 100, 20 }, [&]
            {
                i++;
                auto temp = frost_ui.find_element("id1");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(i) + " Times");

                if (!frost_ui.find_element("id2"))
                    frost_ui.add_button("id2", "Reset", { 5, 30 }, { 100, 20 }, [&]
                        {
                            i = 0;
                            auto temp = frost_ui.find_element("id1");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button");
                            frost_ui.remove_element("id2");
                        });
            });

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        if (GetKey(olc::SHIFT).bPressed)
            main_window.close_window(false);

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