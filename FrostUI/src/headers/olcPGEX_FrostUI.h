/*
    olcPGEX_FrostUI.h

    +-------------------------------------------------------------+
    |         OneLoneCoder Pixel Game Engine Extension            |
    |                FrostUI - v1.0.0			              |
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
#ifndef OLC_PGEX_FROSTUI
#define OLC_PGEX_FROSTUI
#include <deque>

struct FUI_Colors
{
    // window colors
    olc::Pixel window_border_color = olc::GREY;
    olc::Pixel window_background_color = olc::WHITE;
    // window exit button colors
    olc::Pixel exit_button_normal = olc::GREY;
    olc::Pixel exit_button_hover = { 150, 150, 150 };
    olc::Pixel exit_button_click = { 100, 100, 100 };
    // button colors
    olc::Pixel button_normal = olc::GREY;
    olc::Pixel button_hover = { 150, 150, 150 };
    olc::Pixel button_click = { 100, 100, 100 };
    // checkbox colors
    olc::Pixel checkbox_normal = olc::GREY;
    olc::Pixel checkbox_hover = { 150, 150, 150 };
    olc::Pixel checkbox_active = { 100, 100, 100 };
    // dropdown colors
    olc::Pixel dropdown_normal = olc::GREY;
    olc::Pixel dropdown_hover = { 150, 150, 150 };
    olc::Pixel dropdown_active = { 100, 100, 100 };
    // combolist colors
    olc::Pixel combolist_normal = olc::GREY;
    olc::Pixel combolist_hover = { 150, 150, 150 };
    olc::Pixel combolist_active = { 100, 100, 100 };
    // combolist colors
    olc::Pixel groupbox_outline = olc::GREY;
    olc::Pixel groupbox_background = { 225, 225, 225 };
    // slider colors
    olc::Pixel slider_outline = olc::BLACK;
    olc::Pixel slider_normal = { 150, 150, 150 };
    olc::Pixel slider_hover = { 100, 100, 100 };
};

FUI_Colors color_scheme;

enum class FUI_Type
{
    BUTTON = 0,
    LABEL,
    CHECKBOX,
    DROPDOWN,
    COMBOLIST,
    GROUPBOX,
    SLIDER
};

std::string to_string_with_precision(const float a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

olc::vf2d auto_scaling(olc::vf2d text_size, olc::vf2d text_scale, olc::vf2d element_size)
{
    while ((text_size.y * text_scale.y) < element_size.y)
    {
        text_scale.y += 0.001;
    }
    while ((text_size.x * text_scale.x) < element_size.x)
    {
        text_scale.x += 0.001;
    }
    return text_scale;
}

class FUI_Window
{
private:
    olc::PixelGameEngine* pge;

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
    FUI_Window(olc::PixelGameEngine* pge, const std::string& identifier, olc::vi2d position, olc::vi2d size, const std::string& title);

    void draw();

    void input(std::deque<FUI_Window*> windows);

    olc::vi2d get_position() const { return position; }

    olc::vi2d get_size() const { return size; }

    olc::vi2d get_window_space() const { return olc::vi2d(size.x - border_thickness * 2, size.y - top_border_thickness); }

    std::string get_id() const { return identifier; }

    int get_top_border_thickness() const { return top_border_thickness; }

    int get_border_thickness() const { return border_thickness; }

    void set_top_border_thickness(int thickness) { top_border_thickness = thickness; }

    void set_border_thickness(int thickness) { border_thickness = thickness; }

    void close_window(bool close) { should_render = !close; }

    bool get_closed_state() const { return !should_render; }

    void change_position(olc::vi2d pos) { position = pos; }

    void change_size(olc::vi2d s) { size = s; }

    void set_focused(bool state) { focused = state; }

    bool is_focused() const { return focused; }
};

FUI_Window::FUI_Window(olc::PixelGameEngine* p, const std::string& id, olc::vi2d pos, olc::vi2d s, const std::string& txt)
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
    pge->FillRectDecal(position, size, color_scheme.window_background_color);

    // Draw the window border
    pge->FillRectDecal(position, olc::vf2d(border_thickness, size.y), color_scheme.window_border_color); // Left side
    pge->FillRectDecal(olc::vf2d(position.x + size.x - border_thickness, position.y), olc::vf2d(border_thickness, size.y), color_scheme.window_border_color); // Right side
    pge->FillRectDecal(olc::vf2d(position.x, position.y + size.y - border_thickness), olc::vf2d(size.x, border_thickness), color_scheme.window_border_color); // Bottom side
    pge->FillRectDecal(position, olc::vf2d(size.x, top_border_thickness), color_scheme.window_border_color); // Top bar

    // Draw the window title
    olc::vf2d title_position = olc::vf2d(position.x + (size.x / 2) - (pge->GetTextSizeProp(title).x / 2), position.y + (top_border_thickness / 2) - (pge->GetTextSizeProp(title).y / 2));
    pge->DrawStringPropDecal(title_position, title, olc::BLACK);

    // Draw the default window close button
    olc::vi2d temp_pos = { position.x + size.x - (size.x / 10), position.y };
    olc::vi2d temp_size = { size.x / 10, top_border_thickness };
    switch (state)
    {
    case button_state::NORMAL:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.exit_button_normal);
        break;
    case button_state::HOVER:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.exit_button_hover);
        break;
    case button_state::CLICK:
        pge->FillRectDecal(temp_pos, temp_size, color_scheme.exit_button_click);
        break;
    }
    olc::vf2d close_position = olc::vf2d(temp_pos.x + (temp_size.x / 2) - (pge->GetTextSizeProp("X").x / 2), temp_pos.y + (top_border_thickness / 2) - (pge->GetTextSizeProp("X").y / 2));
    pge->DrawStringPropDecal(close_position, "X", olc::BLACK);

    // Override top border with a darker color when window is inactive 
    if (!focused)
        pge->FillRectDecal(position, olc::vf2d(size.x, top_border_thickness), { 100, 100, 100, 150 }); // Top bar
}

void FUI_Window::input(std::deque<FUI_Window*> windows)
{
    overlapping_window = nullptr;
    for (auto& window : windows)
    {
        if (window->get_closed_state())
            continue;
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


        position = new_window_position;
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

enum class DropdownState
{
    NONE = 0,
    HOVER,
    ACTIVE
};

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
    olc::vf2d adaptive_position;
    std::string text;
    std::string group;
    olc::vf2d text_scale = { 1.0f, 1.0f };
    FUI_Type ui_type;

    float slider_value = 0.f;
    float* slier_value_holder = nullptr;
    olc::vf2d range;

    std::string checkbox_orientation = "left";
    int checkbox_padding = 5;
    bool centered = false;
    bool* toggle_button_state = nullptr;

    bool is_focused = false;

    std::vector<std::pair<DropdownState, std::pair<olc::vf2d, std::string>>> elements;
    std::pair<olc::vf2d, std::string> selected_element;
    std::vector<std::pair<olc::vf2d, std::string>> selected_elements;
    std::vector<std::string> return_selected_items;
    float animation_speed = 150.0f;

    olc::Pixel text_color = olc::WHITE;

    std::string identifier;

    virtual void draw(olc::PixelGameEngine* pge) {}

    virtual void input(olc::PixelGameEngine* pge) {}

    void set_size(olc::vi2d s) { size = s; }

    void set_position(olc::vi2d p) { position = p; }

    void set_text(const std::string& txt) { text = txt; }

    void set_text_color(olc::Pixel color) { text_color = color; }

    std::string get_group() const { return group; }

    void set_centered(bool center) { if (ui_type == FUI_Type::LABEL) centered = center; else std::cout << "Trying to set_centered on wrong UI_TYPE\n"; }

    void scale_text(olc::vf2d scale) { text_scale = scale; }

    void set_checkbox_orientation(std::string orientation)
    {
        if (ui_type == FUI_Type::CHECKBOX)
            if (orientation == "left" || orientation == "right")
                checkbox_orientation = orientation;
            else
                std::cout << "orientation '" + orientation + "' not found, orientations are 'left' and 'right' (function affected: set_checkbox_orientation, affected checkbox_id: " + identifier + ")\n";
    }

    void set_checkbox_padding(int padding) { if (ui_type == FUI_Type::CHECKBOX) checkbox_padding = padding; else std::cout << "Trying to set padding on wrong UI_TYPE\n"; }

    void make_toggleable(bool* state) { if (ui_type == FUI_Type::BUTTON) toggle_button_state = state; else std::cout << "Trying to make_toggleable on incorrect UI_TYPE\n"; }

    void add_item(const std::string& item, olc::vf2d scale = { 1.0f, 1.0f }) { if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST)  elements.push_back(std::make_pair(DropdownState::NONE, std::make_pair(scale, item))); else std::cout << "Trying to add_item to wrong UI_TYPE\n"; }
    
    void set_animation_speed(float speed) { if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST) animation_speed = speed; else std::cout << "Trying to set animation speed on wrong UI_TYPE\n"; }

    std::string get_selected_item() { if (ui_type == FUI_Type::DROPDOWN) return selected_element.second; else std::cout << "Trying to set animation speed on wrong UI_TYPE\n"; }

    std::vector<std::string> get_selected_items()
    {
        if (ui_type == FUI_Type::COMBOLIST)
        {
            return_selected_items.clear();
            for (auto& item : selected_elements)
                return_selected_items.push_back(item.second);

            return return_selected_items;
        }
        else std::cout << "Trying to retrieve selected items on wrong UI_TYPE\n";
    }

    const olc::vi2d get_position() const { return position; }

    void set_slider_value(float value) { if (ui_type == FUI_Type::SLIDER) slider_value = value; }

    const float get_slider_value() const { if (ui_type == FUI_Type::SLIDER) return slider_value; }
};

/*
####################################################
################FUI_LABEL START#####################
####################################################
*/

class FUI_Label : public FUI_Element
{
public:
    FUI_Label(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position);
    FUI_Label(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position);
    FUI_Label(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position);
    FUI_Label(const std::string& id, const std::string& text, olc::vi2d position);

    void draw(olc::PixelGameEngine* pge) override;
};

FUI_Label::FUI_Label(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p)
{
    identifier = id;
    parent = pt;
    text = t;
    position = p;
    ui_type = FUI_Type::LABEL;
}
FUI_Label::FUI_Label(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p)
{
    identifier = id;
    parent = pt;
    text = t;
    position = p;
    group = g;
    ui_type = FUI_Type::LABEL;
}
FUI_Label::FUI_Label(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p)
{
    identifier = id;
    text = t;
    position = p;
    group = g;
    ui_type = FUI_Type::LABEL;
}
FUI_Label::FUI_Label(const std::string& id, const std::string& t, olc::vi2d p)
{
    identifier = id;
    text = t;
    position = p;
    ui_type = FUI_Type::LABEL;
}

void FUI_Label::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    olc::vf2d temp = { adaptive_position.x + position.x - ((pge->GetTextSizeProp(text).x * text_scale.x) / 2),
                       adaptive_position.y + position.y - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2) };

    if (centered)
        pge->DrawStringPropDecal(temp, text, text_color, text_scale);
    else
        pge->DrawStringPropDecal(adaptive_position + position, text, text_color, text_scale);
}

/*
####################################################
################FUI_BUTTON START####################
####################################################
*/
class FUI_Button : public FUI_Element
{
private:
    enum class State
    {
        NONE = 0,
        HOVER,
        CLICK
    };

    std::function<void()> callback;
    State state = State::NONE;

public:
    FUI_Button(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
    FUI_Button(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Button::FUI_Button(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    callback = cb;
    ui_type = FUI_Type::BUTTON;
}

FUI_Button::FUI_Button(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    callback = cb;
    ui_type = FUI_Type::BUTTON;
}

FUI_Button::FUI_Button(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    callback = cb;
    group = g;
    ui_type = FUI_Type::BUTTON;
}

FUI_Button::FUI_Button(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, std::function<void()> cb)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    callback = cb;
    group = g;
    ui_type = FUI_Type::BUTTON;
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
    case State::NONE:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_normal);
        break;
    case State::HOVER:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_hover);
        break;
    case State::CLICK:
        pge->FillRectDecal(adaptive_position + position, size, color_scheme.button_click);
        break;
    }
    // Draw the text
    olc::vf2d text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(text).x * text_scale.x) / 2),
                                        adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2));
    pge->DrawStringPropDecal(text_position, text, text_color, text_scale);
}

void FUI_Button::input(olc::PixelGameEngine* pge)
{
    if (!toggle_button_state)
    {
        if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
            pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
            pge->GetMousePos().y >= adaptive_position.y + position.y &&
            pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
        {
            if (pge->GetMouse(0).bPressed)
                callback();
            else
                state = State::HOVER;
        }
        else
            state = State::NONE;
    }
    else
    {
        if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
            pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
            pge->GetMousePos().y >= adaptive_position.y + position.y &&
            pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
        {
            if (pge->GetMouse(0).bPressed)
            {
                if (state == State::CLICK)
                        state = State::NONE;
                else
                    state = State::CLICK;
            }
            else if (state != State::CLICK)
                state = State::HOVER;
        }
        else if (state != State::CLICK)
            state = State::NONE;

        if (state == State::CLICK)
            *toggle_button_state = true;
        else
            *toggle_button_state = false;
    }
}

/*
####################################################
################FUI_CHECKBOX START##################
####################################################
*/
class FUI_Checkbox : public FUI_Element
{
private:
    enum class State
    {
        NONE = 0,
        HOVER,
        ACTIVE
    };

    olc::vf2d checkbox_position;
    bool* checkbox_state;
    State state = State::NONE;
public:
    FUI_Checkbox(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
    FUI_Checkbox(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
    FUI_Checkbox(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
    FUI_Checkbox(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Checkbox::FUI_Checkbox(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s, bool* cb_state)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    ui_type = FUI_Type::CHECKBOX;
    checkbox_state = cb_state;
}

FUI_Checkbox::FUI_Checkbox(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s, bool* cb_state)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    ui_type = FUI_Type::CHECKBOX;
    checkbox_state = cb_state;
}

FUI_Checkbox::FUI_Checkbox(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, bool* cb_state)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    group = g;
    ui_type = FUI_Type::CHECKBOX;
    checkbox_state = cb_state;
}

FUI_Checkbox::FUI_Checkbox(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, bool* cb_state)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    group = g;
    ui_type = FUI_Type::CHECKBOX;
    checkbox_state = cb_state;
}

void FUI_Checkbox::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    checkbox_position = adaptive_position + position;

    // Draw the text
    olc::vf2d text_position = adaptive_position;
    if (checkbox_orientation == "left")
    {
        checkbox_position = olc::vf2d(adaptive_position.x + position.x + pge->GetTextSizeProp(text).x + checkbox_padding, adaptive_position.y + position.y);
        text_position = olc::vf2d(adaptive_position.x + position.x,
            adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2));
        pge->FillRectDecal(checkbox_position, size, color_scheme.checkbox_normal);
    }
    else if (checkbox_orientation == "right")
    {
        text_position = olc::vf2d(adaptive_position.x + position.x + size.x + checkbox_padding,
            adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2));
        pge->FillRectDecal(checkbox_position, size, color_scheme.checkbox_normal);
    }
    pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

    olc::vf2d checkbox_filling = olc::vf2d(1.0f, 1.0f);
    // Draw the body of the checkbox
    switch (state)
    {
    case State::NONE:
        *checkbox_state = false;
        break;
    case State::HOVER:
        *checkbox_state = false;
        pge->FillRectDecal(checkbox_position + checkbox_filling, 
                          { static_cast<float>(size.x) - 2.0f, static_cast<float>(size.y) - 2.0f }, color_scheme.checkbox_hover);
        break;
    case State::ACTIVE:
        *checkbox_state = true;
        pge->FillRectDecal(checkbox_position + checkbox_filling,
                          { static_cast<float>(size.x) - 2.0f, static_cast<float>(size.y) - 2.0f }, color_scheme.checkbox_active);
        break;
    }
}

void FUI_Checkbox::input(olc::PixelGameEngine* pge)
{
    if (pge->GetMousePos().x >= checkbox_position.x &&
        pge->GetMousePos().x <= checkbox_position.x + size.x &&
        pge->GetMousePos().y >= checkbox_position.y &&
        pge->GetMousePos().y <= checkbox_position.y + size.y)
    {
        if (pge->GetMouse(0).bPressed)
        {
            if (state == State::ACTIVE)
                state = State::NONE;
            else
                state = State::ACTIVE;
        }
        else if (state != State::ACTIVE)
            state = State::HOVER;
    }
    else if (state != State::ACTIVE)
        state = State::NONE;
}

/*
####################################################
################FUI_DROPDOWN START##################
####################################################
*/
class FUI_Dropdown : public FUI_Element
{
private:
    olc::vf2d active_size = olc::vf2d(0, 0);
    DropdownState state = DropdownState::NONE;
    bool is_open = false;
public:
    FUI_Dropdown(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Dropdown(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Dropdown(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Dropdown(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Dropdown::FUI_Dropdown(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    ui_type = FUI_Type::DROPDOWN;
}

FUI_Dropdown::FUI_Dropdown(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    ui_type = FUI_Type::DROPDOWN;
}

FUI_Dropdown::FUI_Dropdown(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    group = g;
    ui_type = FUI_Type::DROPDOWN;
}

FUI_Dropdown::FUI_Dropdown(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    group = g;
    ui_type = FUI_Type::DROPDOWN;
}

void FUI_Dropdown::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    if (is_open)
    {
        float future_y = size.y * elements.size();
        active_size.y += animation_speed * pge->GetElapsedTime();
        if (active_size.y >= future_y)
            active_size.y = future_y;
    }
    else
    {
        active_size.y -= animation_speed * pge->GetElapsedTime();
        if (active_size.y <= 0)
            active_size.y = 0;
    }

    // title position
    olc::vf2d text_position = olc::vf2d(adaptive_position.x + position.x - (pge->GetTextSizeProp(text).x * text_scale.x),
        adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2));
    pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

    switch (state)
    {
    case DropdownState::NONE:
        pge->FillRectDecal(position + adaptive_position, size, color_scheme.dropdown_normal);
        break;
    case DropdownState::HOVER:
        pge->FillRectDecal(position + adaptive_position, size, color_scheme.dropdown_hover);
        break;
    }
    if (active_size.y != size.y * elements.size())
        pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y), olc::vf2d(size.x, active_size.y), color_scheme.dropdown_normal);

    if (!selected_element.second.empty())
    {
        text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(selected_element.second).x * selected_element.first.x) / 2),
            adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(selected_element.second).y * selected_element.first.y) / 2));
        pge->DrawStringPropDecal(text_position, selected_element.second, text_color, selected_element.first);
    }

    int i = 1;
    for (auto& element : elements)
    {
        if (active_size.y >= size.y * i)
        {
            switch (element.first)
            {
            case DropdownState::NONE:
                pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y * i), size, color_scheme.dropdown_normal);
                break;
            case DropdownState::HOVER:
                pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y * i), size, color_scheme.dropdown_hover);
                break;
            }
        }
        text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(element.second.second).x * element.second.first.x) / 2),
            adaptive_position.y + position.y + size.y + (size.y * i) - (size.y / 2) - ((pge->GetTextSizeProp(element.second.second).y * element.second.first.y) / 2));
        if (adaptive_position.y + position.y + size.y + active_size.y > text_position.y + (pge->GetTextSizeProp(element.second.second).y + element.second.first.y))
            pge->DrawStringPropDecal(text_position, element.second.second, text_color, element.second.first);
        i++;
    }
}

void FUI_Dropdown::input(olc::PixelGameEngine* pge)
{
    bool could_close = false;
    if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
        pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
        pge->GetMousePos().y >= adaptive_position.y + position.y &&
        pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
    {
        if (pge->GetMouse(1).bPressed)
            selected_element.second.clear();

        if (pge->GetMouse(0).bPressed)
        {
            if (is_open)
                is_open = false;
            else
                is_open = true;
        }
        else
            state = DropdownState::HOVER;
    }
    else
    {
        state = DropdownState::NONE;
        if (pge->GetMouse(0).bPressed)
            could_close = true;
    }


    if (is_open)
    {
        int i = 1;
        for (auto& element : elements)
        {
            if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
                pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
                pge->GetMousePos().y >= adaptive_position.y + position.y + (size.y * i) &&
                pge->GetMousePos().y <= adaptive_position.y + position.y + (size.y * i) + size.y)
            {
                if (pge->GetMouse(0).bPressed)
                {
                    selected_element = std::make_pair(element.second.first, element.second.second);
                    is_open = false;
                }
                else
                    element.first = DropdownState::HOVER;
            }
            else
            {
                element.first = DropdownState::NONE;
                if (could_close && pge->GetMouse(0).bPressed)
                    is_open = false;
            }
            i++;
        }
    }

    if (is_open)
        is_focused = true;
    else
        is_focused = false;
}

/*
####################################################
################FUI_COMBOLIST START#################
####################################################
*/
class FUI_Combolist : public FUI_Element
{
private:
    olc::vf2d active_size = olc::vf2d(0, 0);
    DropdownState state = DropdownState::NONE;
    bool is_open = false;
public:
    FUI_Combolist(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Combolist(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Combolist(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Combolist(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Combolist::FUI_Combolist(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    ui_type = FUI_Type::COMBOLIST;
}

FUI_Combolist::FUI_Combolist(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    ui_type = FUI_Type::COMBOLIST;
}

FUI_Combolist::FUI_Combolist(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    group = g;
    ui_type = FUI_Type::COMBOLIST;
}

FUI_Combolist::FUI_Combolist(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    group = g;
    ui_type = FUI_Type::COMBOLIST;
}

void FUI_Combolist::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    if (is_open)
    {
        float future_y = size.y * elements.size();
        active_size.y += animation_speed * pge->GetElapsedTime();
        if (active_size.y >= future_y)
            active_size.y = future_y;
    }
    else
    {
        active_size.y -= animation_speed * pge->GetElapsedTime();
        if (active_size.y <= 0)
            active_size.y = 0;
    }
    
    // title position
    olc::vf2d text_position = olc::vf2d(adaptive_position.x + position.x - (pge->GetTextSizeProp(text).x * text_scale.x),
        adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2));
    pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

    switch (state)
    {
    case DropdownState::NONE:
        pge->FillRectDecal(position + adaptive_position, size, color_scheme.dropdown_normal);
        break;
    case DropdownState::HOVER:
        pge->FillRectDecal(position + adaptive_position, size, color_scheme.dropdown_hover);
        break;
    }
    if (active_size.y != size.y * elements.size())
        pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y), olc::vf2d(size.x, active_size.y), color_scheme.dropdown_normal);

    if (selected_elements.size() > 1)
    {
        std::string temp_text = selected_elements[0].second + ", ...";
        text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(temp_text).x * selected_elements[0].first.x) / 2),
            adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(temp_text).y * selected_elements[0].first.y) / 2));
        pge->DrawStringPropDecal(text_position, temp_text, text_color, selected_elements[0].first);
    }
    else if (selected_elements.size() > 0)
    {
        text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(selected_elements[0].second).x * selected_elements[0].first.x) / 2),
            adaptive_position.y + position.y + (size.y / 2) - ((pge->GetTextSizeProp(selected_elements[0].second).y * selected_elements[0].first.y) / 2));
        pge->DrawStringPropDecal(text_position, selected_elements[0].second, text_color, selected_elements[0].first);
    }

    int i = 1;
    for (auto& element : elements)
    {
        if (active_size.y >= size.y * i)
        {
            switch (element.first)
            {
            case DropdownState::NONE:
                pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y * i), size, color_scheme.combolist_normal);
                break;
            case DropdownState::HOVER:
                pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y * i), size, color_scheme.combolist_hover);
                break;
            case DropdownState::ACTIVE:
                pge->FillRectDecal(position + adaptive_position + olc::vf2d(0, size.y * i), size, color_scheme.combolist_active);
                break;
            }
        }
        text_position = olc::vf2d(adaptive_position.x + position.x + (size.x / 2) - ((pge->GetTextSizeProp(element.second.second).x * element.second.first.x) / 2),
            adaptive_position.y + position.y + size.y + (size.y * i) - (size.y / 2) - ((pge->GetTextSizeProp(element.second.second).y * element.second.first.y) / 2));
        if (adaptive_position.y + position.y + size.y + active_size.y > text_position.y + (pge->GetTextSizeProp(element.second.second).y + element.second.first.y))
            pge->DrawStringPropDecal(text_position, element.second.second, text_color, element.second.first);
        i++;
    }
}

void FUI_Combolist::input(olc::PixelGameEngine* pge)
{
    if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
        pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
        pge->GetMousePos().y >= adaptive_position.y + position.y &&
        pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
    {
        if (pge->GetMouse(1).bPressed)
        {
            selected_elements.clear();
            for (auto& element : elements)
                element.first = DropdownState::NONE;
        }

        if (pge->GetMouse(0).bPressed)
        {
            if (is_open)
                is_open = false;
            else
                is_open = true;
        }
        else
            state = DropdownState::HOVER;
    }
    else
        state = DropdownState::NONE;


    if (is_open)
    {
        int i = 1;
        for (auto& element : elements)
        {
            if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
                pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
                pge->GetMousePos().y >= adaptive_position.y + position.y + (size.y * i) &&
                pge->GetMousePos().y <= adaptive_position.y + position.y + (size.y * i) + size.y)
            {
                if (pge->GetMouse(0).bPressed)
                {
                    bool did_find_element = false;
                    for (auto& sel_element : selected_elements)
                    {
                        if (sel_element.second == element.second.second)
                        {
                            did_find_element = true;
                            int j = 0;
                            for (auto& el : selected_elements)
                            {
                                if (el.second == element.second.second)
                                {
                                    element.first = DropdownState::NONE;
                                    selected_elements.erase(selected_elements.begin() + j);
                                    break;
                                }
                                j++;
                            }
                            break;
                        }
                    }
                    if (!did_find_element)
                    {
                        element.first = DropdownState::ACTIVE;
                        selected_elements.push_back(std::make_pair(element.second.first, element.second.second));
                    }
                }
                else if (element.first != DropdownState::ACTIVE)
                    element.first = DropdownState::HOVER;
            }
            else if (element.first != DropdownState::ACTIVE)
                element.first = DropdownState::NONE;
            i++;
        }
    }
    
    if (!(pge->GetMousePos().x >= adaptive_position.x + position.x &&
        pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
        pge->GetMousePos().y >= adaptive_position.y + position.y &&
        pge->GetMousePos().y <= adaptive_position.y + position.y + size.y + active_size.y) && pge->GetMouse(0).bPressed)
        is_open = false;
       
    if (is_open)
        is_focused = true;
    else
        is_focused = false;
}

/*
####################################################
################FUI_GROUPBOX START##################
####################################################
*/
class FUI_Groupbox : public FUI_Element
{
public:
    FUI_Groupbox(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Groupbox(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Groupbox(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
    FUI_Groupbox(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override {};
};

FUI_Groupbox::FUI_Groupbox(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    ui_type = FUI_Type::GROUPBOX;
}

FUI_Groupbox::FUI_Groupbox(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    ui_type = FUI_Type::GROUPBOX;
}

FUI_Groupbox::FUI_Groupbox(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    group = g;
    ui_type = FUI_Type::GROUPBOX;
}

FUI_Groupbox::FUI_Groupbox(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    group = g;
    ui_type = FUI_Type::GROUPBOX;
}

void FUI_Groupbox::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);

    auto line_position = position + adaptive_position;
    pge->FillRectDecal(line_position, size, color_scheme.groupbox_background);
    // top left outline
    pge->FillRectDecal(line_position, olc::vf2d((size.x / 2) - (pge->GetTextSizeProp(text).x / 2), 1), color_scheme.groupbox_outline);
    // top right outline
    pge->FillRectDecal(olc::vf2d(line_position.x + (size.x / 2) + (pge->GetTextSizeProp(text).x / 2), line_position.y), olc::vf2d(size.x - (size.x / 2) - (pge->GetTextSizeProp(text).x / 2), 1), color_scheme.groupbox_outline);
    // left outline
    pge->FillRectDecal(line_position, olc::vi2d(1, size.y), color_scheme.groupbox_outline);
    // right outline
    pge->FillRectDecal(olc::vi2d(line_position.x + size.x, line_position.y), olc::vi2d(1, size.y), color_scheme.groupbox_outline);
    // bottom outline
    pge->FillRectDecal(olc::vi2d(line_position.x, line_position.y + size.y), olc::vf2d(size.x + 1, 1), color_scheme.groupbox_outline);

    auto text_size = pge->GetTextSizeProp(text) * text_scale;
    pge->DrawStringPropDecal(olc::vf2d(line_position.x + (size.x / 2) - (text_size.x / 2), line_position.y - (text_size.y / 2)), text, text_color);

}

/*
####################################################
################FUI_SLIDER START####################
####################################################
*/
class FUI_Slider : public FUI_Element
{
private:
    enum class State
    {
        NONE = 0,
        HOVER,
        ACTIVE
    };
    float ratio = 0.f;
    State state = State::NONE;
public:
    FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);
    FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);
    FUI_Slider(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);
    FUI_Slider(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);

    void draw(olc::PixelGameEngine* pge) override;

    void input(olc::PixelGameEngine* pge) override;
};

FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    range = r;
    slier_value_holder = vh;
    ui_type = FUI_Type::SLIDER;
}

FUI_Slider::FUI_Slider(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    range = r;
    slier_value_holder = vh;
    ui_type = FUI_Type::SLIDER;
}

FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh)
{
    identifier = id;
    text = t;
    size = s;
    parent = pt;
    position = p;
    group = g;
    range = r;
    slier_value_holder = vh;
    ui_type = FUI_Type::SLIDER;
}

FUI_Slider::FUI_Slider(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh)
{
    identifier = id;
    text = t;
    size = s;
    position = p;
    group = g;
    range = r;
    slier_value_holder = vh;
    ui_type = FUI_Type::SLIDER;
}

void FUI_Slider::draw(olc::PixelGameEngine* pge)
{
    // Adapt positioning depending on if there's a parent to the element or not
    if (parent)
        adaptive_position = (parent->get_position() + olc::vf2d(parent->get_border_thickness(), parent->get_top_border_thickness()));
    else
        adaptive_position = olc::vi2d(0, 0);
    
    auto absolute_position = position + adaptive_position;

    // draw title with slider value
    std::string temp_text = text + " [" + to_string_with_precision(slider_value, 2) + "] ";
    pge->DrawStringPropDecal(olc::vf2d(absolute_position.x - (pge->GetTextSizeProp(temp_text).x * text_scale.y),
                                       absolute_position.y + (size.y / 2) - ((pge->GetTextSizeProp(text).y * text_scale.y) / 2)), temp_text, text_color);

    if (ratio == 0.0f)
        ratio = slider_value / range.y;

    // draw slider body
    switch (state)
    {
    case State::NONE:
        pge->FillRectDecal(absolute_position, olc::vf2d(size.x * ratio, size.y), color_scheme.slider_normal);
        break;
    case State::HOVER:
        pge->FillRectDecal(absolute_position, olc::vf2d(size.x * ratio, size.y), color_scheme.slider_hover);
        break;
    case State::ACTIVE:
        pge->FillRectDecal(absolute_position, olc::vf2d(size.x * ratio, size.y), color_scheme.slider_hover);
        break;
    }
    // top left outline
    pge->FillRectDecal(absolute_position, olc::vf2d(size.x, 1), color_scheme.slider_outline);
    // left outline
    pge->FillRectDecal(absolute_position, olc::vi2d(1, size.y), color_scheme.slider_outline);
    // right outline
    pge->FillRectDecal(olc::vi2d(absolute_position.x + size.x, absolute_position.y), olc::vi2d(1, size.y), color_scheme.slider_outline);
    // bottom outline
    pge->FillRectDecal(olc::vi2d(absolute_position.x, absolute_position.y + size.y), olc::vf2d(size.x + 1, 1), color_scheme.slider_outline);
}

void FUI_Slider::input(olc::PixelGameEngine* pge)
{
    if (pge->GetMousePos().x >= adaptive_position.x + position.x &&
        pge->GetMousePos().x <= adaptive_position.x + position.x + size.x &&
        pge->GetMousePos().y >= adaptive_position.y + position.y &&
        pge->GetMousePos().y <= adaptive_position.y + position.y + size.y)
    {
        state = State::HOVER;
        if (pge->GetMouse(0).bHeld)
            state = State::ACTIVE;
    }
    else if (state != State::ACTIVE)
        state = State::NONE;

    if (pge->GetMouse(0).bReleased)
        state = State::NONE;

    if (state == State::ACTIVE)
    {
        float slider_delta = (pge->GetMouseX() - (adaptive_position.x + position.x));
        if (slider_delta <= range.x)
            slider_delta = range.x;
        else if (slider_delta >= size.x)
            slider_delta = size.x;

        ratio = (slider_delta / size.x);
        slider_value = range.x + (range.y - range.x) * ratio;
        *slier_value_holder = slider_value;
    }
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
    std::deque<std::pair<FUI_Type, std::shared_ptr<FUI_Element>>> groupboxes;
    std::pair<bool, std::shared_ptr<FUI_Element>> trigger_pushback = std::make_pair(false, nullptr);

    void push_focused_to_back()
    {
        int i = 0;
        for (auto& window : windows)
        {
            if (window->get_closed_state())
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

    void push_focused_element_to_back()
    {
        int i = 0;
        for (auto& element : elements)
        {
            if (element.second->is_focused)
            {
                elements.push_back(element);
                elements.erase(elements.begin() + i);
            }
            i++;
        }
    }
public:

    void set_active_window(const std::string& window_id) 
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

    void set_active_group(const std::string& g)
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
    
    FUI_Window* create_window(const std::string& identifier, olc::vi2d position, olc::vi2d size, const std::string& title)
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

    void add_group(const std::string& g) 
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

    const std::string& get_active_group() { return active_group; }

    void add_button(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void add_button(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

    void add_checkbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state);

    void add_checkbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state);

    void add_dropdown(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_dropdown(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_combolist(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_combolist(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_groupbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_groupbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

    void add_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);

    void add_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);

    void add_label(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position);

    void add_label(const std::string& identifier, const std::string& text, olc::vi2d position);

    FUI_Window* find_window(const std::string& identifier)
    {
        for (auto& window : windows)
        {
            if (window->get_id() == identifier)
                return window;
        }
        std::cout << "Could not find the window ID in added windows (function affected: find_window, affected window_id: " + identifier + ")\n";
        return nullptr;
    }

    std::shared_ptr<FUI_Element> find_element(const std::string& identifier);

    std::shared_ptr<FUI_Element> find_groupbox(const std::string& identifier);

    void remove_element(const std::string& identifier);

    int get_element_amount() { return elements.size(); }

    void run();
};

void olcPGEX_FrostUI::remove_element(const std::string& id)
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

std::shared_ptr<FUI_Element> olcPGEX_FrostUI::find_element(const std::string& id)
{
    for (auto& element : elements)
    {
        if (element.second->identifier == id)
            return element.second;
    }
    return nullptr;
}

std::shared_ptr<FUI_Element> olcPGEX_FrostUI::find_groupbox(const std::string& id)
{
    for (auto& element : groupboxes)
    {
        if (element.second->identifier == id)
            return element.second;
    }
    return nullptr;
}

void olcPGEX_FrostUI::add_label(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position)
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

void olcPGEX_FrostUI::add_label(const std::string& identifier, const std::string& text, olc::vi2d position)
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

void olcPGEX_FrostUI::add_checkbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, window, text, position, size, cb_state)));
                    else
                        elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, window, active_group, text, position, size, cb_state)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_checkbox, checkbox_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_checkbox, checkbox_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_checkbox, checkbox_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_checkbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, window, active_group, text, position, size, cb_state)));
                    else
                        elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, window, text, position, size, cb_state)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, active_group, text, position, size, cb_state)));
            else
                elements.push_front(std::make_pair(FUI_Type::CHECKBOX, std::make_shared<FUI_Checkbox>(identifier, text, position, size, cb_state)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_checkbox, checkbox_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_dropdown(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, window, text, position, size)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, window, active_group, text, position, size)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_dropdown, dropdown_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_dropdown, dropdown_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_dropdown, dropdown_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_dropdown(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, window, active_group, text, position, size)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, window, text, position, size)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, active_group, text, position, size)));
            else
                elements.push_back(std::make_pair(FUI_Type::DROPDOWN, std::make_shared<FUI_Dropdown>(identifier, text, position, size)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_dropdown, dropdown_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_combolist(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, window, text, position, size)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, window, active_group, text, position, size)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_combolist, combolist_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_combolist, combolist_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_combolist, combolist_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_combolist(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, window, active_group, text, position, size)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, window, text, position, size)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, active_group, text, position, size)));
            else
                elements.push_back(std::make_pair(FUI_Type::COMBOLIST, std::make_shared<FUI_Combolist>(identifier, text, position, size)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_combolist, combolist_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_groupbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, window, text, position, size)));
                    else
                        groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, window, active_group, text, position, size)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_groupbox, groupbox_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_groupbox, groupbox_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_groupbox, groupbox_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_groupbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, window, active_group, text, position, size)));
                    else
                        groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, window, text, position, size)));
            }
        }
        else
            if (!active_group.empty())
                groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, active_group, text, position, size)));
            else
                groupboxes.push_back(std::make_pair(FUI_Type::GROUPBOX, std::make_shared<FUI_Groupbox>(identifier, text, position, size)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_groupbox, groupbox_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder)
{
    if (!find_element(identifier))
    {
        if (windows.size() > 0)
        {
            for (auto& window : windows)
            {
                if (window->get_id() == parent_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, window, active_group, text, position, size, range, value_holder)));
                else
                    std::cout << "Could not find parent window ID (function affected: add_slider, slider_id affected: " + identifier + ")\n";
            }
        }
        else
            std::cout << "There's no windows to be used as parent (function affected: add_slider, slider_id affected: " + identifier + ")\n";
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_slider, slider_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder)
{
    if (!find_element(identifier))
    {
        if (!active_window_id.empty())
        {
            for (auto& window : windows)
            {
                if (window->get_id() == active_window_id)
                    if (!active_group.empty())
                        elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, window, active_group, text, position, size, range, value_holder)));
                    else
                        elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder)));
            }
        }
        else
            if (!active_group.empty())
                elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, active_group, text, position, size, range, value_holder)));
            else
                elements.push_back(std::make_pair(FUI_Type::SLIDER, std::make_shared<FUI_Slider>(identifier, text, position, size, range, value_holder)));
    }
    else
        std::cout << "Duplicate IDs found (function affected: add_slider, slider_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_button(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
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
        std::cout << "Duplicate IDs found (function affected: add_button, button_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::add_button(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
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
        std::cout << "Duplicate IDs found (function affected: add_button, button_id affected: " + identifier + ")\n";
}

void olcPGEX_FrostUI::run()
{
    // Draw standalone elements first (standalone elements are elements without a parent / window)

    for (auto& g : groupboxes)
    {
        if (!g.second)
            continue;
        if (!g.second->get_group().empty())
            if (!active_group.empty())
                if (g.second->get_group() != active_group || g.second->get_group().empty())
                    continue;
        if (!g.second->parent)
            g.second->draw(pge);
    }
    
    for (auto& e : elements)
    {
        if (!e.second)
            continue;
        if (!e.second->get_group().empty())
            if (!active_group.empty())
                if (e.second->get_group() != active_group || e.second->get_group().empty())
                    continue;
        if (!e.second->parent)
        {
            e.second->draw(pge);
            e.second->input(pge);
        }
    }
    
    // arrange the deques containing the windows
    push_focused_to_back();

    if (trigger_pushback.first)
    {
        push_focused_element_to_back();
        trigger_pushback.first = false;
        trigger_pushback.second = nullptr;
    }

    // Draw windows first
    if (windows.size() > 0)
    {
        // make sure input is run in reverse order of drawing to not allow through window presses when out of focus
        for (int i = windows.size() - 1; i >= 0; i--)
        {
            if (!windows[i]->get_closed_state())
                windows[i]->input(windows);
        }

        for (auto& window : windows)
        {
            if (window->get_closed_state())
            {
                if (window->is_focused())
                    window->set_focused(false);
                continue;
            }
            
            window->draw();
            for (auto& g : groupboxes)
            {
                if (!g.second)
                    continue;
                if (!g.second->get_group().empty())
                    if (!active_group.empty())
                        if (g.second->get_group() != active_group || g.second->get_group().empty())
                            continue;
                if (g.second->parent && g.second->parent->get_id() == window->get_id())
                    g.second->draw(pge);
            }

            // first = FUI_Type, second = FUI_Element
            for (auto& e : elements)
            {
                if (!e.second)
                    continue;
                if (!e.second->get_group().empty())
                    if (!active_group.empty())
                        if (e.second->get_group() != active_group || e.second->get_group().empty())
                            continue;
                if (e.second->is_focused)
                {
                    trigger_pushback.first = true;
                    trigger_pushback.second = e.second;
                }
                if (e.second->parent)
                {
                    if (e.second->parent->get_id() == window->get_id())
                    {
                        e.second->draw(pge);
                        if (window->is_focused())
                        {
                            if (trigger_pushback.second)
                            {
                                if (trigger_pushback.second->identifier == e.second->identifier)
                                    e.second->input(pge);
                            }
                            else
                                e.second->input(pge);
                        }
                        else
                            e.second->is_focused = false;
                    }
                    else
                        continue;
                }
            }
        }
    }
}
#endif