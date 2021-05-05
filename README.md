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
olc::FrostUI ui; // create the UI handler

bool OnUserCreate()
{
    //create all ui windows/elements here by using the available functions

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK)

    ui.run(); // run the UI handler
    
    return true;
}
```
(A wiki page is planned)
