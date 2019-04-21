#include "settings.h"

namespace c_config {
	namespace legit {
		bool legit_backtrack = false;
	}

	namespace visuals {
		// players
		bool esp_boxes = false;
		color esp_box_colour = color(127.f, 193.f, 255.f, 255.f);
		bool esp_names = false;
		color esp_name_colour = color(255.f, 255.f, 255.f, 255.f);
		bool esp_money = false;
		color esp_money_colour = color(255.f, 255.f, 255.f, 255.f);
		bool esp_weapon = false;
		color esp_weapon_colour = color(255.f, 255.f, 255.f, 255.f);
		bool esp_health = false;
		bool esp_health_bar = false;
		color esp_health_colour = color(255.f, 255.f, 255.f, 255.f);
		bool esp_armour = false;
		color esp_armour_colour = color(255.f, 255.f, 255.f, 255.f);
		bool chams = false;
		int chams_transparency = 0;
		color chams_colour = color(255.f, 255.f, 255.f, 255.f);
		bool chams_ignore_z = false;

		// effects
		int viewmodel_fov = 0;
	}
	namespace misc {
		bool bunnyhop = false;
		bool clantag_changer = false;
		bool infinity_duck = false;
	}
}