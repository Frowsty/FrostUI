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


public:
    bool OnUserCreate() override
    {
        int i = 0;
        frost_ui.add_window(&main_window);
        frost_ui.set_active_window(main_window.get_identifier());
        frost_ui.add_button("id1","Test Button", olc::vi2d(5, 5), olc::vi2d(100, 20), [&] 
            { 
                i++;
                frost_ui.find_element("id1")->set_size(olc::vi2d(200, 20));
                frost_ui.find_element("id1")->set_text("Clicked " + std::to_string(i) + " Times");

                if (!frost_ui.find_element("id2"))
                    frost_ui.add_button("id2", "Reset", olc::vi2d(5, 30), olc::vi2d(100, 20), [&] 
                        {
                            i = 0;
                            auto temp = frost_ui.find_element("id1");
                            temp->set_size(olc::vi2d(100, 20));
                            temp->set_text("Test Button");
                        });
            });

        main_window.set_background_color(olc::WHITE);
        main_window.set_border_color(olc::GREY);
        main_window.set_border_thickness(20);

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        if (GetKey(olc::ESCAPE).bPressed)
            return false;

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