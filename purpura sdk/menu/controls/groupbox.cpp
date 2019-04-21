#include "../menu.h"

void c_menu::groupbox(int x, int y, int w, int h, std::string name, bool fade_thing) {
	static bool switcharoo = false;

	if (fade_thing) {
		if (groupbox_outline_alpha > 15 || groupbox_outline_alpha < 5)
			groupbox_outline_alpha = 5;

		if (mouse_in_params(_pos.x + x, _pos.y + y, w, h) && groupbox_outline_alpha < 15) {
			if (switcharoo)
				groupbox_outline_alpha++;
			switcharoo = !switcharoo;
		}
		if (!mouse_in_params(_pos.x + x, _pos.y + y, w, h) && groupbox_outline_alpha > 5) {
			if (switcharoo)
				groupbox_outline_alpha--;
			switcharoo = !switcharoo;
		}
	}
	else {
		groupbox_outline_alpha = 5;
	}

	render_manager::filled_rect(_pos.x + x, _pos.y + y, w, h, color(60, 60, 60, groupbox_outline_alpha));

	RECT text_size = get_text_size(render_manager::fonts::menu_font, name.c_str());

	render_manager::text(name.c_str(), (((_pos.x + x) + (w / 2)) - (text_size.right / 2)), (_pos.y + y /* -6 */), render_manager::fonts::menu_font, color(230, 230, 230, 230));

	y_offset = (_pos.y + (y + 12));
	x_offset = _pos.x + x;
	groupbox_bottom = (_pos.y + (y + h));
	groupbox_top = (_pos.y + y);
	groupbox_width = (_pos.x + (x + w));
}