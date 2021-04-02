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
    BUTTON = 0,
    LABEL
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

    FUI_Window* overlapping_window;

    enum class button_state
    {
        NORMAL = 0,
        HOVER,
        CLICK
    };

    button_state state = button_state::NORMAL;

    bool is_dragging = false;

    bool focused = false;

    bool should_render = true;

    std::string identifier;
    
    int top_border_thickness = 20;
    int border_thickness = 5;

public:
    FUI_Window(olc::PixelGameEngine* pge, std::string identifier, olc::vi2d position, olc::vi2d size, std::string title);

    void draw();

    void input(std::deque<FUI_Window*> windows);

    olc::vi2d get_position() { return position; }

    olc::vi2d get_size() { return size; }

    olc::vi2d get_window_space() { return olc::vi2d(size.x - border_thickness * 2, size.y - top_border_thickness); }

    std::string get_id() { return identifier; }

    int get_top_border_thickness() { return top_border_thickness; }

    int get_border_thickness() { return border_thickness; }

    void set_background_color(olc::Pixel color) { background_color = color; };

    void set_border_color(olc::Pixel color) { border_color = color; }

    void set_top_border_thickness(int thickness) { top_border_thickness = thickness; }

    void set_border_thickness(int thickness) { border_thickness = thickness; }

    void close_window(bool close) { should_render = !close; }

    bool get_closed_state() { return should_render; }

    void change_position(olc::vi2d pos) { position = pos; }

    void change_size(olc::vi2d s) { size = s; }

    void set_focused(bool state) { focused = state; }

    bool is_focused() { return focused; }
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
    pge->FillRectDecal(position, olc::vf2d(border_thickness, size.y), border_color); // Left side
    pge->FillRectDecal(olc::vf2d(position.x + size.x - border_thickness, position.y), olc::vf2d(border_thickness, size.y), border_color); // Right side
    pge->FillRectDecal(olc::vf2d(position.x, position.y + size.y - border_thickness), olc::vf2d(size.x, border_thickness), border_color); // Bottom side
    pge->FillRectDecal(position, olc::vf2d(size.x, top_border_thickness), border_color); // Top bar

    // Draw the window title
    olc::vf2d title_position = olc::vf2d(position.x + (size.x / 2) - (pge->GetTextSize(title).x / 2), position.y + (top_border_thickness / 2) - (pge->GetTextSize(title).y / 2));
    pge->DrawStringDecal(title_position, title, olc::BLACK);

    // Draw the default window close button
    olc::vi2d temp_pos = { position.x + size.x - (size.x / 10), position.y };
    olc::vi2d temp_size = { size.x / 10, top_border_thickness };
    switch (state)
    {
    case button_state::NORMAL:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.button_normal);
        break;
    case button_state::HOVER:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.button_hover);
        break;
    case button_state::CLICK:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.button_click);
        break;
    }
    olc::vf2d close_position = olc::vf2d(temp_pos.x + (temp_size.x / 2) - (pge->GetTextSize("X").x / 2), temp_pos.y + (top_border_thickness / 2) - (pge->GetTextSize("X").y / 2));
    pge->DrawStringDecal(close_position, "X", olc::BLACK);

    // Override top border with a darker color when window is inactive 
    if (!focused)
        pge->FillRectDecal(position, olc::vf2d(size.x, top_border_thickness), { 100, 100, 100, 150 }); // Top bar
}

void FUI_Window::input(std::deque<FUI_Window*> windows)
{
    for (auto& window : windows)
    {
        if (window->get_id() != identifier)
        {
            if (window->is_focused())
            {
                if (position.x + size.x > window->get_position().x&& position.x < window->get_position().x + window->get_size().x &&
                    position.y + size.y > window->get_position().y&& position.y < window->get_position().y + window->get_size().y)
                {
                    overlapping_window = window;
                    break;
                }
                else
                    overlapping_window = nullptr;
            }
        }
    }

    olc::vi2d new_window_position = position;
    // input on default close button
    if ((pge->GetMousePos().x >= position.x + size.x - (size.x / 10) && pge->GetMousePos().x <= position.x + size.x &&
        pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + top_border_thickness))
    {
        if (pge->GetMouse(0).bHeld || pge->GetMouse(0).bPressed || pge->GetMouse(0).bReleased )
        {
            if (pge->GetMouse(0).bReleased && focused)
                close_window(true);
            state = button_state::CLICK;
        }
        else
            state = button_state::HOVER;
    }
    else
        state = button_state::NORMAL;

    if ((pge->GetMousePos().x >= position.x && pge->GetMousePos().x <= position.x + size.x - (size.x / 10) &&
        pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + top_border_thickness) || is_dragging)
    {
        if (pge->GetMouse(0).bPressed)
        {
            is_dragging = true;
            mouse_difference = pge->GetMousePos() - position;
        }

        if (pge->GetMouse(0).bHeld && is_dragging && focused)
            new_window_position = pge->GetMousePos() - mouse_difference;


        // clamp window to not go out of screen
        if (!(new_window_position.x <= 0 || new_window_position.x + size.x >= pge->GetWindowSize().x))
            position.x = new_window_position.x;
        else
            mouse_difference = pge->GetMousePos() - position;
        if (!(new_window_position.y <= 0 || new_window_position.y + size.y >= pge->GetWindowSize().y))
            position.y = new_window_position.y;
        else
            mouse_difference = pge->GetMousePos() - position;
    }

    if (pge->GetMouse(0).bReleased)
        is_dragging = false;

    if (overlapping_window)
    {
        if (!((pge->GetMousePos().x >= overlapping_window->get_position().x && pge->GetMousePos().x <= overlapping_window->get_position().x + overlapping_window->get_size().x &&
            pge->GetMousePos().y >= overlapping_window->get_position().y && pge->GetMousePos().y <= overlapping_window->get_position().y + overlapping_window->get_size().y) &&
            pge->GetMouse(0).bPressed))
        {
            if ((pge->GetMousePos().x >= position.x && pge->GetMousePos().x <= position.x + size.x &&
                pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + size.y) && pge->GetMouse(0).bPressed)
            {
                overlapping_window->set_focused(false);
                focused = true;
            }
            else if (pge->GetMouse(0).bPressed)
                focused = false;
        }
    }
    else
    {
        if ((pge->GetMousePos().x >= position.x && pge->GetMousePos().x <= position.x + size.x &&
            pge->GetMousePos().y >= position.y && pge->GetMousePos().y <= position.y + size.y) && pge->GetMouse(0).bPressed)
        {
            focused = true;
        }
        else if (pge->GetMouse(0).bPressed)
            focused = false;
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
    std::string group;
    olc::vf2d text_scale = { 1.0f, 1.0f };

    bool centered = false;
    
    olc::Pixel text_color = olc::WHITE;

    std::string identifier;

    virtual void draw(olc::PixelGameEngine* pge) {}

    virtual void input(olc::PixelGameEngine* pge) {}

    void set_size(olc::vi2d s) { size = s; }

    void set_position(olc::vi2d p) { position = p; }

    void set_text(std::string txt) { text = txt; }

    void set_text_color(olc::Pixel color) { text_color = color; }

    std::string get_group() { return group;  }

    void set_centered(bool center) { centered = center; }

    void scale_text(olc::vf2d scale) { text_scale = scale; }
};

/*
####################################################
################FUI_LABEL START#####################
####################################################
*/

class FUI_Label : public FUI_Element
{
public:
    FUI_Label(std::string id, FUI_Window* parent, std::string text, olc::vi2d position);
    FUI_Label(std::string id, FUI_Window* parent, std::string group, std::string text, olc::vi2d position);
    FUI_Label(std::string id, std::string group, std::string text, olc::vi2d position);
    FUI_Label(std::string id, std::string text, olc::vi2d position);

    void draw(olc::PixelGameEngine* pge) override;
};

FUI_Label::FUI_Label(std::string id, FUI_Window* pt, std::string t, olc::vi2d p)
{
    identifier = id;
    parent = pt;
    text = t;
    position = p;
}
FUI_Label::FUI_Label(std::string id, FUI_Window* pt, std::string g, std::string t, olc::vi2d p)
{
    identifier = id;
    parent = pt;
    text = t;
    position = p;
    group = g;
}
FUI_Label::FUI_Label(std::string id, std::string g, std::string t, olc::vi2d p)
{
    identifier = id;
    text = t;
    position = p;
    group = g;
}
FUI_Label::FUI_Label(std::string id, std::string t, olc::vi2d p)
{
    identifier = id;
    text = t;
    position = p;
}

void FUI_Label::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    olc::vf2d temp = { adaptive_position.x + position.x - ((pge->GetTextSize(text).x / 2) * text_scale.x),
                       adaptive_position.y + position.y - ((pge->GetTextSize(text).y / 2) * text_scale.y) };

    if (centered)
        pge->DrawStringDecal(temp, text, text_color, text_scale);
    else
        pge->DrawStringDecal(adaptive_position + position, text, text_color, text_scale);
}

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
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
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
    pge->DrawStringDecal(text_position, text, text_color, text_scale);
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
    std::deque<FUI_Window*> windows;
    std::vector<std::string> groups;
    std::string active_window_id;
    std::string active_group;
    std::deque<std::pair<FUI_Type, std::shared_ptr<FUI_Element>>> elements;

    void draw();

    void push_focused_to_back()
    {
        int i = 0;
        for (auto& window : windows)
        {
            if (!window->get_closed_state())
            {
                i++;
                continue;
            }
            if (window->is_focused())
            {
                windows.push_back(window);
                windows.erase(windows.begin() + i);
            }
            i++;
        }
    }
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
    //this, "new_window", { 520, 25 }, { 490, 250 }, "New Window"
    FUI_Window* create_window(std::string identifier, olc::vi2d position, olc::vi2d size, std::string title)
    {
        bool is_duplicate = false;
        FUI_Window* temp_window = nullptr;
        for (auto& window : windows)
        {
            if (window->get_id() == identifier)
                is_duplicate = true;
        }
        if (!is_duplicate)
        {
            windows.push_back(new FUI_Window{ pge, identifier, position, size, title });
            temp_window = windows.back();
        }
        else
            std::cout << "Cannot add duplicates of same window (function affected: create_window, affected window_id: " + identifier + ")\n";

        if (windows.size() == 1)
            windows.back()->set_focused(true);

        return temp_window;
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

    void add_label(std::string parent_id, std::string identifier, std::string text, olc::vi2d position);

    void add_label(std::string identifier, std::string text, olc::vi2d position);

    FUI_Window* find_window(std::string identifier)
    {
        for (auto& window : windows)
        {
            if (window->get_id() == identifier)
                return window;
        }
        std::cout << "Could not find the window ID in added windows (function affected: find_window, affected window_id: " + identifier + ")\n";
        return nullptr;
    }

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

void olcPGEX_FrostUI::add_label(std::string parent_id, std::string identifier, std::string text, olc::vi2d position)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, window, text, position)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, window, active_group, text, position)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_label, label_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_label, label_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_label, label_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_label(std::string identifier, std::string text, olc::vi2d position)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, window, active_group, text, position)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, window, text, position)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, active_group, text, position)));
            else
                elements.push_back(std::make_pair(FUI_Type::LABEL, std::make_shared<FUI_Label>(identifier, text, position)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_label, label_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_button(std::string parent_id, std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
                    else
                        elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, active_group, text, position, size, callback)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_button, button_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_button, button_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_button, label_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_button(std::string identifier, std::string text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, active_group, text, position, size, callback)));
                    else
                        elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, window, text, position, size, callback)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, active_group, text, position, size, callback)));
            else
                elements.push_front(std::make_pair(FUI_Type::BUTTON, std::make_shared<FUI_Button>(identifier, text, position, size, callback)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_button, label_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::draw()
{
    push_focused_to_back();
    // Draw windows first
    if (windows.size() > 0)
    {
        for (auto& window : windows)
        {
            if (!window->get_closed_state())
            {
                if (window->is_focused())
                    window->set_focused(false);
                continue;
            }
            
            window->input(windows);
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
                        if (window->is_focused())
                            e.second->input(pge);
                    }
                    else
                        continue;
                }
                else
                {
                    e.second->draw(pge);
                    if (window->is_focused())
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