#define OLC_PGE_APPLICATION
#include "headers/olcPixelGameEngine.h"
#include "headers/gui.h"

bool first_run = true;
bool settings_finished = false;

class SettingsPrompt : public olc::PixelGameEngine
{
public:
    SettingsPrompt()
    {
        sAppName = "GAME NAME HERE";
    }

    GUI gui;
public:
    bool OnUserCreate() override
    {
        if (first_run)
            gui.create();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        
        if (first_run)
        {
            if (!gui.run())
            {
                first_run = false;
                settings_finished = true;
                return false;
            }
            else
                return true;
        }
        return true;
    }
};

int main()
{
    SettingsPrompt* settings_prompt = new SettingsPrompt;

    if (settings_prompt->Construct(1200, 750, 1, 1, false))
        settings_prompt->Start();

    delete settings_prompt;

    if (settings_finished)
    {
        SettingsPrompt* main_program = new SettingsPrompt;

        std::ifstream file("settings.json");
        json settings = json::parse(file);

        if (settings["custom_title"].size() > 0)
            main_program->sAppName = settings["custom_title"];

        if (main_program->Construct(settings["resolution_width"], settings["resolution_height"], 1, 1, settings["fullscreen"]))
            main_program->Start();
    }
    return 0;
}