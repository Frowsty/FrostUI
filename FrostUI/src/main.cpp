#define OLC_PGE_APPLICATION
#define OLC_GFX_OPENGL33

#include "headers/olcPixelGameEngine.h"
#include "headers/olcPGEX_FrostUI.h"

class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "Example";
    }

    olcPGEX_FrostUI frost_ui;

    int i = 0;
    int j = 0;

    bool checkbox_state = false;
    bool last_cb_state = checkbox_state;
    bool button_state = false;
    bool last_btn_state = button_state;

    std::string current_element = "";
    std::string old_element = "";

    std::vector<std::string> current_elements;
    std::vector<std::string> old_elements;

    float slider_value = 0.0f;
    float old_slider_value = slider_value;
public:
    bool OnUserCreate() override
    {
        // Create all windows
        auto main_window = frost_ui.create_window("main_window", { 10, 25 }, { 490, 250 }, "New Window");
        auto new_window1 = frost_ui.create_window("new_window", { 520, 25 }, { 490, 250 }, "New Window");
        auto new_window2 = frost_ui.create_window("new_window2", { 520, 300 }, { 490, 250 }, "New Window");
        auto new_window3 = frost_ui.create_window("new_window3", { 10, 300 }, { 490, 250 }, "New Window");
        auto new_window4 = frost_ui.create_window("new_window4", { 300, 200 }, { 490, 250 }, "New Window");

        // Create groups for respective tabs
        frost_ui.add_group("tab_1");
        frost_ui.add_group("tab_2");
        frost_ui.add_group("tab_3");

        frost_ui.set_active_window("new_window");

        frost_ui.add_groupbox("groupbox1", "This is a groupbox", { 5, 10 }, { 210, 120 });
        auto groupbox = frost_ui.find_groupbox("groupbox1");
        if (groupbox)
            groupbox->set_text_color(olc::BLACK);
        auto groupbox_pos = frost_ui.find_groupbox("groupbox1")->get_position();

        // dropdown example
        frost_ui.add_dropdown("dropID1", "Select an item: ", { groupbox_pos.x + 100, groupbox_pos.y + 10 }, { 100, 20 });
        frost_ui.find_element("dropID1")->set_text_color(olc::BLACK);
        frost_ui.find_element("dropID1")->scale_text({ 1.0f, 1.0f });
        frost_ui.find_element("dropID1")->add_item("Cool item");
        frost_ui.find_element("dropID1")->add_item("Cool item2");

        // dropdown example
        frost_ui.add_combolist("comboID1", "Select items: ", { groupbox_pos.x + 100, groupbox_pos.y + 50 }, { 100, 20 });
        frost_ui.find_element("comboID1")->set_text_color(olc::BLACK);
        frost_ui.find_element("comboID1")->add_item("Cool item");
        frost_ui.find_element("comboID1")->add_item("Cool item2");

        frost_ui.add_slider("slider1", "Testing", { groupbox_pos.x + 100, groupbox_pos.y + 90 }, { 100, 10 }, { 0.0f, 50.0f }, &slider_value);
        frost_ui.find_element("slider1")->set_text_color(olc::BLACK);
        frost_ui.find_element("slider1")->set_slider_value(22.5f);

        frost_ui.set_active_window("new_window2");
        
        frost_ui.add_inputfield("input1", "Testing", { 10, 10 }, { 100, 10 });
        frost_ui.find_element("input1")->set_text_color(olc::BLACK);

        // Set the active window (window that will be used to add elements)
        frost_ui.set_active_window("main_window");

        // Tabs example
        int tab_size = main_window->get_window_space().x / 3;
        frost_ui.add_button("tab1", "Tab 1", { 0, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_1"); });
        frost_ui.add_button("tab2", "Tab 2", { tab_size, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_2"); });
        frost_ui.add_button("tab3", "Tab 3", { tab_size * 2, 0 }, { tab_size, 20 }, [&] { frost_ui.set_active_group("tab_3"); });

        // Set the active group to tab_1 (every element that is added to the UI instance will now be a part of this group)
        frost_ui.set_active_group("tab_1");

        frost_ui.add_label("label_1", "Test label", { 245, 40 });
        auto temp_var = frost_ui.find_element("label_1");
        if (!frost_ui.find_window("main_window"))
            temp_var->set_text_color(olc::WHITE);
        else
            temp_var->set_text_color(olc::BLACK);
        frost_ui.find_element("label_1")->set_centered(true);

        // Nesting buttons in the tab_1 group
        frost_ui.add_button("id1", "Test Button", { 5, 25 }, { 100, 20 }, [&]
            {
                i++;
                auto temp = frost_ui.find_element("id1");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(i) + " Times");
                if (!frost_ui.find_element("id2"))
                {
                    frost_ui.add_button("id2", "Reset", { 5, 50 }, { 100, 20 }, [&]
                        {
                            i = 0;
                            auto temp = frost_ui.find_element("id1");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button");
                            frost_ui.remove_element("id2");
                        });
                }
            });

        frost_ui.add_button("id99", "Toggle Button", { 5, 75 }, { 100, 20 }, nullptr);
        frost_ui.find_element("id99")->make_toggleable(&button_state);

        frost_ui.clear_active_group();

        frost_ui.add_checkbox("id5", "Checkbox", { 215, 55 }, { 10, 10 }, &checkbox_state);
        frost_ui.find_element("id5")->set_text_color(olc::BLACK);
        frost_ui.find_element("id5")->set_checkbox_orientation("left");

        // Change the active group to tab_2 (every element will be automatically added to this group)
        frost_ui.set_active_group("tab_2");
        // Nesting buttons in the tab_2 group
        frost_ui.add_button("id3", "Test Button 2", { 5, 25 }, { 100, 20 }, [&]
            {
                j++;
                auto temp = frost_ui.find_element("id3");
                temp->set_size({ 200, 20 });
                temp->set_text("Clicked " + std::to_string(j) + " Times");
                if (!frost_ui.find_element("id4"))
                    frost_ui.add_button("id4", "Reset 2", { 5, 50 }, { 100, 20 }, [&]
                        {
                            j = 0;
                            auto temp = frost_ui.find_element("id3");
                            temp->set_size({ 100, 20 });
                            temp->set_text("Test Button 2");
                            frost_ui.remove_element("id4");
                        });
            });

        // set the active group to tab_1 (this will act as the default group to be rendered)
        frost_ui.set_active_group("tab_1");

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        if (GetKey(olc::SHIFT).bPressed)
            frost_ui.find_window("main_window")->close_window(false);
        if (GetKey(olc::ENTER).bPressed)
            frost_ui.find_window("new_window")->close_window(false);

        if (checkbox_state != last_cb_state)
            std::cout << checkbox_state << "\n";
        if (button_state != last_btn_state)
            std::cout << button_state << "\n";
        if (current_element != old_element)
        {
            current_element = frost_ui.find_element("dropID1")->get_selected_item();
            std::cout << current_element << "\n";
        }
        if (current_elements.size() != old_elements.size())
        {
            current_elements = frost_ui.find_element("comboID1")->get_selected_items();
            std::string text;
            for (auto& element : current_elements)
                text += element + " ";
            std::cout << text << "\n";
        }
        if (slider_value != old_slider_value)
            std::cout << "Slider value: " << slider_value << "\n";

        last_btn_state = button_state;
        last_cb_state = checkbox_state;
        old_element = frost_ui.find_element("dropID1")->get_selected_item();
        old_elements = frost_ui.find_element("comboID1")->get_selected_items();
        old_slider_value = slider_value;

        frost_ui.run();

        return true;
    }
};


int main()
{
    Example demo;
    if (demo.Construct(1024, 720, 1, 1))
        demo.Start();

    return 0;
}