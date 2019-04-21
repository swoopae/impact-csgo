#include "../menu.h"

#include "../../sdk/c_input.h"

auto listen_for_input(int &key) -> bool {
	return false;
}

void c_menu::keybind(int &item, std::string name) {
	bool pressed = false;
	bool open = false;

	static bool selected_opened = false;
	static bool click_rest;
	static bool rest;
	static std::string name_selected;

	int x_position = groupbox_width - 20;
	int y_position = y_offset - 16;

	std::string something;

	if (menu.menu_opened) {
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_position - 40, y_position - 1, 48, 13)) {
			name_selected = name;
			pressed = true;
			click_rest = true;
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_position - 40, y_position - 1, 48, 13)) {
			click_rest = false;
		}
		if (pressed)
		{
			if (!rest)
				selected_opened = !selected_opened;
			rest = true;
		}
		else
			rest = false;

		if (name_selected == name)
			open = selected_opened;
	}

	if (open) {
		if (listen_for_input(item)) {
			something = interfaces::input_system->button_code_to_string((button_code_t)item);
		}
		else {
			something = "press a key";
		}
	}
	else something = interfaces::input_system->button_code_to_string((button_code_t)item);

	std::string thing_to_draw = "[ " + something + " ]";

	RECT text_size = menu.get_text_size(render_manager::fonts::menu_font, thing_to_draw.c_str());

	render_manager::text(thing_to_draw.c_str(), x_position - text_size.right, y_position, render_manager::fonts::menu_font, color(220, 220, 220, 230));
}