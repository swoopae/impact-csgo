#pragma once

#include "../sdk/i_surface.h"

namespace c_config {
	namespace legit {
		extern bool legit_backtrack;
	}

	namespace visuals {
		extern bool esp_boxes;
		extern color esp_box_colour;
		extern bool esp_names;
		extern color esp_name_colour;
		extern bool esp_health;
		extern bool esp_health_bar;
		extern color esp_health_colour;
		extern bool esp_armour;
		extern color esp_armour_colour;
		extern bool esp_weapon;
		extern color esp_weapon_colour;
		extern bool esp_money;
		extern color esp_money_colour;
		extern bool chams;
		extern int chams_transparency;
		extern color chams_colour;
		extern bool chams_ignore_z;

		extern int viewmodel_fov;
	}
	namespace misc {
		extern bool bunnyhop;
		extern bool clantag_changer;
		extern bool infinity_duck;
	}
}