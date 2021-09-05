/*
    FrostUI.h

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

    Credits to Megarev#2866 on discord for keyboard input related code (https://github.com/Megarev/olcPGEX_TextEnterer)
*/
#ifndef OLC_PGEX_FROSTUI
#define OLC_PGEX_FROSTUI

#include "olcPixelGameEngine.h"
#include <deque>
#include <iomanip>

/*
####################################################
#                  DECLARATIONS                    #
####################################################
*/
namespace olc
{
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
        olc::Pixel button_click = { 120, 120, 120 };
        olc::Pixel button_active = { 100, 100, 100 };
        // checkbox colors
        olc::Pixel checkbox_normal = olc::GREY;
        olc::Pixel checkbox_hover = { 150, 150, 150 };
        olc::Pixel checkbox_click = { 120, 120, 120 };
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
        // inputfield colors
        olc::Pixel inputfield_outline = olc::BLACK;
        olc::Pixel inputfield_background = { 150, 150, 150 };
        olc::Pixel inputfield_select_all_background = { 29, 43, 240, 150 };
        olc::Pixel inputfield_cursor = olc::BLACK;
        // scroll indicator
        olc::Pixel scroll_indicator = { 50, 50, 50 };
        // console colors
        olc::Pixel console_outline = olc::BLACK;
        olc::Pixel console_background = { 150, 150, 150 };
    };

    enum class FUI_Type
    {
        BUTTON = 0,
        LABEL,
        CHECKBOX,
        DROPDOWN,
        COMBOLIST,
        GROUPBOX,
        SLIDER,
        INPUTFIELD,
        CONSOLE
    };

    class FUI_Window
    {
    private:
        olc::PixelGameEngine* pge;

        olc::vf2d position;
        olc::vi2d mouse_difference;
        olc::vf2d size;
        std::string title;

        FUI_Window* overlapping_window;

        FUI_Colors color_scheme;

        enum class button_state
        {
            NORMAL = 0,
            HOVER,
            CLICK
        };

        button_state state = button_state::NORMAL;

        bool is_dragging = false;
        bool disable_drag = false;

        bool focused = false;

        bool should_render = true;

        std::string identifier;

        float top_border_thickness = 20;
        float border_thickness = 5;

    public:
        FUI_Window(olc::PixelGameEngine* pge, const std::string& identifier, olc::vi2d position, olc::vi2d size, const std::string& title);

        void draw();

        void input(std::deque<FUI_Window*> windows);

        olc::vf2d get_position() const;

        olc::vf2d get_size() const;

        olc::vf2d get_window_space() const;

        std::string get_id() const;

        float get_top_border_thickness() const;

        float get_border_thickness() const;

        void set_top_border_thickness(float thickness);

        void set_border_thickness(float thickness);

        void close_window(bool close);

        bool get_closed_state() const;

        void change_position(olc::vi2d pos);

        void change_size(olc::vi2d s);

        void set_focused(bool state);

        bool is_focused() const;

        void disable_dragging(bool state);
    };

    class FUI_Element
    {
    public: 
        enum class type
        {
            FLOAT = 0,
            INT
        };
    protected:
        enum class DropdownState
        {
            NONE = 0,
            HOVER,
            ACTIVE
        };
        FUI_Window* parent = nullptr;
        olc::vf2d size;
        olc::vf2d position;
        olc::vf2d absolute_position;
        std::string text;
        std::string group;
        olc::vf2d text_scale = { 1.0f, 1.0f };
        olc::vf2d input_scale = { 1.0f, 1.0f };
        FUI_Type ui_type;

        bool has_textures = false;
        olc::Decal* texture;
        std::vector<olc::vi2d> texture_positions;
        olc::vi2d texture_size = { 0, 0 };
        olc::vf2d texture_scale = { 1.0f, 1.0f };

        FUI_Colors color_scheme;

        type slider_type;
        float slider_value_float = 0.f;
        int slider_value_int = 0;
        float* slider_value_holder_float = nullptr;
        int* slider_value_holder_int = nullptr;
        olc::vf2d range;

        std::function<void()> input_enter_callback;

        bool* toggle_button_state = nullptr;

        bool clear_inputfield = false;
        std::string inputfield_text = "";
        bool mask_inputfield = false;

        bool is_focused = false;

        std::vector<std::pair<int, std::pair<DropdownState, std::pair<olc::vf2d, std::string>>>> elements;
        std::pair<int, std::pair<olc::vf2d, std::string>> selected_element;
        std::vector<std::pair<int, std::pair<olc::vf2d, std::string>>> selected_elements;
        std::vector<int> return_selected_items;
        float animation_speed = 150.0f;
        int max_display_items = 0;

        olc::Pixel text_color = olc::BLACK;

        std::string identifier;

        std::function<void(std::string&, std::string*)> command_handler;
    public:

        virtual void draw(olc::PixelGameEngine* pge) {}

        virtual void input(olc::PixelGameEngine* pge) {}

        const std::string get_identifier();

        const int get_elements_amount();

        const bool get_focused_status();

        void set_focused_status(bool status);

        const FUI_Window* get_parent();

        const FUI_Type get_ui_type();

        const olc::vf2d get_size();

        void set_size(olc::vi2d s);

        void set_position(olc::vf2d p);

        void set_text(const std::string& txt);

        void set_text_color(olc::Pixel color);

        std::string get_group() const;

        void scale_text(olc::vf2d scale);

        void inputfield_scale(olc::vf2d scale);

        void make_toggleable(bool* state);

        void add_item(const std::string& item, olc::vf2d scale);

        void set_animation_speed(float speed);

        const int get_selected_item();

        std::vector<int> get_selected_items();

        const olc::vf2d get_position() const;

        const olc::vf2d get_absolute_position();

        void set_default_item(const int& item);

        void set_default_items(const std::vector<int>& items);

        void set_max_display_items(const int amount);

        void set_slider_value(float value);

        void set_slider_value(int value);

        const float get_slider_value() const;

        const std::string get_inputfield_value() const;

        void clear_inputfield_value();

        void mask_inputfield_value(bool state);

        olc::vi2d get_text_size(olc::PixelGameEngine* pge);

        void add_texture(olc::Decal* texture, std::vector<olc::vi2d> texture_positions, olc::vi2d size);

        void set_on_enter_callback(std::function<void()> cb);

        void add_command_handler(std::function<void(std::string&, std::string*)> handler);
    };

    class FUI_Label : public FUI_Element
    {
    public:
        FUI_Label(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position);
        FUI_Label(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position);
        FUI_Label(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position);
        FUI_Label(const std::string& id, const std::string& text, olc::vi2d position);

        void draw(olc::PixelGameEngine* pge) override;
    };

    class FUI_Button : public FUI_Element
    {
    private:
        enum class State
        {
            NONE = 0,
            HOVER,
            CLICK,
            ACTIVE
        };

        std::function<void()> callback;
        State state = State::NONE;
        bool was_active = false;
    public:
        FUI_Button(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
        FUI_Button(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
        FUI_Button(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);
        FUI_Button(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    class FUI_Checkbox : public FUI_Element
    {
    private:
        enum class State
        {
            NONE = 0,
            HOVER,
            CLICK,
            ACTIVE
        };

        bool* checkbox_state;
        State state = State::NONE;
        bool was_active = false;
    public:
        FUI_Checkbox(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
        FUI_Checkbox(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
        FUI_Checkbox(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);
        FUI_Checkbox(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, bool* state);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    class FUI_Dropdown : public FUI_Element
    {
    private:
        olc::vf2d active_size = olc::vf2d{ 0.f, 0.f };
        DropdownState state = DropdownState::NONE;
        bool is_open = false;
        int item_start_index = 1;
    public:
        FUI_Dropdown(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Dropdown(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Dropdown(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Dropdown(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    class FUI_Combolist : public FUI_Element
    {
    private:
        olc::vf2d active_size = olc::vf2d{ 0.f, 0.f };
        DropdownState state = DropdownState::NONE;
        bool is_open = false;
        int item_start_index = 1;
    public:
        FUI_Combolist(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Combolist(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Combolist(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Combolist(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

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
        float slider_ratio = 0.f;
        State state = State::NONE;
        bool has_negative = false;

        bool run_once = true;

        std::string to_string_with_precision(const float a_value, const int n);

    public:
        // float sliders
        FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder, type slider_type);
        FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder, type slider_type);
        FUI_Slider(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder, type slider_type);
        FUI_Slider(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder, type slider_type);

        // int sliders
        FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder, type slider_type);
        FUI_Slider(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder, type slider_type);
        FUI_Slider(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder, type slider_type);
        FUI_Slider(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder, type slider_type);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    // Credits to Megarev#2866 on discord for keyboard input related code
    class FUI_Inputfield : public FUI_Element
    {
    private:
        enum class State
        {
            NONE = 0,
            ACTIVE
        };

        enum class TextKey {
            None = -1,
            A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
            LBracket, RBracket, Semicolon, Comma, Period, Quote, ForwardSlash, BackwardSlash,
            Tilda, Equal, Hyphen, Space
        };

        int text_keys = 48;

        State state = State::NONE;
        std::string text_noshift = "abcdefghijklmnopqrstuvwxyz0123456789[];,.'/\\`=- ";
        std::string text_shift = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)!@#$%^&*({}:<>\"?|~+_ ";
        bool select_all = false;

        bool is_textkey_pressed(olc::PixelGameEngine* pge, const TextKey& key);

        int get_char_id(olc::PixelGameEngine* pge);

        std::string get_char_from_id(olc::PixelGameEngine* pge);

        std::string old_inputfield_text = inputfield_text;
        std::string text_out_of_view;
        std::string displayed_text;

        uint64_t last_cursor_tick = 0;

    public:
        FUI_Inputfield(const std::string& id, FUI_Window* parent, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Inputfield(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Inputfield(const std::string& id, const std::string& group, const std::string& text, olc::vi2d position, olc::vi2d size);
        FUI_Inputfield(const std::string& id, const std::string& text, olc::vi2d position, olc::vi2d size);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    class FUI_Console : public FUI_Element
    {
    private:
        FUI_Inputfield inputfield = FUI_Inputfield{ "console_input", "", { 0, 0 }, { 0, 0 } };

        int input_thickness = 10;
        std::string command;
        std::string executed_command;
        std::vector<std::string> executed_commands;

        bool run_once = true;
        float scroll_threshold = 0.f;
        bool can_scroll = false;
        int scroll_index = 0;
        int commands_shown = 0;

        std::string get_time() 
        {
            time_t now = time(0);
            struct tm tstruct;
            char buf[80];
            localtime_s(&tstruct, &now);
            strftime(buf, sizeof(buf), "%H:%M", &tstruct);
            return buf;
        }
    public:
        FUI_Console(const std::string& id, FUI_Window* parent, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness);
        FUI_Console(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness);
        FUI_Console(const std::string& id, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness);
        FUI_Console(const std::string& id, const std::string& group, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness);

        void draw(olc::PixelGameEngine* pge) override;

        void input(olc::PixelGameEngine* pge) override;
    };

    class FrostUI : public olc::PGEX
    {
    private:
        std::deque<FUI_Window*> windows;
        std::vector<std::pair<std::string, std::string>> groups;
        std::string active_window_id;
        std::pair<std::string, std::string> active_group;
        std::deque<std::shared_ptr<FUI_Element>> elements;
        std::deque<std::shared_ptr<FUI_Element>> groupboxes;
        std::pair<bool, std::shared_ptr<FUI_Element>> trigger_pushback = std::make_pair(false, nullptr);
        
        std::string current_focused_window;
        std::string saved_focused_window;

        bool prime_window_focusing = true;

        bool is_a_window_focused();

        bool disable_window_input_if_open_dropdown(int window_index);

        void cycle_inputfield();

        void push_focused_to_back();

        void push_focused_element_to_back();

    public:

        void set_active_window(const std::string& window_id);

        void set_active_group(const std::string& g);

        FUI_Window* create_window(const std::string& identifier, const std::string& title, olc::vi2d position, olc::vi2d size);

        void add_group(const std::string& window_id, const std::string& g);

        void clear_active_window();

        void clear_active_group();

        const std::string& get_active_group();

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

        void add_float_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);

        void add_float_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder);

        void add_int_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder);

        void add_int_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder);

        void add_label(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position);

        void add_label(const std::string& identifier, const std::string& text, olc::vi2d position);

        void add_inputfield(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

        void add_inputfield(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size);

        void add_console(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, int inputfield_thickness);

        void add_console(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, int inputfield_thickness);

        FUI_Window* find_window(const std::string& identifier);

        std::shared_ptr<FUI_Element> find_element(const std::string& identifier);

        std::shared_ptr<FUI_Element> find_groupbox(const std::string& identifier);

        void remove_element(const std::string& identifier);

        int get_element_amount();

        void run();
    };
}
/*
####################################################
#               IMPLEMENTATIONS                    #
####################################################
*/
#define OLC_PGEX_FUI
#ifdef OLC_PGEX_FUI
#undef OLC_PGEX_FUI
namespace olc
{
    FUI_Window::FUI_Window(olc::PixelGameEngine* p, const std::string& id, olc::vi2d pos, olc::vi2d s, const std::string& txt)
    {
        identifier = id;
        pge = p;
        position = pos;
        size = s;
        title = txt;
    }

    olc::vf2d FUI_Window::get_position() const { return position; }

    olc::vf2d FUI_Window::get_size() const { return size; }

    olc::vf2d FUI_Window::get_window_space() const { return olc::vf2d{ size.x - border_thickness * 2, size.y - top_border_thickness }; }

    std::string FUI_Window::get_id() const { return identifier; }

    float FUI_Window::get_top_border_thickness() const { return top_border_thickness; }

    float FUI_Window::get_border_thickness() const { return border_thickness; }

    void FUI_Window::set_top_border_thickness(float thickness) { top_border_thickness = thickness; }

    void FUI_Window::set_border_thickness(float thickness) { border_thickness = thickness; }

    void FUI_Window::close_window(bool close) { should_render = !close; }

    bool FUI_Window::get_closed_state() const { return !should_render; }

    void FUI_Window::change_position(olc::vi2d pos) { position = pos; }

    void FUI_Window::change_size(olc::vi2d s) { size = s; }

    void FUI_Window::set_focused(bool state) { focused = state; }

    bool FUI_Window::is_focused() const { return focused; }

    void FUI_Window::disable_dragging(bool state) { disable_drag = state; }

    void FUI_Window::draw()
    {
        // Draw the main window area
        pge->FillRectDecal(position, size, color_scheme.window_background_color);

        // Draw the window border
        pge->FillRectDecal(position, olc::vf2d{ border_thickness, size.y }, color_scheme.window_border_color); // Left side
        pge->FillRectDecal(olc::vf2d{ position.x + size.x - border_thickness, position.y }, olc::vf2d{ border_thickness, size.y }, color_scheme.window_border_color); // Right side
        pge->FillRectDecal(olc::vf2d{ position.x, position.y + size.y - border_thickness }, olc::vf2d{ size.x, border_thickness }, color_scheme.window_border_color); // Bottom side
        pge->FillRectDecal(position, olc::vf2d{ size.x, top_border_thickness }, color_scheme.window_border_color); // Top bar

        // Draw the window title
        olc::vf2d title_position = olc::vf2d{ position.x + (size.x / 2) - (pge->GetTextSizeProp(title).x / 2), position.y + (top_border_thickness / 2) - (pge->GetTextSizeProp(title).y / 2) };
        pge->DrawStringPropDecal(title_position, title, olc::BLACK);

        // Draw the default window close button
        olc::vf2d temp_pos = { position.x + size.x - (size.x / 10), position.y };
        olc::vf2d temp_size = { size.x / 10, top_border_thickness };
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
        olc::vf2d close_position = olc::vf2d{ temp_pos.x + (temp_size.x / 2) - (pge->GetTextSizeProp("X").x / 2), temp_pos.y + (top_border_thickness / 2) - (pge->GetTextSizeProp("X").y / 2) };
        pge->DrawStringPropDecal(close_position, "X", olc::BLACK);

        // Override top border with a darker color when window is inactive 
        if (!focused)
            pge->FillRectDecal(position, olc::vf2d{ size.x, top_border_thickness }, { 100, 100, 100, 150 }); // Top bar
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
            if (pge->GetMouse(0).bHeld || pge->GetMouse(0).bPressed || pge->GetMouse(0).bReleased)
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

        // dragging related
        if (!disable_drag)
        {
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
        }
        // focusing system related
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
    #               FUI_ELEMENT START                  #
    ####################################################
    */
    const std::string FUI_Element::get_identifier()
    {
        return identifier;
    }

    const int FUI_Element::get_elements_amount()
    {
        if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST)
            return elements.size();
        else
            std::cout << "Trying to get element amount on incorrect UI_TYPE\n";
        return -1;
    }

    const bool FUI_Element::get_focused_status()
    {
        return is_focused;
    }

    void FUI_Element::set_focused_status(bool status)
    {
        is_focused = status;
    }

    const FUI_Window* FUI_Element::get_parent()
    {
        return parent;
    }

    const FUI_Type FUI_Element::get_ui_type()
    {
        return ui_type;
    }

    const olc::vf2d FUI_Element::get_size()
    {
        return size;
    }

    void FUI_Element::set_size(olc::vi2d s)
    {
        size = s;
    }

    void FUI_Element::set_position(olc::vf2d p)
    {
        position = p;
    }

    void FUI_Element::set_text(const std::string& txt)
    {
        text = txt;
    }

    void FUI_Element::set_text_color(olc::Pixel color)
    {
        text_color = color;
    }

    std::string FUI_Element::get_group() const
    {
        return group;
    }

    void FUI_Element::scale_text(olc::vf2d scale)
    {
        text_scale = scale;
    }

    void FUI_Element::inputfield_scale(olc::vf2d scale)
    {
        if (ui_type == FUI_Type::INPUTFIELD)
            input_scale = scale;
        else
            std::cout << "Trying to use inputfield_scale on incorrect UI_TYPE\n";
    }

    void FUI_Element::make_toggleable(bool* state)
    {
        if (ui_type == FUI_Type::BUTTON)
            toggle_button_state = state;
        else
            std::cout << "Trying to make_toggleable on incorrect UI_TYPE\n";
    }

    void FUI_Element::add_item(const std::string& item, olc::vf2d scale = { 1.0f, 1.0f })
    {
        if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST)
            elements.push_back(std::make_pair(elements.size(), std::make_pair(DropdownState::NONE, std::make_pair(scale, item))));
        else
            std::cout << "Trying to add_item to wrong UI_TYPE\n";
    }

    void FUI_Element::set_animation_speed(float speed)
    {
        if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST)
            animation_speed = speed;
        else
            std::cout << "Trying to set_animation_speed on wrong UI_TYPE\n";
    }

    const int FUI_Element::get_selected_item()
    {
        if (ui_type == FUI_Type::DROPDOWN)
            return selected_element.first;
        else std::cout << "Trying to get_selected_item on wrong UI_TYPE\n";

        return -1;
    }

    void FUI_Element::set_default_item(const int& item)
    {
        if (ui_type == FUI_Type::DROPDOWN)
        {
            if (item > elements.size() - 1)
                std::cout << "Trying to set a invalid default item (" + std::to_string(item) + ")\n";
            else
            {
                for (auto& element : elements)
                {
                    if (element.first == item)
                    {
                        selected_element.first = element.first;
                        selected_element.second = element.second.second;
                    }
                }
            }
        }
        else
            std::cout << "Trying to set_default_item to wrong UI_TYPE\n";
    }

    void FUI_Element::set_default_items(const std::vector<int>& items)
    {
        if (ui_type == FUI_Type::COMBOLIST)
        {
            for (auto& element : elements)
            {
                for (auto& item : items)
                {
                    if (item > elements.size() - 1)
                        std::cout << "Trying to set a invalid default item (" + std::to_string(item) + ")\n";
                    else
                    {
                        bool found = false;
                        int selected_id = 0;
                        for (auto& e : selected_elements)
                        {
                            if (selected_id == item)
                                found = true;
                        }
                        if (element.first == item && !found)
                        {
                            element.second.first = DropdownState::ACTIVE;
                            selected_elements.push_back(std::make_pair(element.first, element.second.second));
                        }
                    }
                }
            }
        }
        else
            std::cout << "Trying to set_default_item to wrong UI_TYPE\n";
    }

    void FUI_Element::set_max_display_items(const int amount)
    {
        if (ui_type == FUI_Type::DROPDOWN || ui_type == FUI_Type::COMBOLIST)
        {
            if (amount <= elements.size())
                max_display_items = amount;
        }
        else
            std::cout << "Trying to set_max_display_items on wrong UI_TYPE\n";
    }

    std::vector<int> FUI_Element::get_selected_items()
    {
        if (ui_type == FUI_Type::COMBOLIST)
        {
            return_selected_items.clear();
            for (auto& item : selected_elements)
                return_selected_items.push_back(item.first);

            return return_selected_items;
        }
        else
            std::cout << "Trying to retrieve selected items on wrong UI_TYPE\n";

        return return_selected_items;
    }

    const olc::vf2d FUI_Element::get_position() const
    {
        return position;
    }

    const olc::vf2d FUI_Element::get_absolute_position()
    {
        if (parent)
            absolute_position = (parent->get_position() + olc::vf2d{ parent->get_border_thickness(), parent->get_top_border_thickness() });
        else
            absolute_position = olc::vf2d{ 0, 0 };
        return absolute_position + position;
    }

    void FUI_Element::set_slider_value(float value)
    {
        if (ui_type == FUI_Type::SLIDER)
        {
            slider_value_float = value;
            *slider_value_holder_float = value;
        }
        else
            std::cout << "Trying to set_slider_value on wrong UI_TYPE\n";
    }

    void FUI_Element::set_slider_value(int value)
    {
        if (ui_type == FUI_Type::SLIDER)
        {
            slider_value_int = value;
            *slider_value_holder_int = value;
        }
        else
            std::cout << "Trying to set_slider_value on wrong UI_TYPE\n";
    }

    const float FUI_Element::get_slider_value() const
    {
        if (ui_type == FUI_Type::SLIDER)
        {
            switch (slider_type)
            {
            case type::FLOAT:
                return slider_value_float;
            case type::INT:
                return slider_value_int;
            }
        }
        else
            std::cout << "Trying to get_slider_value on wrong UI_TYPE\n";

        return 0.0f;
    }

    const std::string FUI_Element::get_inputfield_value() const
    {
        if (ui_type == FUI_Type::INPUTFIELD)
            return inputfield_text;
        else
            std::cout << "Trying to get_inputfield_value on wrong UI_TYPE\n";

        return "";
    }

    void FUI_Element::clear_inputfield_value()
    {
        if (ui_type == FUI_Type::INPUTFIELD)
            clear_inputfield = true;
        else
            std::cout << "Trying to clear_inputfield_value on wrong UI_TYPE\n";
    }

    void FUI_Element::mask_inputfield_value(bool state)
    {
        mask_inputfield = state;
    }

    olc::vi2d FUI_Element::get_text_size(olc::PixelGameEngine* pge)
    {
        return pge->GetTextSizeProp(text) * text_scale;
    }

    void FUI_Element::add_texture(olc::Decal* txtr, std::vector<olc::vi2d> texture_pos, olc::vi2d s)
    {
        texture = txtr;
        texture_positions = texture_pos;
        texture_size = s;

        texture_scale = { static_cast<float>(size.x) / static_cast<float>(s.x), static_cast<float>(size.y) / static_cast<float>(s.y) };
        size = { std::round(s.x * texture_scale.x), std::round(s.y * texture_scale.y) };
        has_textures = true;

        // warning messages
        switch(ui_type)
        {
        case FUI_Type::BUTTON:
            if (toggle_button_state)
            {
                if (texture_positions.size() < 4)
                    std::cout << "There's not enough sprites to cover all toggle button states\n";
            }
            else
                if (texture_positions.size() < 3)
                    std::cout << "There's not enough sprites to cover all button states\n";
            break;
        }
    }

    void FUI_Element::set_on_enter_callback(std::function<void()> callback)
    {
        if (ui_type == FUI_Type::INPUTFIELD)
        {
            input_enter_callback = callback;
        }
        else
            std::cout << "Trying to set_on_enter_action on wrong UI_TYPE\n";
    }

    void FUI_Element::add_command_handler(std::function<void(std::string&, std::string*)> handler)
    {
        if (ui_type == FUI_Type::CONSOLE)
            command_handler = handler;
        else
            std::cout << "Trying to add_command_handler to wrong UI_TYPE\n";
    }

    /*
    ####################################################
    #               FUI_LABEL START                    #
    ####################################################
    */
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
        absolute_position = get_absolute_position();

        pge->DrawStringPropDecal(absolute_position, text, text_color, text_scale);
    }

    /*
    ####################################################
    #               FUI_BUTTON START                   #
    ####################################################
    */
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
        absolute_position = get_absolute_position();

        if (has_textures)
        {
            // Draw the body of the button
            switch (state)
            {
            case State::NONE:
                pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::NONE)], texture_size, texture_scale);
                break;
            case State::HOVER:
                if (texture_positions.size() > 1)
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::HOVER)], texture_size, texture_scale);
                else
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::NONE)], texture_size, texture_scale);
                break;
            case State::CLICK:
                if (texture_positions.size() > 2)
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::CLICK)], texture_size, texture_scale);
                else
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::NONE)], texture_size, texture_scale);
                break;
            case State::ACTIVE:
                if (texture_positions.size() > 3)
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::CLICK)], texture_size, texture_scale);
                else
                    pge->DrawPartialDecal(absolute_position, texture, texture_positions[static_cast<int>(State::NONE)], texture_size, texture_scale);
                break;
                break;
            }
        }
        else
        {
            auto text_size = pge->GetTextSizeProp(text) * text_scale;

            // Draw the body of the button
            switch (state)
            {
            case State::NONE:
                pge->FillRectDecal(absolute_position, size, color_scheme.button_normal);
                break;
            case State::HOVER:
                pge->FillRectDecal(absolute_position, size, color_scheme.button_hover);
                break;
            case State::CLICK:
                pge->FillRectDecal(absolute_position, size, color_scheme.button_click);
                break;
            case State::ACTIVE:
                pge->FillRectDecal(absolute_position, size, color_scheme.button_active);
                break;
            }
            // Draw the text
            olc::vf2d text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (text_size.x / 2),
                absolute_position.y + (size.y / 2) - (text_size.y / 2) };
            pge->DrawStringPropDecal(text_position, text, text_color, text_scale);
        }
    }

    void FUI_Button::input(olc::PixelGameEngine* pge)
    {
        if (!toggle_button_state)
        {
            if (pge->GetMousePos().x >= absolute_position.x &&
                pge->GetMousePos().x <= absolute_position.x + size.x &&
                pge->GetMousePos().y >= absolute_position.y &&
                pge->GetMousePos().y <= absolute_position.y + size.y)
            {
                if (pge->GetMouse(0).bPressed)
                    state = State::CLICK;
                else if (pge->GetMouse(0).bReleased && state == State::CLICK)
                {
                    callback();
                    state = State::HOVER;
                }
                
                if (state != State::CLICK)
                    state = State::HOVER;
            }
            else
                state = State::NONE;
        }
        else
        {
            if (pge->GetMousePos().x >= absolute_position.x &&
                pge->GetMousePos().x <= absolute_position.x + size.x &&
                pge->GetMousePos().y >= absolute_position.y &&
                pge->GetMousePos().y <= absolute_position.y + size.y)
            {
                if (pge->GetMouse(0).bPressed)
                {
                    if (state == State::ACTIVE)
                        was_active = true;

                    state = State::CLICK;
                }
                else if (pge->GetMouse(0).bReleased && state == State::CLICK)
                {
                    if (was_active)
                    {
                        state = State::HOVER;
                        was_active = false;
                    }
                    else
                        state = State::ACTIVE;
                }

                if (state != State::CLICK && state != State::ACTIVE)
                    state = State::HOVER;
            }
            else if (state == State::CLICK && was_active)
                state = State::ACTIVE;
            else if (state != State::ACTIVE)
                state = State::NONE;

            if (state == State::ACTIVE)
                *toggle_button_state = true;
            else
                *toggle_button_state = false;
        }
    }

    /*
    ####################################################
    #               FUI_CHECKBOX START                 #
    ####################################################
    */
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
        absolute_position = get_absolute_position();

        // Draw the text
        auto text_size = pge->GetTextSizeProp(text) * text_scale;
        auto text_position = olc::vf2d{ absolute_position.x - text_size.x, absolute_position.y + (size.y / 2) - (text_size.y / 2) };
        pge->FillRectDecal(absolute_position, size, color_scheme.checkbox_normal);

        pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

        olc::vf2d checkbox_filling = olc::vf2d{ 1.0f, 1.0f };
        // Draw the body of the checkbox
        switch (state)
        {
        case State::NONE:
            break;
        case State::HOVER:
            pge->FillRectDecal(absolute_position + checkbox_filling,
                { static_cast<float>(size.x) - 2.0f, static_cast<float>(size.y) - 2.0f }, color_scheme.checkbox_hover);
            break;
        case State::CLICK:
            pge->FillRectDecal(absolute_position + checkbox_filling,
                { static_cast<float>(size.x) - 2.0f, static_cast<float>(size.y) - 2.0f }, color_scheme.checkbox_click);
            break;
        case State::ACTIVE:
            pge->FillRectDecal(absolute_position + checkbox_filling,
                { static_cast<float>(size.x) - 2.0f, static_cast<float>(size.y) - 2.0f }, color_scheme.checkbox_active);
            break;
        }
    }

    void FUI_Checkbox::input(olc::PixelGameEngine* pge)
    {
        if (pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y)
        {
            if (pge->GetMouse(0).bPressed)
            {
                if (state == State::ACTIVE)
                    was_active = true;

                state = State::CLICK;
            }
            else if (pge->GetMouse(0).bReleased && state == State::CLICK)
            {
                if (was_active)
                {
                    state = State::HOVER;
                    was_active = false;
                }
                else
                    state = State::ACTIVE;
            }

            if (state != State::CLICK && state != State::ACTIVE)
                state = State::HOVER;
        }
        else if (state == State::CLICK && was_active)
            state = State::ACTIVE;
        else if (state != State::ACTIVE)
            state = State::NONE;

        if (state == State::ACTIVE)
            *checkbox_state = true;
        else
            *checkbox_state = false;
    }

    /*
    ####################################################
    #               FUI_DROPDOWN START                 #
    ####################################################
    */
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
        absolute_position = get_absolute_position();
        auto title_text_size = pge->GetTextSizeProp(text) * text_scale;

        if (is_open)
        {
            float future_y = size.y * elements.size();
            if (max_display_items > 0)
                future_y = size.y * max_display_items;
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
        olc::vf2d text_position = olc::vf2d{ absolute_position.x - title_text_size.x,
            absolute_position.y + (size.y / 2) - (title_text_size.y / 2) };
        pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

        switch (state)
        {
        case DropdownState::NONE:
            pge->FillRectDecal(absolute_position, size, color_scheme.dropdown_normal);
            break;
        case DropdownState::HOVER:
            pge->FillRectDecal(absolute_position, size, color_scheme.dropdown_hover);
            break;
        case DropdownState::ACTIVE:
            pge->FillRectDecal(absolute_position, size, color_scheme.dropdown_active);
            break;
        }
        if (active_size.y != size.y * elements.size())
            pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y }, olc::vf2d{ size.x, active_size.y }, color_scheme.dropdown_normal);

        if (!selected_element.second.second.empty())
        {
            auto element_text_size = pge->GetTextSizeProp(selected_element.second.second) * selected_element.second.first;
            text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                absolute_position.y + (size.y / 2) - (element_text_size.y / 2) };
            pge->DrawStringPropDecal(text_position, selected_element.second.second, text_color, selected_element.second.first);
        }

        if (max_display_items > 0 && max_display_items < elements.size())
        {
            int i = 1;
            for (int j = item_start_index - 1; j < item_start_index + max_display_items - 1; j++)
            {
                auto element_text_size = pge->GetTextSizeProp(elements[j].second.second.second) * elements[j].second.second.first;
                if (active_size.y >= size.y * i)
                {
                    switch (elements[j].second.first)
                    {
                    case DropdownState::NONE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_normal);
                        break;
                    case DropdownState::HOVER:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_hover);
                        break;
                    case DropdownState::ACTIVE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_active);
                        break;
                    }
                }
                text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                    absolute_position.y + size.y + (size.y * i) - (size.y / 2) - (element_text_size.y / 2) };
                if (absolute_position.y + size.y + active_size.y > text_position.y + element_text_size.y)
                    pge->DrawStringPropDecal(text_position, elements[j].second.second.second, text_color, elements[j].second.second.first);

                i++;
            }

            if (is_open && (max_display_items < elements.size()))
            {
                float scroll_size =  (size.y + active_size.y) / (elements.size() - max_display_items);
                float scroll_y_pos = ((item_start_index - 1) * scroll_size);
                scroll_y_pos = scroll_y_pos - (scroll_y_pos / (elements.size() - max_display_items));

                pge->FillRectDecal({ absolute_position.x + size.x - 3, absolute_position.y + scroll_y_pos },
                    { 3, scroll_size }, color_scheme.scroll_indicator);

            }
        }
        else
        {
            int i = 1;
            for (auto& element : elements)
            {
                auto element_text_size = pge->GetTextSizeProp(element.second.second.second) * element.second.second.first;
                if (active_size.y >= size.y * i)
                {
                    switch (element.second.first)
                    {
                    case DropdownState::NONE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_normal);
                        break;
                    case DropdownState::HOVER:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_hover);
                        break;
                    case DropdownState::ACTIVE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.dropdown_active);
                        break;
                    }
                }
                text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                    absolute_position.y + size.y + (size.y * i) - (size.y / 2) - (element_text_size.y / 2) };
                if (absolute_position.y + size.y + active_size.y > text_position.y + element_text_size.y)
                    pge->DrawStringPropDecal(text_position, element.second.second.second, text_color, element.second.second.first);

                i++;
            }
        }
    }

    void FUI_Dropdown::input(olc::PixelGameEngine* pge)
    {
        bool could_close = false;
        if (pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y)
        {
            if (pge->GetMouse(1).bPressed)
                selected_element.second.second.clear();

            if (pge->GetMouse(0).bPressed)
                state = DropdownState::ACTIVE;
            else if (pge->GetMouse(0).bReleased && state == DropdownState::ACTIVE)
            {
                is_open = !is_open;
                state = DropdownState::HOVER;
            }

            if (state != DropdownState::ACTIVE)
                state = DropdownState::HOVER;
        }
        else
        {
            state = DropdownState::NONE;
            int element_amount;
            if (max_display_items > 0)
                element_amount = max_display_items;
            else
                element_amount = elements.size();
            if (!(pge->GetMousePos().x >= absolute_position.x &&
                pge->GetMousePos().x <= absolute_position.x + size.x &&
                pge->GetMousePos().y >= absolute_position.y &&
                pge->GetMousePos().y <= absolute_position.y + size.y + (size.y * element_amount)))
            {
                if (pge->GetMouse(0).bPressed)
                    could_close = true;
            }
        }


        if (is_open)
        {
            if (max_display_items > 0 && max_display_items < elements.size()) // if we have a max display limit we want to run a slightly different method of checking input
            {
                int i = 1;
                for (int j = item_start_index - 1; j < item_start_index + max_display_items - 1; j++)
                {
                    if (pge->GetMousePos().x >= absolute_position.x &&
                        pge->GetMousePos().x <= absolute_position.x + size.x &&
                        pge->GetMousePos().y > absolute_position.y + (size.y * i) &&
                        pge->GetMousePos().y < absolute_position.y + (size.y * i) + size.y)
                    {
                        if (pge->GetMouse(0).bPressed)
                            elements[j].second.first = DropdownState::ACTIVE;
                        else if (pge->GetMouse(0).bReleased && elements[j].second.first == DropdownState::ACTIVE)
                        {
                            selected_element.first = elements[j].first;
                            selected_element.second = elements[j].second.second;
                            elements[j].second.first = DropdownState::HOVER;
                            is_open = false;
                        }
                        else if (elements[j].second.first != DropdownState::ACTIVE)
                            elements[j].second.first = DropdownState::HOVER;
                    }
                    else
                    {
                        elements[j].second.first = DropdownState::NONE;
                        if (could_close && pge->GetMouse(0).bPressed)
                            is_open = false;
                    }
                    i++;
                }
                if (pge->GetMousePos().x >= absolute_position.x &&
                    pge->GetMousePos().x <= absolute_position.x + size.x &&
                    pge->GetMousePos().y >= absolute_position.y &&
                    pge->GetMousePos().y <= absolute_position.y + size.y + active_size.y)
                {
                    if (elements.size() > max_display_items)
                    {
                        if (pge->GetMouseWheel() > 0)
                        {
                            if (item_start_index > 1)
                                item_start_index--;
                        }
                        else if (pge->GetMouseWheel() < 0)
                        {
                            if (item_start_index < (elements.size() - max_display_items + 1))
                                item_start_index++;
                        }
                    }
                }
            }
            else // if we don't have any max display limit
            {
                int i = 1;
                for (auto& element : elements)
                {
                    if (pge->GetMousePos().x >= absolute_position.x &&
                        pge->GetMousePos().x <= absolute_position.x + size.x &&
                        pge->GetMousePos().y > absolute_position.y + (size.y * i) &&
                        pge->GetMousePos().y < absolute_position.y + (size.y * i) + size.y)
                    {
                        if (pge->GetMouse(0).bPressed)
                            element.second.first = DropdownState::ACTIVE;
                        else if (pge->GetMouse(0).bReleased && element.second.first == DropdownState::ACTIVE)
                        {
                            selected_element.first = element.first;
                            selected_element.second = element.second.second;
                            element.second.first = DropdownState::HOVER;
                            is_open = false;
                        }
                        else if (element.second.first != DropdownState::ACTIVE)
                            element.second.first = DropdownState::HOVER;
                    }
                    else
                    {
                        element.second.first = DropdownState::NONE;
                        if (could_close && pge->GetMouse(0).bPressed)
                            is_open = false;
                    }
                    i++;
                }
            }
        }

        if (is_open)
            is_focused = true;
        else
            is_focused = false;
    }

    /*
    ####################################################
    #               FUI_COMBOLIST START                #
    ####################################################
    */
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
        absolute_position = get_absolute_position();
        auto title_text_size = pge->GetTextSizeProp(text) * text_scale;

        if (is_open)
        {
            float future_y = size.y * elements.size();
            if (max_display_items > 0)
                future_y = size.y * max_display_items;
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
        olc::vf2d text_position = olc::vf2d{ absolute_position.x - title_text_size.x,
            absolute_position.y + (size.y / 2) - (title_text_size.y / 2) };
        pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

        switch (state)
        {
        case DropdownState::NONE:
            pge->FillRectDecal(absolute_position, size, color_scheme.dropdown_normal);
            break;
        case DropdownState::HOVER:
            pge->FillRectDecal(absolute_position, size, color_scheme.dropdown_hover);
            break;
        }
        if (active_size.y != size.y * elements.size())
            pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y }, olc::vf2d{ size.x, active_size.y }, color_scheme.dropdown_normal);

        if (selected_elements.size() > 1)
        {
            std::string temp_text = selected_elements[0].second.second + ", ...";
            auto element_text_size = pge->GetTextSizeProp(temp_text) * selected_elements[0].second.first;

            text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                absolute_position.y + (size.y / 2) - (element_text_size.y / 2) };
            pge->DrawStringPropDecal(text_position, temp_text, text_color, selected_elements[0].second.first);
        }
        else if (selected_elements.size() > 0)
        {
            auto element_text_size = pge->GetTextSizeProp(selected_elements[0].second.second) * selected_elements[0].second.first;

            text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                absolute_position.y + (size.y / 2) - (element_text_size.y / 2) };
            pge->DrawStringPropDecal(text_position, selected_elements[0].second.second, text_color, selected_elements[0].second.first);
        }

        if (max_display_items > 0 && max_display_items < elements.size())
        {
            int i = 1;
            for (int j = item_start_index - 1; j < item_start_index + max_display_items - 1; j++)
            {
                auto element_text_size = pge->GetTextSizeProp(elements[j].second.second.second) * elements[j].second.second.first;
                if (active_size.y >= size.y * i)
                {
                    switch (elements[j].second.first)
                    {
                    case DropdownState::NONE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_normal);
                        break;
                    case DropdownState::HOVER:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_hover);
                        break;
                    case DropdownState::ACTIVE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_active);
                        break;
                    }
                }
                text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                    absolute_position.y + size.y + (size.y * i) - (size.y / 2) - (element_text_size.y / 2) };
                if (absolute_position.y + size.y + active_size.y > text_position.y + element_text_size.y)
                    pge->DrawStringPropDecal(text_position, elements[j].second.second.second, text_color, elements[j].second.second.first);
                i++;
            }

            if (is_open && (max_display_items < elements.size()))
            {
                float scroll_size = (size.y + active_size.y) / (elements.size() - max_display_items);
                float scroll_y_pos = ((item_start_index - 1) * scroll_size);
                scroll_y_pos = scroll_y_pos - (scroll_y_pos / (elements.size() - max_display_items));

                pge->FillRectDecal({ absolute_position.x + size.x - 3, absolute_position.y + scroll_y_pos },
                    { 3, scroll_size }, color_scheme.scroll_indicator);
            }
        }
        else
        {
            int i = 1;
            for (auto& element : elements)
            {
                auto element_text_size = pge->GetTextSizeProp(element.second.second.second) * element.second.second.first;
                if (active_size.y >= size.y * i)
                {
                    switch (element.second.first)
                    {
                    case DropdownState::NONE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_normal);
                        break;
                    case DropdownState::HOVER:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_hover);
                        break;
                    case DropdownState::ACTIVE:
                        pge->FillRectDecal(absolute_position + olc::vf2d{ 0.f, size.y * i }, size, color_scheme.combolist_active);
                        break;
                    }
                }
                text_position = olc::vf2d{ absolute_position.x + (size.x / 2) - (element_text_size.x / 2),
                    absolute_position.y + size.y + (size.y * i) - (size.y / 2) - (element_text_size.y / 2) };
                if (absolute_position.y + size.y + active_size.y > text_position.y + element_text_size.y)
                    pge->DrawStringPropDecal(text_position, element.second.second.second, text_color, element.second.second.first);
                i++;
            }
        }
    }

    void FUI_Combolist::input(olc::PixelGameEngine* pge)
    {
        if (pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y)
        {
            if (pge->GetMouse(1).bPressed)
            {
                selected_elements.clear();
                for (auto& element : elements)
                    element.second.first = DropdownState::NONE;
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
            if (max_display_items > 0 && max_display_items < elements.size()) // if we have a max display limit we want to run a slightly different method of checking input
            {
                int i = 1;
                for (int j = item_start_index - 1; j < item_start_index + max_display_items - 1; j++)
                {
                    if (pge->GetMousePos().x >= absolute_position.x &&
                        pge->GetMousePos().x <= absolute_position.x + size.x &&
                        pge->GetMousePos().y > absolute_position.y + (size.y * i) &&
                        pge->GetMousePos().y < absolute_position.y + (size.y * i) + size.y)
                    {
                        if (pge->GetMouse(0).bPressed)
                        {
                            bool did_find_element = false;
                            for (auto& sel_element : selected_elements)
                            {
                                if (sel_element.first == elements[j].first)
                                {
                                    did_find_element = true;
                                    int v = 0;
                                    for (auto& el : selected_elements)
                                    {
                                        if (el.first == elements[j].first)
                                        {
                                            elements[j].second.first = DropdownState::NONE;
                                            selected_elements.erase(selected_elements.begin() + v);
                                            break;
                                        }
                                        v++;
                                    }
                                    break;
                                }
                            }
                            if (!did_find_element)
                            {
                                elements[j].second.first = DropdownState::ACTIVE;
                                selected_elements.push_back(std::make_pair(elements[j].first, elements[j].second.second));
                            }
                        }
                        else if (elements[j].second.first != DropdownState::ACTIVE)
                            elements[j].second.first = DropdownState::HOVER;
                    }
                    else if (elements[j].second.first != DropdownState::ACTIVE)
                        elements[j].second.first = DropdownState::NONE;
                    i++;
                }
                if (pge->GetMousePos().x >= absolute_position.x &&
                    pge->GetMousePos().x <= absolute_position.x + size.x &&
                    pge->GetMousePos().y >= absolute_position.y &&
                    pge->GetMousePos().y <= absolute_position.y + size.y + active_size.y)
                {
                    if (elements.size() > max_display_items)
                    {
                        if (pge->GetMouseWheel() > 0)
                        {
                            if (item_start_index > 1)
                                item_start_index--;
                        }
                        else if (pge->GetMouseWheel() < 0)
                        {
                            if (item_start_index < (elements.size() - max_display_items + 1))
                                item_start_index++;
                        }
                    }
                }
            }
            else // if we don't have any max display limit
            {
                int i = 1;
                for (auto& element : elements)
                {
                    if (pge->GetMousePos().x >= absolute_position.x &&
                        pge->GetMousePos().x <= absolute_position.x + size.x &&
                        pge->GetMousePos().y > absolute_position.y + (size.y * i) &&
                        pge->GetMousePos().y < absolute_position.y + (size.y * i) + size.y)
                    {
                        if (pge->GetMouse(0).bPressed)
                        {
                            bool did_find_element = false;
                            for (auto& sel_element : selected_elements)
                            {
                                if (sel_element.first == element.first)
                                {
                                    did_find_element = true;
                                    int j = 0;
                                    for (auto& el : selected_elements)
                                    {
                                        if (el.first == element.first)
                                        {
                                            element.second.first = DropdownState::NONE;
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
                                element.second.first = DropdownState::ACTIVE;
                                selected_elements.push_back(std::make_pair(element.first, element.second.second));
                            }
                        }
                        else if (element.second.first != DropdownState::ACTIVE)
                            element.second.first = DropdownState::HOVER;
                    }
                    else if (element.second.first != DropdownState::ACTIVE)
                        element.second.first = DropdownState::NONE;
                    i++;
                }
            }
        }

        if (!(pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y + active_size.y) && pge->GetMouse(0).bPressed)
            is_open = false;

        if (is_open)
            is_focused = true;
        else
            is_focused = false;
    }

    /*
    ####################################################
    #               FUI_GROUPBOX START                 #
    ####################################################
    */
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
        absolute_position = get_absolute_position();
        auto text_size = pge->GetTextSizeProp(text) * text_scale;

        pge->FillRectDecal(absolute_position, size, color_scheme.groupbox_background);

        // top left outline
        pge->FillRectDecal(absolute_position, olc::vf2d{ (size.x / 2) - (text_size.x / 2), 1.f }, color_scheme.groupbox_outline);
        // top right outline
        pge->FillRectDecal(olc::vf2d{ absolute_position.x + (size.x / 2) + (text_size.x / 2), absolute_position.y },
            olc::vf2d{ size.x - (size.x / 2) - (text_size.x / 2), 1.f }, color_scheme.groupbox_outline);

        // left outline
        pge->FillRectDecal(absolute_position, olc::vf2d{ 1, size.y }, color_scheme.groupbox_outline);
        // right outline
        pge->FillRectDecal(olc::vf2d{ absolute_position.x + size.x - 1, absolute_position.y }, olc::vf2d{ 1.f, size.y }, color_scheme.groupbox_outline);
        // bottom outline
        pge->FillRectDecal(olc::vf2d{ absolute_position.x, absolute_position.y + size.y - 1 }, olc::vf2d{ size.x + 1.f, 1.f }, color_scheme.groupbox_outline);

        pge->DrawStringPropDecal(olc::vf2d{ absolute_position.x + (size.x / 2) - (text_size.x / 2), absolute_position.y - (text_size.y / 2) }, text, text_color);

    }

    /*
    ####################################################
    #               FUI_SLIDER START                   #
    ####################################################
    */
    FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        range = r;
        slider_value_holder_float = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        range = r;
        slider_value_holder_float = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        group = g;
        range = r;
        slider_value_holder_float = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vf2d r, float* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        group = g;
        range = r;
        slider_value_holder_float = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    //////

    FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vi2d r, int* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        range = r;
        slider_value_holder_int = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vi2d r, int* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        range = r;
        slider_value_holder_int = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vi2d r, int* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        group = g;
        range = r;
        slider_value_holder_int = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    FUI_Slider::FUI_Slider(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s, olc::vi2d r, int* vh, FUI_Slider::type s_type)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        group = g;
        range = r;
        slider_value_holder_int = vh;
        slider_type = s_type;
        ui_type = FUI_Type::SLIDER;
    }

    std::string FUI_Slider::to_string_with_precision(const float a_value, const int n = 6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    }

    void FUI_Slider::draw(olc::PixelGameEngine* pge)
    {
        absolute_position = get_absolute_position();

        // start with the value of the value_holder else set value to minimum in range
        if (run_once)
        {
            // check if there's negative values in the range
            if (range.x < 0)
                has_negative = true;
            switch (slider_type)
            {
            case type::FLOAT:
                if (*slider_value_holder_float < range.x)
                {
                    slider_value_float = range.x;
                    *slider_value_holder_float = range.x;
                }
                else
                    slider_value_float = *slider_value_holder_float;

                if (has_negative)
                {
                    if (slider_value_float < 0.0f)
                        slider_ratio = (1.0f - (slider_value_float / range.x)) * 0.5;
                    else if (slider_value_float > 0.0f)
                        slider_ratio = (1.0f + (slider_value_float / range.y)) * 0.5;
                    else
                        slider_ratio = 0.5f;
                }
                else
                    slider_ratio = slider_value_float / range.y;
                break;
            case type::INT:
                if (*slider_value_holder_int < range.x)
                {
                    slider_value_int = range.x;
                    *slider_value_holder_int = range.x;
                }
                else
                    slider_value_int = *slider_value_holder_int;

                if (has_negative)
                {
                    if (slider_value_int < 0)
                        slider_ratio = (1.0f - (slider_value_int / range.x)) * 0.5;
                    else if (slider_value_int > 0)
                        slider_ratio = (1.0f + (slider_value_int / range.y)) * 0.5;
                    else
                        slider_ratio = 0.5f;
                }
                else
                    slider_ratio = slider_value_int / range.y;
                break;
            }

            run_once = false;
        }

        // draw title with slider value
        std::string temp_text;

        switch (slider_type)
        {
        case type::FLOAT:
            temp_text = "[" + to_string_with_precision(slider_value_float, 2) + "]";
            break;
        case type::INT:
            temp_text = "[" + std::to_string(slider_value_int) + "]";
            break;
        }

        auto text_size_title = pge->GetTextSizeProp(text) * text_scale;
        pge->DrawStringPropDecal(olc::vf2d{ absolute_position.x - text_size_title.x, absolute_position.y + (size.y / 2) - (text_size_title.y / 2) + 1 }, text, text_color);
        // draw slider body
        switch (state)
        {
        case State::NONE:
            pge->FillRectDecal(absolute_position, olc::vf2d{ size.x * slider_ratio, size.y }, color_scheme.slider_normal);
            break;
        case State::HOVER:
            pge->FillRectDecal(absolute_position, olc::vf2d{ size.x * slider_ratio, size.y }, color_scheme.slider_hover);
            break;
        case State::ACTIVE:
            pge->FillRectDecal(absolute_position, olc::vf2d{ size.x * slider_ratio, size.y }, color_scheme.slider_hover);
            break;
        }

        // Draw text ontop of the slider body
        auto text_size = pge->GetTextSizeProp(temp_text) * text_scale;
        pge->DrawStringPropDecal(olc::vf2d{ absolute_position.x + size.x / 2 - text_size.x / 2, absolute_position.y + (size.y / 2) - (text_size.y / 2) + 1 }, temp_text, text_color);

        // top left outline
        pge->FillRectDecal(absolute_position, olc::vf2d{ size.x, 1.f }, color_scheme.slider_outline);
        // left outline
        pge->FillRectDecal(absolute_position, olc::vf2d{ 1.f, size.y }, color_scheme.slider_outline);
        // right outline
        pge->FillRectDecal(olc::vf2d{ absolute_position.x + size.x - 1, absolute_position.y }, olc::vf2d{ 1.f, size.y }, color_scheme.slider_outline);
        // bottom outline
        pge->FillRectDecal(olc::vf2d{ absolute_position.x, absolute_position.y + size.y }, olc::vf2d{ size.x, 1.f }, color_scheme.slider_outline);
    }

    void FUI_Slider::input(olc::PixelGameEngine* pge)
    {
        if (pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y)
        {
            state = State::HOVER;
            if (pge->GetMouse(0).bHeld)
            {
                state = State::ACTIVE;
                is_focused = true;
            }
        }
        else if (state != State::ACTIVE)
            state = State::NONE;

        if (pge->GetMouse(0).bReleased)
            state = State::NONE;

        if (state == State::ACTIVE)
        {
            if (has_negative)
                if (((pge->GetMouseX() - (absolute_position.x)) / size.x) <= 0.5)
                {
                    ratio = (-1.0f * (pge->GetMouseX() - (absolute_position.x)) / size.x) * 2.0f;
                }
                else
                    ratio = -1.0f + ((pge->GetMouseX() - (absolute_position.x)) / size.x) * 2;

            slider_ratio = (pge->GetMouseX() - (absolute_position.x)) / size.x;

            if (slider_ratio <= 0.0f)
                slider_ratio = 0.0f;
            else if (slider_ratio >= 1.0f)
                slider_ratio = 1.0f;

            if (slider_ratio <= 0.0f)
                ratio = 0.0f;
            else if (slider_ratio >= 1.0f)
                ratio = 1.0f;

            switch (slider_type)
            {
            case type::FLOAT:
                if (has_negative)
                {
                    if (ratio <= 0.0f)
                        slider_value_float = range.x * (1.0f - (-1.0f * ratio));
                    else
                        slider_value_float = range.y * ratio;
                }
                else
                    slider_value_float = range.y * slider_ratio;

                if (slider_value_float < range.x)
                    slider_value_float = range.x;
                else if (slider_value_float > range.y)
                    slider_value_float = range.y;

                *slider_value_holder_float = slider_value_float;
                break;
            case type::INT:
                if (has_negative)
                {
                    if (ratio <= 0.0f)
                        slider_value_int = range.x * (1.0f - (-1.0f * ratio));
                    else
                        slider_value_int = range.y * ratio;
                }
                else
                    slider_value_int = range.y * slider_ratio;

                if (slider_value_int < range.x)
                    slider_value_int = range.x;
                else if (slider_value_int > range.y)
                    slider_value_int = range.y;

                *slider_value_holder_int = slider_value_int;
                break;
            }
        }

        if (pge->GetMouse(0).bReleased)
            is_focused = false;
    }

    /*
    ####################################################
    #               FUI_TEXTFIELD START                #
    ####################################################
    */
    FUI_Inputfield::FUI_Inputfield(const std::string& id, FUI_Window* pt, const std::string& t, olc::vi2d p, olc::vi2d s)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        ui_type = FUI_Type::INPUTFIELD;
    }

    FUI_Inputfield::FUI_Inputfield(const std::string& id, const std::string& t, olc::vi2d p, olc::vi2d s)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        ui_type = FUI_Type::INPUTFIELD;
    }

    FUI_Inputfield::FUI_Inputfield(const std::string& id, FUI_Window* pt, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
    {
        identifier = id;
        text = t;
        size = s;
        parent = pt;
        position = p;
        group = g;
        ui_type = FUI_Type::INPUTFIELD;
    }

    FUI_Inputfield::FUI_Inputfield(const std::string& id, const std::string& g, const std::string& t, olc::vi2d p, olc::vi2d s)
    {
        identifier = id;
        text = t;
        size = s;
        position = p;
        group = g;
        ui_type = FUI_Type::INPUTFIELD;
    }

    bool FUI_Inputfield::is_textkey_pressed(olc::PixelGameEngine* pge, const TextKey& key)
    {
        int vTextKey = 0;
        switch (key)
        {
        default:                        vTextKey = olc::NONE;        break;
        case TextKey::A:                vTextKey = olc::A;           break;
        case TextKey::B:                vTextKey = olc::B;           break;
        case TextKey::C:                vTextKey = olc::C;           break;
        case TextKey::D:                vTextKey = olc::D;           break;
        case TextKey::E:                vTextKey = olc::E;           break;
        case TextKey::F:                vTextKey = olc::F;           break;
        case TextKey::G:                vTextKey = olc::G;           break;
        case TextKey::H:                vTextKey = olc::H;           break;
        case TextKey::I:                vTextKey = olc::I;           break;
        case TextKey::J:                vTextKey = olc::J;           break;
        case TextKey::K:                vTextKey = olc::K;           break;
        case TextKey::L:                vTextKey = olc::L;           break;
        case TextKey::M:                vTextKey = olc::M;           break;
        case TextKey::N:                vTextKey = olc::N;           break;
        case TextKey::O:                vTextKey = olc::O;           break;
        case TextKey::P:                vTextKey = olc::P;           break;
        case TextKey::Q:                vTextKey = olc::Q;           break;
        case TextKey::R:                vTextKey = olc::R;           break;
        case TextKey::S:                vTextKey = olc::S;           break;
        case TextKey::T:                vTextKey = olc::T;           break;
        case TextKey::U:                vTextKey = olc::U;           break;
        case TextKey::V:                vTextKey = olc::V;           break;
        case TextKey::W:                vTextKey = olc::W;           break;
        case TextKey::X:                vTextKey = olc::X;           break;
        case TextKey::Y:                vTextKey = olc::Y;           break;
        case TextKey::Z:                vTextKey = olc::Z;           break;
        case TextKey::Num0:             vTextKey = olc::K0;          break;
        case TextKey::Num1:             vTextKey = olc::K1;          break;
        case TextKey::Num2:             vTextKey = olc::K2;          break;
        case TextKey::Num3:             vTextKey = olc::K3;          break;
        case TextKey::Num4:             vTextKey = olc::K4;          break;
        case TextKey::Num5:             vTextKey = olc::K5;          break;
        case TextKey::Num6:             vTextKey = olc::K6;          break;
        case TextKey::Num7:             vTextKey = olc::K7;          break;
        case TextKey::Num8:             vTextKey = olc::K8;          break;
        case TextKey::Num9:             vTextKey = olc::K9;          break;

        case TextKey::LBracket:         vTextKey = olc::OEM_4;       break;
        case TextKey::RBracket:         vTextKey = olc::OEM_6;       break;
        case TextKey::Semicolon:        vTextKey = olc::OEM_1;       break;
        case TextKey::Comma:            vTextKey = olc::COMMA;       break;
        case TextKey::Period:           vTextKey = olc::PERIOD;      break;
        case TextKey::Quote:            vTextKey = olc::OEM_7;       break;
        case TextKey::ForwardSlash:     vTextKey = olc::OEM_2;       break;
        case TextKey::BackwardSlash:    vTextKey = olc::OEM_5;       break;
        case TextKey::Tilda:            vTextKey = olc::OEM_3;       break;
        case TextKey::Equal:            vTextKey = olc::EQUALS;      break;
        case TextKey::Hyphen:           vTextKey = olc::MINUS;       break;

        case TextKey::Space:            vTextKey = olc::SPACE;       break;
        }

        return pge->GetKey((olc::Key)vTextKey).bPressed;
    }

    int FUI_Inputfield::get_char_id(olc::PixelGameEngine* pge)
    {
        for (int i = 0; i < text_keys; i++) {
            if (is_textkey_pressed(pge, (TextKey)i)) {
                return i;
            }
        }
        return static_cast<int>(TextKey::None);
    }

    std::string FUI_Inputfield::get_char_from_id(olc::PixelGameEngine* pge)
    {
        int index = get_char_id(pge);
        if (index == static_cast<int>(TextKey::None)) return "";

        if (pge->GetKey(olc::SHIFT).bHeld) {
            return std::string(1, text_shift[index]);
        }

        return std::string(1, text_noshift[index]);
    }

    void FUI_Inputfield::draw(olc::PixelGameEngine* pge)
    {
        absolute_position = get_absolute_position();
        auto title_text_size = pge->GetTextSizeProp(text) * text_scale;
        auto display_text_size = pge->GetTextSizeProp(displayed_text) * input_scale + olc::vf2d{ 2.f, 0.f };
        // title text
        auto text_position = olc::vf2d{ absolute_position.x - title_text_size.x, absolute_position.y + (size.y / 2) - (title_text_size.y / 2) };
        auto timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto cursor_size = pge->GetTextSizeProp("_");

        pge->DrawStringPropDecal(text_position, text, text_color, text_scale);

        // outline
        pge->FillRectDecal(absolute_position, size, color_scheme.inputfield_outline);
        // background
        pge->FillRectDecal(absolute_position + olc::vf2d{ 1.0f, 1.0f }, size - olc::vf2d{ 2.0f, 2.0f }, color_scheme.inputfield_background);
        if (select_all)
            pge->FillRectDecal(absolute_position, olc::vf2d(display_text_size.x * text_scale.x, size.y), color_scheme.inputfield_select_all_background);
        
        // render the text ( + 3 in text_position is used as an offset to not render the first letter inside of the outline)
        text_position = olc::vf2d{ absolute_position.x + 3, absolute_position.y + (size.y / 2) - (display_text_size.y / 2) };
        auto cursor_position = olc::vf2d{ text_position.x + display_text_size.x, text_position.y + display_text_size.y };

        if (display_text_size.x <= size.x && inputfield_text.size() > old_inputfield_text.size())
        {
            if (mask_inputfield)
                displayed_text += "*";
            else
                displayed_text += inputfield_text.back();
            old_inputfield_text = inputfield_text;
        }
        else if (display_text_size.x >= size.x - 1)
        {
            text_out_of_view.push_back(displayed_text.front());
            displayed_text.erase(0, 1);
        }

        if (clear_inputfield)
        {
            inputfield_text.clear();
            displayed_text.clear();
            text_out_of_view.clear();
            old_inputfield_text.clear();

            clear_inputfield = false;
        }

        pge->DrawStringPropDecal(text_position, displayed_text, text_color, input_scale);

        if (cursor_position.x + (cursor_size.x * input_scale.x) > absolute_position.x + size.x)
            cursor_position.x -= (cursor_position.x + (cursor_size.x * input_scale.x)) - (absolute_position.x + size.x);

        if (state == State::ACTIVE)
        {
            if (timer - last_cursor_tick > 500)
            {
                if (timer - last_cursor_tick > 1500)
                    last_cursor_tick = timer;
                pge->FillRectDecal(cursor_position, { cursor_size.x * input_scale.x, 1.f }, color_scheme.inputfield_cursor);
            }
        }
    }

    void FUI_Inputfield::input(olc::PixelGameEngine* pge)
    {
        if (pge->GetMousePos().x >= absolute_position.x &&
            pge->GetMousePos().x <= absolute_position.x + size.x &&
            pge->GetMousePos().y >= absolute_position.y &&
            pge->GetMousePos().y <= absolute_position.y + size.y)
        {
            if (pge->GetMouse(0).bPressed)
            {
                is_focused = true;
                last_cursor_tick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 500;
            }
        }
        else if (pge->GetMouse(0).bPressed && is_focused)
            is_focused = false;

        if (pge->GetKey(olc::ESCAPE).bPressed)
            is_focused = false;

        if (pge->GetKey(olc::ENTER).bPressed)
        {
            if (input_enter_callback)
                input_enter_callback();
        }

        if (is_focused)
        {
            if (pge->GetKey(olc::CTRL).bHeld && pge->GetKey(olc::A).bPressed)
                select_all = true;

            // Clear text
            if ((select_all && get_char_from_id(pge).size() > 0 && !pge->GetKey(olc::CTRL).bHeld) ||
                (select_all && pge->GetKey(olc::BACK).bPressed))
            {
                inputfield_text.clear();
                displayed_text.clear();
                text_out_of_view.clear();
                old_inputfield_text.clear();
                select_all = false;
            }
            // Remove last character if backspace is pressed
            if (pge->GetKey(olc::BACK).bPressed && !select_all && inputfield_text.size() > 0)
            {
                inputfield_text.pop_back();
                displayed_text.pop_back();
                old_inputfield_text.pop_back();
                if (text_out_of_view.size() > 0)
                {
                    displayed_text.insert(0, &text_out_of_view.back());
                    text_out_of_view.pop_back();
                }
            }

            // Append character to string
            if (!pge->GetKey(olc::CTRL).bHeld)
                inputfield_text.append(get_char_from_id(pge));
        }

        if (is_focused)
            state = State::ACTIVE;
        else
            state = State::NONE;
    }

    FUI_Console::FUI_Console(const std::string& id, FUI_Window* parent, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness = 10)
    {
        identifier = id;
        this->parent = parent;
        text = title;
        this->position = position;
        this->size = size;
        this->input_thickness = input_thickness;
        inputfield.set_size({ size.x, input_thickness });
        ui_type = FUI_Type::CONSOLE;
    }

    FUI_Console::FUI_Console(const std::string& id, FUI_Window* parent, const std::string& group, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness = 10)
    {
        identifier = id;
        this->parent = parent;
        text = title;
        this->position = position;
        this->size = size;
        this->group = group;
        this->input_thickness = input_thickness;
        inputfield.set_size({ size.x, input_thickness });
        ui_type = FUI_Type::CONSOLE;
    }

    FUI_Console::FUI_Console(const std::string& id, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness = 10)
    {
        identifier = id;
        this->parent = parent;
        text = title;
        this->position = position;
        this->size = size;
        this->input_thickness = input_thickness;
        inputfield.set_size({ size.x, input_thickness });
        ui_type = FUI_Type::CONSOLE;
    }

    FUI_Console::FUI_Console(const std::string& id, const std::string& group, const std::string& title, olc::vi2d position, olc::vi2d size, int input_thickness = 10)
    {
        identifier = id;
        this->parent = parent;
        text = title;
        this->position = position;
        this->size = size;
        this->group = group;
        this->input_thickness = input_thickness;
        inputfield.set_size({ size.x, input_thickness });
        ui_type = FUI_Type::CONSOLE;
    }

    void FUI_Console::draw(olc::PixelGameEngine* pge)
    {
        absolute_position = get_absolute_position();

        inputfield.inputfield_scale(text_scale);
        inputfield.set_position({ absolute_position.x, absolute_position.y + size.y - input_thickness});

        // outline
        pge->FillRectDecal(absolute_position, { size.x , size.y - input_thickness }, color_scheme.console_outline);
        // body
        pge->FillRectDecal({ absolute_position.x + 1, absolute_position.y + 1 }, { size.x - 2, size.y - input_thickness - 2 }, color_scheme.console_background);

        // title text
        auto title_size = pge->GetTextSizeProp(text) * text_scale;
        auto text_pos = olc::vf2d{ absolute_position.x + (size.x / 2) - (title_size.x / 2) , absolute_position.y + 1 };
        pge->DrawStringPropDecal(text_pos, text, text_color, text_scale);
        pge->FillRectDecal({ absolute_position.x, absolute_position.y + title_size.y + 1}, { size.x, 1 }, color_scheme.console_outline);

        if (run_once)
        {
            scroll_threshold = size.y - input_thickness - title_size.y - 2;
            run_once = false;
        }

        // console text
        int j = 0;
        commands_shown = 0;
        for (int i = scroll_index; i < executed_commands.size(); i++)
        {
            auto text_size = pge->GetTextSizeProp(executed_commands[i]) * text_scale;
            if (title_size.y + (text_size.y * j) <= scroll_threshold)
            {
                pge->DrawStringPropDecal({ absolute_position.x, absolute_position.y + title_size.y + 2 + (text_size.y * j) }, executed_commands[i], text_color, text_scale);
                commands_shown++;
            }
            j++;
        }

        inputfield.draw(pge);
    }

    void FUI_Console::input(olc::PixelGameEngine* pge)
    {
        if (pge->GetKey(olc::ENTER).bPressed)
        {
            command = inputfield.get_inputfield_value();
            if (!command.empty())
            {
                command_handler(command, &executed_command);
                std::string temp1 = get_time() + " - " + executed_command;
                auto text_size = pge->GetTextSizeProp(temp1) * text_scale;
                auto size_to_remove = 0.f;
                while (text_size.x > size.x)
                {
                    text_size = pge->GetTextSizeProp(temp1) * text_scale;
                    size_to_remove = text_size.x - size.x;
                    size_to_remove = size_to_remove / text_size.x;
                    size_to_remove = size_to_remove * temp1.size();
                    size_to_remove = temp1.size() - std::ceil(size_to_remove);
                    if (size_to_remove < temp1.size())
                        temp1.erase(size_to_remove, temp1.size());
                    else
                        break;
                }
                executed_commands.push_back(temp1);
                inputfield.clear_inputfield_value();

                auto title_size = pge->GetTextSizeProp(text) * text_scale;
                auto current_visible = executed_commands.size();
                if (title_size.y + (text_size.y * commands_shown) >= scroll_threshold)
                    can_scroll = true;
                else
                    can_scroll = false;

                if (can_scroll)
                    scroll_index++;

                if (title_size.y + (text_size.y * executed_commands.size()) >= scroll_threshold)
                    can_scroll = true;
                else
                    can_scroll = false;
            }
        }
        if (can_scroll)
        {
            if (pge->GetMouseWheel() > 0)
            {
                if (scroll_index > 0)
                    scroll_index--;
            }
            else if (pge->GetMouseWheel() < 0)
            {
                if (scroll_index < executed_commands.size() - 1)
                    scroll_index++;
            }
        }
        inputfield.input(pge);
    }

    /*
    ####################################################
    #               FUI_HANDLER START                  #
    ####################################################
    */
    bool FrostUI::is_a_window_focused()
    {
        for (auto& window : windows)
        {
            if (window->is_focused())
                return true;
        }
        return false;
    }

    bool FrostUI::disable_window_input_if_open_dropdown(int window_index)
    {
        for (auto element : elements)
        {
            if (!element->get_parent() || windows[window_index]->get_id() != element->get_parent()->get_id())
                continue;
            if (element->get_ui_type() == FUI_Type::DROPDOWN || element->get_ui_type() == FUI_Type::COMBOLIST)
            {
                auto adaptive = element->get_absolute_position();
                auto size = element->get_size();
                auto position = element->get_position();
                auto amount = element->get_elements_amount();
                if (element->get_focused_status() && (pge->GetMousePos().x >= adaptive.x + position.x &&
                    pge->GetMousePos().x <= adaptive.x + position.x + size.x &&
                    pge->GetMousePos().y >= adaptive.y + position.y &&
                    pge->GetMousePos().y <= adaptive.y + position.y + (size.y * amount) + size.y))
                    return true;
            }
                    
        }
        return false;
    }

    void FrostUI::cycle_inputfield()
    {
        if (pge->GetKey(olc::TAB).bPressed)
        {
            int i = 0;
            int j = 0;
            bool input_was_focused = false;
            for (auto& element : elements)
            {
                if (element->get_focused_status() && element->get_ui_type() == FUI_Type::INPUTFIELD)
                {
                    element->set_focused_status(false);
                    input_was_focused = true;
                    break;
                }
                i++;
            }
            for (auto& element : elements)
            {
                if (element->get_ui_type() == FUI_Type::INPUTFIELD && j > i && input_was_focused)
                {
                    element->set_focused_status(true);
                    break;
                }
                j++;
            }
        }
    }

    void FrostUI::push_focused_to_back()
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

    void FrostUI::push_focused_element_to_back()
    {
        int i = 0;
        for (auto& element : elements)
        {
            if (element->get_focused_status())
            {
                elements.push_back(element);
                elements.erase(elements.begin() + i);
            }
            i++;
        }
    }

    void FrostUI::set_active_window(const std::string& window_id)
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

    void FrostUI::set_active_group(const std::string& g)
    {
        for (auto group : groups)
        {
            if (group.second == g)
            {
                active_group.first = group.first;
                active_group.second = group.second;
                break;
            }
            else
            {
                active_group.first.clear();
                active_group.second.clear();
            }
        }
        if (active_group.first.empty() && active_group.second.empty())
            std::cout << "Could not find the group ID in added windows (function affected: set_active_group, affected window_id: " + g + ")\n";
    }

    FUI_Window* FrostUI::create_window(const std::string& identifier, const std::string& title, olc::vi2d position, olc::vi2d size)
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

    void FrostUI::add_group(const std::string& window_id, const std::string& group_id)
    {
        bool is_duplicate = false;
        for (auto group : groups)
        {
            if (group.second == group_id)
                is_duplicate = true;
        }
        if (!is_duplicate)
            groups.push_back(std::make_pair(window_id, group_id));
        else
            std::cout << "Cannot add duplicates of same group (function affected: add_group, affected group_id: " + group_id + ")\n";
    }

    void FrostUI::clear_active_window()
    {
        active_window_id.clear();
    }

    void FrostUI::clear_active_group()
    {
        active_group.first.clear();
        active_group.second.clear();
    }

    const std::string& FrostUI::get_active_group()
    {
        return active_group.second;
    }

    FUI_Window* FrostUI::find_window(const std::string& identifier)
    {
        for (auto& window : windows)
        {
            if (window->get_id() == identifier)
                return window;
        }
        std::cout << "Could not find the window ID in added windows (function affected: find_window, affected window_id: " + identifier + ")\n";
        return nullptr;
    }

    int FrostUI::get_element_amount() { return elements.size(); }

    void FrostUI::remove_element(const std::string& id)
    {
        int i = 0;
        for (auto& element : elements)
        {
            if (element->get_identifier() == id)
            {
                elements.erase(elements.begin() + i);
                break;
            }
            i++;
        }
    }

    std::shared_ptr<FUI_Element> FrostUI::find_element(const std::string& id)
    {
        for (auto& element : elements)
        {
            if (element->get_identifier() == id)
                return element;
        }
        return nullptr;
    }

    std::shared_ptr<FUI_Element> FrostUI::find_groupbox(const std::string& id)
    {
        for (auto& element : groupboxes)
        {
            if (element->get_identifier() == id)
                return element;
        }
        return nullptr;
    }

    void FrostUI::add_label(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Label>(identifier, window, text, position));
                        else
                            elements.push_back(std::make_shared<FUI_Label>(identifier, window, active_group.second, text, position));
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

    void FrostUI::add_label(const std::string& identifier, const std::string& text, olc::vi2d position)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Label>(identifier, window, active_group.second, text, position));
                        else
                            elements.push_back(std::make_shared<FUI_Label>(identifier, window, text, position));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Label>(identifier, active_group.second, text, position));
                else
                    elements.push_back(std::make_shared<FUI_Label>(identifier, text, position));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_label, label_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_checkbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_front(std::make_shared<FUI_Checkbox>(identifier, window, text, position, size, cb_state));
                        else
                            elements.push_front(std::make_shared<FUI_Checkbox>(identifier, window, active_group.second, text, position, size, cb_state));
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

    void FrostUI::add_checkbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, bool* cb_state)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_front(std::make_shared<FUI_Checkbox>(identifier, window, active_group.second, text, position, size, cb_state));
                        else
                            elements.push_front(std::make_shared<FUI_Checkbox>(identifier, window, text, position, size, cb_state));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_front(std::make_shared<FUI_Checkbox>(identifier, active_group.second, text, position, size, cb_state));
                else
                    elements.push_front(std::make_shared<FUI_Checkbox>(identifier, text, position, size, cb_state));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_checkbox, checkbox_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_dropdown(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Dropdown>(identifier, window, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Dropdown>(identifier, window, active_group.second, text, position, size));
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

    void FrostUI::add_dropdown(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Dropdown>(identifier, window, active_group.second, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Dropdown>(identifier, window, text, position, size));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Dropdown>(identifier, active_group.second, text, position, size));
                else
                    elements.push_back(std::make_shared<FUI_Dropdown>(identifier, text, position, size));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_dropdown, dropdown_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_combolist(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Combolist>(identifier, window, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Combolist>(identifier, window, active_group.second, text, position, size));
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

    void FrostUI::add_combolist(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Combolist>(identifier, window, active_group.second, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Combolist>(identifier, window, text, position, size));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Combolist>(identifier, active_group.second, text, position, size));
                else
                    elements.push_back(std::make_shared<FUI_Combolist>(identifier, text, position, size));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_combolist, combolist_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_groupbox(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, window, text, position, size));
                        else
                            groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, window, active_group.second, text, position, size));
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

    void FrostUI::add_groupbox(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, window, active_group.second, text, position, size));
                        else
                            groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, window, text, position, size));
                }
            }
            else
                if (!active_group.second.empty())
                    groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, active_group.second, text, position, size));
                else
                    groupboxes.push_back(std::make_shared<FUI_Groupbox>(identifier, text, position, size));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_groupbox, groupbox_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_float_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
                        else
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
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

    void FrostUI::add_float_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vf2d range, float* value_holder)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
                        else
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Slider>(identifier, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
                else
                    elements.push_back(std::make_shared<FUI_Slider>(identifier, text, position, size, range, value_holder, FUI_Slider::type::FLOAT));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_slider, slider_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_int_slider(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder, FUI_Slider::type::INT));
                        else
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::INT));
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

    void FrostUI::add_int_slider(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, olc::vi2d range, int* value_holder)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::INT));
                        else
                            elements.push_back(std::make_shared<FUI_Slider>(identifier, window, text, position, size, range, value_holder, FUI_Slider::type::INT));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Slider>(identifier, active_group.second, text, position, size, range, value_holder, FUI_Slider::type::INT));
                else
                    elements.push_back(std::make_shared<FUI_Slider>(identifier, text, position, size, range, value_holder, FUI_Slider::type::INT));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_slider, slider_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_button(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_front(std::make_shared<FUI_Button>(identifier, window, text, position, size, callback));
                        else
                            elements.push_front(std::make_shared<FUI_Button>(identifier, window, active_group.second, text, position, size, callback));
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

    void FrostUI::add_button(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, std::function<void()> callback)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_front(std::make_shared<FUI_Button>(identifier, window, active_group.second, text, position, size, callback));
                        else
                            elements.push_front(std::make_shared<FUI_Button>(identifier, window, text, position, size, callback));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_front(std::make_shared<FUI_Button>(identifier, active_group.second, text, position, size, callback));
                else
                    elements.push_front(std::make_shared<FUI_Button>(identifier, text, position, size, callback));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_button, button_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_inputfield(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Inputfield>(identifier, window, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Inputfield>(identifier, window, active_group.second, text, position, size));
                    else
                        std::cout << "Could not find parent window ID (function affected: add_inputfield, inputfield_id affected: " + identifier + ")\n";
                }
            }
            else
                std::cout << "There's no windows to be used as parent (function affected: add_inputfield, inputfield_id affected: " + identifier + ")\n";
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_inputfield, inputfield_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_inputfield(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Inputfield>(identifier, window, active_group.second, text, position, size));
                        else
                            elements.push_back(std::make_shared<FUI_Inputfield>(identifier, window, text, position, size));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Inputfield>(identifier, active_group.second, text, position, size));
                else
                    elements.push_back(std::make_shared<FUI_Inputfield>(identifier, text, position, size));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_inputfield, inputfield_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_console(const std::string& parent_id, const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, int inputfield_thickness)
    {
        if (!find_element(identifier))
        {
            if (windows.size() > 0)
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == parent_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Console>(identifier, window, text, position, size, inputfield_thickness));
                        else
                            elements.push_back(std::make_shared<FUI_Console>(identifier, window, active_group.second, text, position, size, inputfield_thickness));
                    else
                        std::cout << "Could not find parent window ID (function affected: add_console, console_id affected: " + identifier + ")\n";
                }
            }
            else
                std::cout << "There's no windows to be used as parent (function affected: add_console, console_id affected: " + identifier + ")\n";
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_console, console_id affected: " + identifier + ")\n";
    }

    void FrostUI::add_console(const std::string& identifier, const std::string& text, olc::vi2d position, olc::vi2d size, int inputfield_thickness)
    {
        if (!find_element(identifier))
        {
            if (!active_window_id.empty())
            {
                for (auto& window : windows)
                {
                    if (window->get_id() == active_window_id)
                        if (!active_group.second.empty())
                            elements.push_back(std::make_shared<FUI_Console>(identifier, window, active_group.second, text, position, size, inputfield_thickness));
                        else
                            elements.push_back(std::make_shared<FUI_Console>(identifier, window, text, position, size, inputfield_thickness));
                }
            }
            else
                if (!active_group.second.empty())
                    elements.push_back(std::make_shared<FUI_Console>(identifier, active_group.second, text, position, size, inputfield_thickness));
                else
                    elements.push_back(std::make_shared<FUI_Console>(identifier, text, position, size, inputfield_thickness));
        }
        else
            std::cout << "Duplicate IDs found (function affected: add_inputfield, inputfield_id affected: " + identifier + ")\n";
    }

    void FrostUI::run()
    {
        // Cycle the inputfields before anything is drawn
        cycle_inputfield();

        // run this only once to prime the window focusing system
        if (prime_window_focusing)
        {
            push_focused_to_back();
            prime_window_focusing = false;
        }

        if (trigger_pushback.first)
            push_focused_element_to_back();

        // Draw standalone elements first (standalone elements are elements without a parent / window)
        for (auto& g : groupboxes)
        {
            if (!g)
                continue;
            if (!g->get_group().empty())
                if (!active_group.second.empty())
                    if (!g->get_parent() && active_group.first.size() < 1)
                        if (g->get_group() != active_group.second || g->get_group().empty())
                            continue;
            if (!g->get_group().empty() && (active_group.first.empty() && active_group.second.empty()))
                continue;
            if (!g->get_parent())
                g->draw(pge);
        }

        for (auto& e : elements)
        {
            if (!e)
                continue;
            if (!e->get_group().empty())
                if (!active_group.second.empty())
                    if (!e->get_parent() && active_group.first.size() < 1)
                        if (e->get_group() != active_group.second || e->get_group().empty())
                            continue;
            if (!e->get_group().empty() && (active_group.first.empty() && active_group.second.empty()))
                continue;
            // reset top priority if not focused anymore
            if (trigger_pushback.second && !e->get_focused_status() && trigger_pushback.second->get_identifier() == e->get_identifier())
            {
                trigger_pushback.first = false;
                trigger_pushback.second = nullptr;
            }
            if (e->get_focused_status() && e->get_ui_type() != FUI_Type::INPUTFIELD)
            {
                trigger_pushback.first = true;
                trigger_pushback.second = e;
            }
            if (!e->get_parent())
            {
                if (windows.size() > 0)
                {
                    for (auto& window : windows)
                    {
                        if (window->is_focused())
                            continue;
                        if (trigger_pushback.second)
                        {
                            if (trigger_pushback.second->get_identifier() == e->get_identifier())
                            {
                                e->input(pge);
                            }
                        }
                        else
                            e->input(pge);
                    }
                }
                else
                {
                    if (trigger_pushback.second)
                    {
                        if (trigger_pushback.second->get_identifier() == e->get_identifier())
                        {
                            e->input(pge);
                        }
                    }
                    else
                        e->input(pge);
                }
                e->draw(pge);
            }
        }

        // Draw windows first
        if (windows.size() > 0)
        {
            // make sure input is run in reverse order of drawing to not allow through window presses when out of focus
            for (int i = windows.size() - 1; i >= 0; i--)
            {
                if (!windows[i]->get_closed_state())
                {
                    if (!disable_window_input_if_open_dropdown(i))
                        windows[i]->input(windows);
                }
            }

            for (auto& window : windows)
            {
                if (window->get_closed_state())
                {
                    if (window->is_focused())
                        window->set_focused(false);
                    continue;
                }

                if (window->is_focused())
                    current_focused_window = window->get_id();

                window->draw();
                for (auto& g : groupboxes)
                {
                    if (!g)
                        continue;
                    if (!g->get_group().empty())
                        if (!active_group.second.empty())
                            if (g->get_parent() && g->get_parent()->get_id() == active_group.first)
                                if (g->get_group() != active_group.second || g->get_group().empty())
                                    continue;
                    if (!g->get_group().empty() && (active_group.first.empty() && active_group.second.empty()))
                        continue;
                    if (g->get_parent() && g->get_parent()->get_id() == window->get_id())
                        g->draw(pge);
                }

                // first = FUI_Type, second = FUI_Element
                for (auto& e : elements)
                {
                    if (!e)
                        continue;
                    if (!e->get_group().empty())
                        if (!active_group.second.empty())
                            if (e->get_parent() && e->get_parent()->get_id() == active_group.first)
                                if (e->get_group() != active_group.second || e->get_group().empty())
                                    continue;
                    if (!e->get_group().empty() && (active_group.first.empty() && active_group.second.empty()))
                        continue;
                    // reset top priority if not focused anymore
                    if (trigger_pushback.second && !e->get_focused_status() && trigger_pushback.second->get_identifier() == e->get_identifier())
                    {
                        trigger_pushback.first = false;
                        trigger_pushback.second = nullptr;
                    }
                    if (e->get_focused_status() && e->get_ui_type() != FUI_Type::INPUTFIELD)
                    {
                        trigger_pushback.first = true;
                        trigger_pushback.second = e;
                    }
                    if (e->get_parent())
                    {
                        if (e->get_parent()->get_id() == window->get_id())
                        {
                            e->draw(pge);
                            if (window->is_focused())
                            {
                                if (trigger_pushback.second)
                                {
                                    if (trigger_pushback.second->get_identifier() == e->get_identifier())
                                        e->input(pge);
                                }
                                else
                                    e->input(pge);
                            }
                            else
                                e->set_focused_status(false);
                        }
                        else
                            continue;
                    }
                }
            }
            if (!is_a_window_focused())
                current_focused_window = "";
            // arrange the deques containing the windows
            if (current_focused_window != saved_focused_window)
            {
                // change window focus
                push_focused_to_back();

                for (auto& e : elements)
                {
                    if (!e)
                        continue;
                    if (!e->get_group().empty())
                        if (!active_group.second.empty())
                            if (e->get_parent() && e->get_parent()->get_id() == active_group.first)
                                if (e->get_group() != active_group.second || e->get_group().empty())
                                    continue;
                    if (!e->get_group().empty() && (active_group.first.empty() && active_group.second.empty()))
                        continue;

                    if (e->get_parent())
                    {
                        if (e->get_parent()->get_id() == saved_focused_window)
                            e->input(pge);
                    }
                }
            }
            saved_focused_window = current_focused_window;
        }
    }
}
#endif

#endif // OLC_PGEX_FROSTUI.h