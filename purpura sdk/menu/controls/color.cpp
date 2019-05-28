#include "../menu.h"

void spectrum(int x, int y, int w, int h) {
	render_manager::filled_rect(x, y, w, h - 3, color(15, 15, 15, 225));
	render_manager::filled_rect(x + 1, y + 1, w - 2, h - 2 - 3, color(20, 20, 20, 230));

	for (int i = 1; i < 60; i++) {
		if (i <= 10)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(255, 25.5f * (i), 0), color(255, 255, 255));
		if (i > 10 && i <= 20)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(255 - (25.5f * (i)), 255, 0), color(255, 255, 255));
		if (i > 20 && i <= 30)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(0, 255, 25.5f * (i)), color(255, 255, 255));
		if (i > 30 && i <= 40)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(0, 255 - (25.5f * (i)), 255), color(255, 255, 255));
		if (i > 40 && i <= 50)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(25.5f * (i), 0, 255), color(255, 255, 255));
		if (i > 50 && i <= 60)
			render_manager::horizontal_gradient_rect(x + 2, y + i + 2, w - 4, 1, color(255, 0, 255 - (25.5f * (i))), color(255, 255, 255));
	}
}

void c_menu::color_selector(std::string name, color * colour) {
	bool pressed = false;
	bool open = false;

	static bool selected_opened = false;
	static bool click_rest;
	static bool rest;
	static std::string name_selected;

	int x_position = groupbox_width - 29;
	int y_position = y_offset - 16;

	render_manager::filled_rect(x_position - 1, y_position - 1, 25, 13, color(35, 35, 35, 255));
	render_manager::filled_rect(x_position, y_position, 23, 11, color(colour->r, colour->g, colour->b, colour->a));

	if (menu.menu_opened) {
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_position - 1, y_position - 1, 25, 13) && !click_rest) {
			name_selected = name;
			pressed = true;
			click_rest = true;
		}
		else if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_position - 1, y_position - 1, 25, 13)) {
			click_rest = false;
		}
		if (pressed)
		{
			if (!rest) {
				menu.is_color_tick_selected = !menu.is_color_tick_selected;
				selected_opened = !selected_opened;
			}
			rest = true;
		}
		else
			rest = false;

		if (name_selected == name)
			open = selected_opened;
	}

	if (open) {
		spectrum(x_position + 25, y_position - 4, 68, 68); // draw spectrum

		// handle input
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_position + 27, y_position - 4 + 3, 60, 60)) {
			
			HDC hdc = GetDC(nullptr); 

			COLORREF selected_colour;
			selected_colour = GetPixel(hdc, mouse_pos().x, mouse_pos().y);

			colour->r = GetRValue(selected_colour);
			colour->g = GetGValue(selected_colour);
			colour->b = GetBValue(selected_colour);
			colour->a = 255.f;
		}
	}
}
