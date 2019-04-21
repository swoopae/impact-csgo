#include "../menu.h"

void c_menu::checkbox(std::string name, bool* item, std::string tooltip) {
	if (groupbox_bottom <= y_offset + 16)
		return;

	if (groupbox_top >= y_offset + 16)
		return;

	int size = 12;

	static bool pressed = false;

	if (checkbox_fade_alpha > 30 || checkbox_fade_alpha < 15)
		checkbox_fade_alpha = 5;

	auto text_size = get_text_size(render_manager::fonts::menu_font, name.c_str());

	if (mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size) && checkbox_fade_alpha < 30) {
		checkbox_fade_alpha++;
	}
	if (!mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size) && checkbox_fade_alpha > 15) {
		checkbox_fade_alpha--;
	}

	// handle input
	if (!menu.is_color_tick_selected) {
		if (menu.menu_opened) {
			if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size))
			{
				if (pressed)
					*item = !*item;
				pressed = false;
			}

			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size) && !pressed)
				pressed = true;
		}
	}

	if (*item == true)
		render_manager::filled_rect(x_offset + 8, y_offset, size, size, color(127, 193, 255, 235));
	else
		render_manager::filled_rect(x_offset + 8, y_offset, size, size, color(75, 75, 75, checkbox_fade_alpha));

	render_manager::rect(x_offset + 8, y_offset, size, size, color(185, 185, 185, 230));
	render_manager::text(name.c_str(), x_offset + 29 - 5, y_offset, render_manager::fonts::menu_font, color(220, 220, 220, 230));

	y_offset += 16;
}