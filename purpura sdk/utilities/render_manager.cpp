#include "render_manager.h"

namespace render_manager {
	namespace fonts {
		DWORD others_font;
		DWORD esp_font;
		DWORD menu_font;
		DWORD minecraft_font;
		DWORD tab_font;
		DWORD cool_thing_font;
	}
}

void render_manager::init() {
	global_utils::console_log("initialising draw manager...");

	fonts::others_font = interfaces::surface->create_font();
	fonts::esp_font = interfaces::surface->create_font();
	fonts::menu_font = interfaces::surface->create_font();
	fonts::minecraft_font = interfaces::surface->create_font();
	fonts::tab_font = interfaces::surface->create_font();
	fonts::cool_thing_font = interfaces::surface->create_font();

	interfaces::surface->set_font_glyph_set(fonts::others_font, "Small Fonts", 8, 400, 0, 0, FONTFLAG_OUTLINE);
	interfaces::surface->set_font_glyph_set(fonts::esp_font, "Verdana", 13, 50, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->set_font_glyph_set(fonts::menu_font, "Verdana", 12, 0, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->set_font_glyph_set(fonts::tab_font, "cherryfont", 23, 0, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::surface->set_font_glyph_set(fonts::cool_thing_font, "Verdana", 25, 0, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::surface->set_font_glyph_set(fonts::minecraft_font, "Minecraft", 19, 0, 0, 0, FONTFLAG_DROPSHADOW);

	global_utils::console_log("draw manager initialised...");
}

void render_manager::rect(int x, int y, int w, int h, color color) {
	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outline(x, y, x + w, y + h);
}

void render_manager::filled_rect(int x, int y, int w, int h, color color) {
	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_filled_rect(x, y, x + w, y + h);
}

void render_manager::vertical_gradient_rect(int x, int y, int w, int h, color top, color bottom) {
	interfaces::surface->draw_set_color(top.r, top.g, top.b, top.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 255, 255, false);
	interfaces::surface->draw_set_color(bottom.r, bottom.g, bottom.b, bottom.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 0, 255, false);
}

void render_manager::horizontal_gradient_rect(int x, int y, int w, int h, color left, color right) {
	interfaces::surface->draw_set_color(left.r, left.g, left.b, left.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 255, 255, true);
	interfaces::surface->draw_set_color(right.r, right.g, right.b, right.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 0, 255, true);
}

void render_manager::text(const char* text, int x, int y, int font, color color) {
	std::string text_normal = text;
	std::wstring text_wide = std::wstring(text_normal.begin(), text_normal.end());

	interfaces::surface->draw_set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_set_text_font(font);
	interfaces::surface->draw_set_text_pos(x, y);
	interfaces::surface->draw_print_text(text_wide.c_str(), text_wide.length(), FONT_DRAW_DEFAULT);
}
