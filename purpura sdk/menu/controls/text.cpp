#include "../menu.h"

void c_menu::text(std::string text_to_write) {
	if (groupbox_bottom <= y_offset + 14)
		return;

	if (groupbox_top >= y_offset + 14)
		return;

	render_manager::text(text_to_write.c_str(), x_offset + 8, y_offset, render_manager::fonts::menu_font, color(220, 220, 220, 230));

	y_offset += 14;
}