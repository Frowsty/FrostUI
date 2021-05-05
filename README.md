# olcPGEX_FrostUI

This extension is designed for use with the [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) by [Javidx9](https://github.com/OneLoneCoder).

---

## Usage

To use the olcPGEX_FrostUI extension, it needs to be included in your application.

```cpp
#define OLC_PGEX_FUI
#include "olcPGEX_FrostUI.h"
```

### Example usage

```cpp
// define the 
olc::FrostUI ui;

bool OnUserCreate()
{
    /*
    create all ui windows/elements here by using the available functions
    */
    
    //creating a window
    ui.create_window(std::string id, std::string title, olc::vi2d position, olc::vi2d size);
    
    //How to add elements using ui.set_active_window(window_id):
    ui.set_active_window(std::string window_id);
    add_button(std::string id, std::string text, olc::vi2d position, olc::vi2d size, callback);
    add_inputfield(std::string id, std::string text, olc::vi2d position, olc::vi2d size);
    
    //How to add elements without using ui.set_active_window(window_id):
    add_button(std::string window_id, std::string id, std::string text, olc::vi2d position, olc::vi2d size, callback);
    add_inputfield(std::string window_id,std::string id, std::string text, olc::vi2d position, olc::vi2d size);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK)

    ui.run();
    
    return true;
}
```
(A wiki page is planned)
