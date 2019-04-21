#pragma once

#include "../../utilities/vmt.h"
#include "../../interfaces/interfaces.h"
#include "../../sdk/c_input.h"
#include "../../sdk/i_client_entity.h"

namespace features {
	class visuals {
	public:
		struct esp_box {
			int x, y, w, h;
		};

		void render();
	private:
		const bool calculate_box_position(c_base_entity * entity, features::visuals::esp_box & box);
		void render_box(esp_box box);
		void render_health_bar(esp_box box, int entity_index);
		void render_name(esp_box box, int entity_index);
		void render_money(esp_box box, int entity_index);
		void render_weapon(esp_box box, int entity_index);
		void render_health(esp_box box, int entity_index);
		void render_armour(esp_box box, int entity_index);

		RECT util_get_screen_size(DWORD font, const char* text, ...)
		{
			size_t origsize = strlen(text) + 1;
			const size_t newsize = 100;
			size_t convertedChars = 0;
			wchar_t wcstring[newsize];
			mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

			RECT rect; int x, y;
			interfaces::surface->get_text_size(font, wcstring, x, y);
			rect.left = x; rect.bottom = y;
			rect.right = x;
			return rect;
		}
	};

	extern visuals* vis;
}