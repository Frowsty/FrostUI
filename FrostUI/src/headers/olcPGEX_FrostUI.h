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

struct FUI_Colors
{
    olc::Pixel button_normal = olc::GREY;
    olc::Pixel button_hover = { 150, 150, 150 };
    olc::Pixel button_click = { 100, 100, 100 };
};

FUI_Colors color_scheme;

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
    olc::vi2d mouse_difference;
    olc::vi2d size;
    std::string title;

    bool is_dragging = false;

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
    if ((pge->GetMousePos().x >= position.x && pge->GetMousePos().x <= position.x + size.x &&
        pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + border_thickness) || is_dragging)
    {
        if (pge->GetMouse(0).bPressed)
        {
            is_dragging = true;
            mouse_difference = pge->GetMousePos() - position;
        }

        if (pge->GetMouse(0).bHeld && is_dragging)
            position = pge->GetMousePos() - mouse_difference;
    }
    
    if (pge->GetMouse(0).bReleased)
        is_dragging = false;
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
    std::string group;
    
    olc::Pixel text_color = olc::WHITE;

    std::string identifier;

    virtual void draw(olc::PixelGameEngine* pge) {}

    virtual void input(olc::PixelGameEngine* pge) {}

    virtual void update() {}

    void set_size(olc::vi2d s) { size = s; }

    void set_position(olc::vi2d p) { position = p; }

    void set_text(std::string txt) { text = txt; }

    void set_text_color(olc::Pixel color) { text_color = color; }

    std::string get_group() { return group;  }
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
    FUI_Button(std::string id, FUI_Window* parent, std::string group, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(std::string id, std::string group, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(std::string id, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;

    void update() override;
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

FUI_Button::FUI_Button(std::string id, FUI_Window* pt, std::string g, std::string t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    callback = cb;
    group = g;
}

FUI_Button::FUI_Button(std::string id, std::string g, std::string t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    callback = cb;
    group = g;
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
    pge->DrawStringDecal(text_position, text, text_color);
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

void FUI_Button::update()
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness() / 3, parent->get_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);
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
    std::vector<std::string> groups;
    std::string active_window_id;
    std::string active_group;
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
            std::cout << "Could not find the window ID in added windows (function affected: set_active_window, affected window_id: " + window_id + ")\n";
    }

    void set_active_group(std::string g)
    {
        for (auto group : groups)
        {
            if (group == g)
            {
                active_group = g;
                break;
            }
            else
                active_group.clear();
        }
        if (active_group.empty())
            std::cout << "Could not find the group ID in added windows (function affected: set_active_group, affected window_id: " + g + ")\n";
    }

    void add_window(FUI_Window* w)
    {
        bool is_duplicate = false;
        for (auto& window : windows)
        {
            if (window->get_id() == w->get_id())
                is_duplicate = true;
        }
        if (!is_duplicate)
            windows.push_back(w);
        else
            std::cout << "Cannot add duplicates of same window (function affected: add_window, affected window_id: " + w->get_id() + ")\n";
    }

    void add_group(std::string g) 
    {
        bool is_duplicate = false;
        for (auto group : groups)
        {
            if (group == g)
                is_duplicate = true;
        }
        if (!is_duplicate)
            groups.push_back(g);
        else
            std::cout << "Cannot add duplicates of same group (function affected: add_group, affected group_id: " + g + ")\n";
    }

    void clear_active_group() { active_group.clear(); }

    std::string get_active_group() { return active_group; }

    void run();

    void add_button(std::string parent_id, std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void add_button(std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    std::shared_ptr<FUI_Element> find_element(std::string identifier);

    void remove_element(std::string identifier);

    int get_element_amount() { return elements.size(); }

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
                if (!active_group.empty())
                    elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
                else
                    elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, active_group, text, position, size, callback)));
            else
                std::cout << "Could not find parent window ID (function affected: add_button, button_id affected: " + identifier + ")\n";
        }
    }
    else
        std::cout << "There's no windows to be used as parent (function affected: add_button, button_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_button(std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
{
    if (!active_window_id.empty())
    {
        for (auto& window : windows)
        {
            if (window->get_id() == active_window_id)
                if (!active_group.empty())
                    elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, active_group, text, position, size, callback)));
                else
                    elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
        }
    }
    else
        if (!active_group.empty())
            elements.push_back(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, active_group, text, position, size, callback)));
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

            window->input();
            window->draw();
            

            // first = FUI_Type, second = FUI_Element
            for (auto& e : elements)
            {
                if (!e.second)
                    continue;
                if (!e.second->get_group().empty())
                    if (!active_group.empty())
                        if (e.second->get_group() != active_group || e.second->get_group().empty())
                            continue;
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
            if (!e.second)
                continue;
            if (!e.second->get_group().empty())
                if (!active_group.empty())
                    if (e.second->get_group() != active_group || e.second->get_group().empty())
                        continue;
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
