#include "../menu.h"

void c_menu::slider(int max, std::string name, int* item, std::string suffix, int step)
{
	if (groupbox_bottom <= y_offset + 30)
		return;

	float slider_size = 100; // 163

	float _pixel_value = max / slider_size;

	if (!menu.is_color_tick_selected) {
		if (menu.menu_opened) {
			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 29, y_offset + 14, slider_size + 1, 10))
				*item = abs(mouse_pos().x - (x_offset + 29)) * _pixel_value;

			static bool pressed_subtract = false;
			static bool pressed_add = false;

			/*
			subtract
			*/

			if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 21, y_offset + 12, 8, 10))
			{
				if (pressed_subtract)
					*item -= step;
				pressed_subtract = false;
			}

			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 21, y_offset + 12, 8, 10) && !pressed_subtract)
				pressed_subtract = true;

			/*
			add
			*/

			if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 22 + slider_size, y_offset + 12, 15, 10))
			{
				if (pressed_add)
					*item += step;
				pressed_add = false;
			}

			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 22 + slider_size, y_offset + 12, 15, 10) && !pressed_add)
				pressed_add = true;

			if (*item > max) {
				*item = max;
			}

			if (*item < 0) {
				*item = 0;
			}
		}
	}

	std::string namedisplay;

	namedisplay += name.c_str();

	namedisplay += " (";

	namedisplay += std::to_string(*item);

	namedisplay += ")";

	render_manager::text(namedisplay.c_str(), x_offset + 29, y_offset - 3, render_manager::fonts::menu_font, color(185, 185, 185, 230));

	render_manager::filled_rect(x_offset + 29, y_offset + 14, slider_size, 10, color(75, 75, 75, 10));

	if (*item)
	{
		if (*item == max)
			render_manager::filled_rect(x_offset + 29, y_offset + 14, slider_size, 10, color(127, 193, 255, 235));
		else
			render_manager::filled_rect(x_offset + 29, y_offset + 14, (*item / _pixel_value), 10, color(127, 193, 255, 235));
	}

	render_manager::rect(x_offset + 29, y_offset + 14, slider_size, 10, color(185, 185, 185, 230));

	render_manager::text("<", x_offset + 22 - 3, y_offset + 12, render_manager::fonts::menu_font, color(185, 185, 185, 230));
	render_manager::text(">", x_offset + 20 + slider_size + 12, y_offset + 13, render_manager::fonts::menu_font, color(185, 185, 185, 230));

	y_offset += 30;
}