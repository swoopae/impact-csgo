#include "../menu.h"

void c_menu::combobox(int size, std::string name, std::string* itemname, int* item)
{
	if (groupbox_bottom <= y_offset + 41)
		return;

	bool pressed = false;
	bool open = false;
	static bool selected_opened = false;
	static bool click_rest;
	static bool rest;
	static std::string name_selected;

	int combo_size = 160;

	x_offset -= 22;

	if (!menu.is_color_tick_selected) {
		if (menu.menu_opened) {
			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 25, y_offset + 14, combo_size, 17) && !click_rest)
			{
				name_selected = name;
				pressed = true;
				click_rest = true;
			}
			else if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 25, y_offset + 14, combo_size, 17))
				click_rest = false;

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
	}

	render_manager::text(name.c_str(), x_offset + 29, y_offset - 2, render_manager::fonts::menu_font, color(220, 220, 220, 230));
	render_manager::filled_rect(x_offset + 29, y_offset + 14, combo_size, 17, color(60, 60, 60, 5));
	render_manager::rect(x_offset + 29, y_offset + 14, combo_size, 17, color(185, 185, 185, 230));

	if (open)
	{
		render_manager::filled_rect(x_offset + 29, y_offset + 14 + 21, combo_size, (size * 16), color(60, 60, 60, 5));
		render_manager::rect(x_offset + 29, y_offset + 14 + 21, combo_size, (size * 16), color(185, 185, 185, 230));

		for (int i = 0; i < size; i++)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 29, y_offset + 34 + i * 16, combo_size, 16))
				*item = i;

			if (i == *item)
				render_manager::text(itemname[i].c_str(), x_offset + 29 + 10, y_offset + 35 + i * 16, render_manager::fonts::menu_font, color(127, 193, 255, 255));
			else
				render_manager::text(itemname[i].c_str(), x_offset + 29 + 10, y_offset + 35 + i * 16, render_manager::fonts::menu_font, color(220, 220, 220, 230));
		}
	}

	render_manager::text(itemname[*item].c_str(), x_offset + 38, y_offset + 15, render_manager::fonts::menu_font, color(220, 220, 220, 230));

	if (open) // i added 1 more to 42 bec the space between the main box and the drop down
		y_offset += 39 + (size * 16);
	else
		y_offset += 38;

	x_offset += 22;
}