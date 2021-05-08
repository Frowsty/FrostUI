#define OLC_PGE_APPLICATION
#define OLC_GFX_OPENGL33

#include "headers/olcPixelGameEngine.h"
#include "headers/gui.h"


class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "FrostUI Example Program";
    }

    GUI gui;
public:
    bool OnUserCreate() override
    {
        gui.create();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        
        gui.run();

        return true;
    }
};


int main()
{
    Example demo;

    if (demo.Construct(500, 300, 1, 1))
        demo.Start();

    return 0;
}