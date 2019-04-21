#pragma once

#include "../interfaces/interfaces.h"

namespace render_manager {
	namespace fonts {
		extern DWORD others_font;
		extern DWORD esp_font;
		extern DWORD menu_font;
		extern DWORD minecraft_font;
		extern DWORD tab_font;
		extern DWORD cool_thing_font;
	}

	void init();
	void rect(int x, int y, int w, int h, color color);
	void filled_rect(int x, int y, int w, int h, color color);
	void vertical_gradient_rect(int x, int y, int w, int h, color top, color bottom);
	void horizontal_gradient_rect(int x, int y, int w, int h, color left, color right);
	void text(const char *text, int x, int y, int font, color color);
}

/*

#include "vector.h" // i don't know why i include "vector.h" but i'm not going to remove it this commit, i really don't want it to break some shit

*/