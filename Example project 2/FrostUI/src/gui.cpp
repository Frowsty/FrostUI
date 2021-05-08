#define OLC_PGEX_FUI
#include "headers/gui.h"

void GUI::create()
{
    // create groups for the tabs (leave window_id blank if there's no window)
    frost_ui.add_group("", "generate_tab");
    frost_ui.add_group("", "save_tab");

    frost_ui.add_groupbox("main_groupbox", "", { 0, 0 }, { 500, 300 });

    // create tabs
    const auto tab_amount = 2;
    const auto tab_width = 500 / tab_amount;
    const auto tab_height = 20;

    frost_ui.add_button("gen_tab", "Password Generator", { 0, 0 }, { tab_width, tab_height }, [&] { frost_ui.set_active_group("generate_tab"); });
    frost_ui.add_button("sv_tab", "Store Passwords", { tab_width, 0 }, { tab_width, tab_height }, [&] { frost_ui.set_active_group("save_tab"); });

    frost_ui.set_active_group("generate_tab");
    // inputfield for the password
    frost_ui.add_label("generated_pw_title", "Generated Password: ", { 8, tab_height + 10});
    frost_ui.find_element("generated_pw_title")->scale_text({ 1.0f, 1.55f });

    frost_ui.add_label("generated_pw", "----", { 143, tab_height + 10 });
    frost_ui.find_element("generated_pw")->scale_text({ 1.0f, 1.55f });
    frost_ui.find_element("generated_pw")->set_text_color(olc::DARK_RED);

    // slider for password length
    frost_ui.add_int_slider("pw_len", "Length: ", { 140, tab_height + 40 }, { 200, 10 }, { 1, 40 }, &password_length);
    frost_ui.find_element("pw_len")->set_slider_value(5);

    frost_ui.add_button("generate_button", "Generate Password", { 140, 90 }, { 200, 20 }, [&] 
        { 
            frost_ui.find_element("generated_pw")->set_text(generator.generate(password_length));
            frost_ui.find_element("generated_pw")->set_text_color(olc::DARK_GREEN);
        });

    // button to generate the password
}

void GUI::run()
{
    frost_ui.run();
}