/*
    olcPGEX_FrostUI.h

    +-------------------------------------------------------------+
    |         OneLoneCoder Pixel Game Engine Extension            |
    |                FrostUI - v2.0.0			              |
    +-------------------------------------------------------------+

    What is this?
    ~~~~~~~~~~~~~
    This is an extension to the olcPixelGameEngine, which provides
    the ability to easily create Graphical User interfaces that
    may be used in some sort of game or desktop application.

    License (OLC-3)
    ~~~~~~~~~~~~~~~

    Copyright 2018, 2019, 2020, 2021 OneLoneCoder.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions or derivations of source code must retain the above
    copyright notice, this list of conditions and the following disclaimer.

    2. Redistributions or derivative works in binary form must reproduce
    the above copyright notice. This list of conditions and the following
    disclaimer must be reproduced in the documentation and/or other
    materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Author
    ~~~~~~
    Daniel aka Frosty
*/

#include <deque>
#ifndef OLC_PGEX_FROSTUI
#define OLC_PGEX_FROSTUI

struct Color_Scheme
{
    olc::Pixel button_normal = olc::GREY;
    olc::Pixel button_hover = { 150, 150, 150 };
    olc::Pixel button_click = { 100, 100, 100 };
};

Color_Scheme color_scheme;

enum class FUI_Type
{
    BUTTON = 0
};

class FUI_Window
{
private:
    olc::PixelGameEngine* pge;

    olc::Pixel border_color = olc::GREY;
    olc::Pixel background_color = olc::BLACK;

    olc::vi2d position;
    olc::vi2d last_position;
    olc::vi2d move_delta;
    olc::vi2d size;
    std::string title;

    bool should_render = true;

    std::string identifier;
    //std::string id, FUI_Window* parent, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback
    
    int border_thickness = 5;

public:
    FUI_Window(olc::PixelGameEngine* pge, std::string identifier, olc::vi2d position, olc::vi2d size, std::string title);

    void draw();

    void input();

    olc::vi2d get_position() { return position; }

    olc::vi2d get_size() { return size; }

    std::string get_id() { return identifier; }

    int get_border_thickness() { return border_thickness; }

    void set_background_color(olc::Pixel color) { background_color = color; };

    void set_border_color(olc::Pixel color) { border_color = color; }

    void set_border_thickness(int thickness) { border_thickness = thickness; }

    void close_window(bool close) { should_render = !close; }

    bool get_closed_state() { return should_render; }

    void change_position(olc::vi2d pos) { position = pos; }

    void change_size(olc::vi2d s) { size = s; }
};

FUI_Window::FUI_Window(olc::PixelGameEngine* p, std::string id, olc::vi2d pos, olc::vi2d s, std::string txt)
{
    identifier = id;
    pge = p;
    position = pos;
    size = s;
    title = txt;
}

void FUI_Window::draw()
{
    // Draw the main window area
    pge->FillRectDecal(position, size, background_color);

    // Draw the window border
    int border_size = border_thickness / 3;
    pge->FillRectDecal(position, olc::vf2d(border_size, size.y), border_color); // Left side
    pge->FillRectDecal(olc::vf2d(position.x + size.x - border_size, position.y), olc::vf2d(border_size, size.y), border_color); // Right side
    pge->FillRectDecal(olc::vf2d(position.x, position.y + size.y - border_size), olc::vf2d(size.x, border_size), border_color); // Bottom side
    pge->FillRectDecal(position, olc::vf2d(size.x, border_thickness), border_color); // Top bar

    // Draw the window title
    olc::vf2d title_position = olc::vf2d(position.x + (size.x / 2) - (pge->GetTextSize(title).x / 2), position.y + (border_thickness / 2) - (pge->GetTextSize(title).y / 2));
    pge->DrawStringDecal(title_position, title, olc::BLACK);
}

void FUI_Window::input()
{
    if (pge->GetMousePos().x >= position.x && pge->GetMousePos().x <= position.x + size.x - 20 &&
        pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + border_thickness &&
        pge->GetMouse(0).bHeld)
    {
        if (last_position.x != 0 && last_position.y != 0)
        {
            move_delta.x = pge->GetMousePos().x - last_position.x;
            move_delta.y = pge->GetMousePos().y - last_position.y;
        }

        position.x = position.x + move_delta.x;
        position.y = position.y + move_delta.y;

        last_position.x = pge->GetMousePos().x;
        last_position.y = pge->GetMousePos().y;
    }
    else
    {
        move_delta = { 0, 0 };
        last_position = { 0, 0 };
    }
}

/*
####################################################
################FUI_ELEMENT START###################
####################################################
*/

class FUI_Element
{
public:

    FUI_Window* parent = nullptr;
    olc::vi2d size;
    olc::vi2d position;
    olc::vi2d adaptive_position;
    std::string text;

    std::string identifier;

    virtual void draw(olc::PixelGameEngine* pge) {}

    virtual void input(olc::PixelGameEngine* pge) {}

    void set_size(olc::vi2d s) { size = s; }

    void set_position(olc::vi2d p) { position = p; }

    void set_text(std::string txt) { text = txt; }
};

/*
####################################################
################FUI_BUTTON START####################
####################################################
*/
class FUI_Button : public FUI_Element
{
private:
    enum class Button_State
    {
        NONE = 0,
        HOVER,
        CLICK
    };

    std::function<void()> callback;
    Button_State state = Button_State::NONE;

public:
    FUI_Button(std::string id, FUI_Window* parent, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(std::string id, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Button::FUI_Button(std::string id, FUI_Window* pt, std::string t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    callback = cb;
}

FUI_Button::FUI_Button(std::string id, std::string t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    callback = cb;
}

void FUI_Button::draw(olc::PixelGameEngine* pge)
{

    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness() / 3, parent->get_border_thickness()));
    else
        adaptive_position = olc::vi2d(0,0);

    // Draw the body of the button
    switch (state)
    {
    case Button_State::NONE:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_normal);
        break;
    case Button_State::HOVER:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_hover);
        break;
    case Button_State::CLICK:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_click);
        break;
    }
    // Draw the text
    olc::vf2d text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - (pge->GetTextSize(text).x / 2),
                                        adaptive_position.y + position.y + (size.y / 2) - (pge->GetTextSize(text).y / 2));
    pge->DrawStringDecal(text_position, text, olc::WHITE);
}

void FUI_Button::input(olc::PixelGameEngine* pge)
{
    if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
        pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
        pge->GetMousePos().y >= adaptive_position.y + position.y &&
        pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
    {
        if (pge->GetMouse(0).bHeld || pge->GetMouse(0).bPressed || pge->GetMouse(0).bReleased)
        {
            if (pge->GetMouse(0).bReleased)
                callback();
            state = Button_State::CLICK;
        }
        else
            state = Button_State::HOVER;
    }
    else
        state = Button_State::NONE;
}


/*
####################################################
################FUI_HANDLER START###################
####################################################
*/
class olcPGEX_FrostUI : public olc::PGEX
{
private:
    std::vector<FUI_Window*> windows;
    std::string active_window_id;
    bool has_set_window = false;
    std::deque <std::pair<FUI_Type, std::shared_ptr<FUI_Element>>> elements;

    void draw();

public:

    void set_active_window(std::string window_id) 
    { 
        for (auto& window : windows) 
        { 
            if (window->get_id() == window_id)
            {
                active_window_id = window_id;
                break;
            }
            else
                active_window_id.clear();
        }
        if (active_window_id.empty())
            std::cout << "Could not find the window ID in added windows\n";
    }

    void add_window(FUI_Window* w) { windows.emplace_back(w); has_set_window = true; }

    void run();

    void add_button(std::string parent_id, std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void add_button(std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    std::shared_ptr<FUI_Element> find_element(std::string identifier);

    void remove_element(std::string identifier);

};

void olcPGEX_FrostUI::remove_element(std::string id)
{
    int i = 0;
    for (auto& element : elements)
    {
        if (element.second->identifier == id)
        {
            elements.erase(elements.begin() + i);
            break;
        }
        i++;
    }
}

std::shared_ptr<FUI_Element> olcPGEX_FrostUI::find_element(std::string id)
{
    for (auto& element : elements)
    {
        if (element.second->identifier == id)
            return element.second;
    }
    return nullptr;
}

void olcPGEX_FrostUI::add_button(std::string parent_id, std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
{
    if (windows.size() > 0)
    {
        for (auto& window : windows)
        {
            if (window->get_id() == parent_id)
                elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
            else
                std::cout << "Coulnd't find window ID\n";
        }
    }
    else
        std::cout << "There's no windows to be used as parent\n";
}

void olcPGEX_FrostUI::add_button(std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
{
    if (!active_window_id.empty())
    {
        for (auto& window : windows)
        {
            if (window->get_id() == active_window_id)
                elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
        }
    }
    else
        elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, text, position, size, callback)));
}

void olcPGEX_FrostUI::draw()
{
    // Draw main window first
    if (windows.size() > 0)
    {
        for (auto& window : windows)
        {
            if (!window->get_closed_state())
                continue;
            window->draw();
            window->input();

            // first = FUI_Type, second = FUI_Element
            for (auto& e : elements)
            {
                if (e.second->parent)
                {
                    if (e.second->parent->get_id() == window->get_id())
                    {
                        e.second->draw(pge);
                        e.second->input(pge);
                    }
                    else
                        continue;
                }
                else
                {
                    e.second->draw(pge);
                    e.second->input(pge);
                }
            }
        }
    }
    else
    {
        for (auto& e : elements)
        {
             e.second->draw(pge);
             e.second->input(pge);
        }
    }
}

void olcPGEX_FrostUI::run()
{
    draw();
}

#endif
