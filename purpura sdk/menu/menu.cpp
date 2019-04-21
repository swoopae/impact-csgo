#include "menu.h"
#include "settings.h"

#include "configs/configs.h"

/*
* Credits for the menu:
* - stickrpg for the original framework
* - psilent/tomoisbiggay for leaking ""his"" own source
* - swoopae (me l0l) for design, additional controls
*/

std::string configs[] = { "legit", "other", "rage" };

c_menu menu;

vec2_t c_menu::mouse_pos() {
	POINT mouse_position;
	GetCursorPos(&mouse_position);
	ScreenToClient(FindWindowA(0, "Counter-Strike: Global Offensive"), &mouse_position);
	return { static_cast <float> (mouse_position.x), static_cast <float> (mouse_position.y) };
}

bool c_menu::mouse_in_params(int x, int y, int x2, int y2) {
	if (mouse_pos().x > x && mouse_pos().y > y && mouse_pos().x < x2 + x && mouse_pos().y < y2 + y)
		return true;
	return false;
}

enum tabs {
	aim = 0,
	visuals = 1,
	null = 2,
	home = 3,
	misc = 4
};

bool config_save = false, config_load = false;
int config_selected = 0;

void c_menu::draw() {
	static bool _pressed = true;

	if (!_pressed && GetAsyncKeyState(VK_INSERT))

		_pressed = true;

	else if (_pressed && !GetAsyncKeyState(VK_INSERT)) {
		_pressed = false;
		menu_opened = !menu_opened;

		interfaces::input_system->enable_input(!menu_opened);
	}

	interfaces::engine_client->get_screen_size(screen_width, screen_width);

	static vec2_t _mouse_pos;

	static int _drag_x = 300;
	static int _drag_y = 300;
	static int _width = 550;
	static int _height = 350;

	static int filled_rect_tab_alpha = 2;

	static bool _dragging = false;
	bool _click = false;

	if (menu_opened) {
		if (GetAsyncKeyState(VK_LBUTTON))
			_click = true;

		vec2_t _mouse_pos = mouse_pos();

		if (_dragging && !_click)
			_dragging = false;

		if (_dragging && _click) {
			_pos.x = _mouse_pos.x - _drag_x;
			_pos.y = _mouse_pos.y - _drag_y;
		}

		if (mouse_in_params(_pos.x, _pos.y, _width, _height) && !(mouse_in_params(_pos.x + 20, _pos.y + 20, _width - 10, _height - 10))) {
			_dragging = true;
			_drag_x = _mouse_pos.x - _pos.x;
			_drag_y = _mouse_pos.y - _pos.y;
		}

		if (config_save) {
			switch (config_selected) {
			case 0: config_system->save("legit"); break;
			case 1: config_system->save("other"); break;
			case 2: config_system->save("rage"); break;
			}
			config_save = !config_save;
		}

		if (config_load) {
			switch (config_selected) {
			case 0: config_system->load("legit"); break;
			case 1: config_system->load("other"); break;
			case 2: config_system->load("rage"); break;
			}
			config_load = !config_load;
		}

		render_manager::filled_rect(_pos.x - 7, _pos.y - 7, _width + 14, _height + 14, color(0, 0, 0));
		render_manager::filled_rect(_pos.x - 6, _pos.y - 6, _width + 12, _height + 12, color(127, 193, 255, 180));
		render_manager::filled_rect(_pos.x - 4, _pos.y - 4, _width + 8, _height + 8, color(15, 15, 15));

		if (mouse_in_params(_pos.x - 4, _pos.y - 4, 44, _height + 8)) {
			if (filled_rect_tab_alpha < 40) filled_rect_tab_alpha++;
		}
		else {
			if (filled_rect_tab_alpha > 2) filled_rect_tab_alpha--;
		}

		// tab thing, changes color based on hover lmao
		render_manager::filled_rect(_pos.x - 4, _pos.y - 4, 44, _height + 8, color(46, 46, 46, filled_rect_tab_alpha));

		render_manager::vertical_gradient_rect(_pos.x + 40, _pos.y + 10, 2, (_height / 2) + 4 - 10, color(15, 15, 15), color(50, 50, 50));
		render_manager::vertical_gradient_rect(_pos.x + 40, _pos.y + (_height / 2), 2, (_height / 2) - 10, color(50, 50, 50), color(15, 15, 15));

		RECT netflix_text_size = get_text_size(render_manager::fonts::cool_thing_font, "IMPACT");

		render_manager::text("IMPACT", _pos.x + _width - 5 - netflix_text_size.right, _pos.y + _height - 36, render_manager::fonts::cool_thing_font, color(127, 193, 255, 235));

		std::string final_tooltip;
		final_tooltip = menu.tooltip;

		int in_sizew = _width;

		static int tab_selected = 0;
		static const int tab_amount = 5, factor = 50;
		static std::string tab_names[tab_amount] = { "A", "D", "-", "E", "G" };
		static std::string tab_tooltips[tab_amount] = { "aimbot tab", "visuals tab", "null", "home tab", "misc tab" };

		for (int i = 0; i < tab_amount; i++)
		{
			RECT text_size = get_text_size(render_manager::fonts::tab_font, tab_names[i].c_str());

			if (i == 2)
				continue;
			else {
				if (tab_selected == i) {
					render_manager::text(tab_names[i].c_str(), _pos.x + 7, _pos.y + 50 + (factor * i), render_manager::fonts::tab_font, color(127, 193, 255, 235));
				}
				else {
					render_manager::text(tab_names[i].c_str(), _pos.x + 7, _pos.y + 50 + (factor * i), render_manager::fonts::tab_font, color(255, 255, 255, 255));
				}
			}

			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(_pos.x + 5, _pos.y + 50 + (factor * i), text_size.right, text_size.bottom)) {
				tab_selected = i;
			}
		}

		bool test_bool;
		int test_int = 0;

		switch (tab_selected) {
		case aim:
			groupbox(50, 10, 485, 300, "aimbot", false);
			//checkbox("test", &test_bool, " ");
			//keybind(test_int, "test keybind");
			checkbox("legit backtrack", &c_config::legit::legit_backtrack, " ");

			menu.tooltip = tab_tooltips[aim];
			break;
		case visuals:

			// SECOND GROUPBOX BEFORE FIRST ONE SO RENDERING DOESNT FUCK UP (big brain gaming only)
			groupbox((485 / 2) + 60, 10, (485 / 2) - 10, 300, "visual effects", false);
			text("\n"); // for spacing
			slider(140, "viewmodel fov", &c_config::visuals::viewmodel_fov, "%", 1);

			groupbox(55, 10, (485 / 2) - 10, 330, "player visuals", false);
			checkbox("render boxes", &c_config::visuals::esp_boxes, " ");
			color_selector("box colour", &c_config::visuals::esp_box_colour);
			checkbox("render names", &c_config::visuals::esp_names, " ");
			color_selector("name colour", &c_config::visuals::esp_name_colour);
			checkbox("render health", &c_config::visuals::esp_health, " ");
			color_selector("health colour", &c_config::visuals::esp_health_colour);
			checkbox("render health bar", &c_config::visuals::esp_health_bar, " ");
			checkbox("render armour", &c_config::visuals::esp_armour, " ");
			color_selector("armour colour", &c_config::visuals::esp_armour_colour);
			checkbox("render money", &c_config::visuals::esp_money, " ");
			color_selector("money colour", &c_config::visuals::esp_money_colour);
			checkbox("render weapon", &c_config::visuals::esp_weapon, " ");
			color_selector("weapon colour", &c_config::visuals::esp_weapon_colour);
			checkbox("render chams", &c_config::visuals::chams, " ");
			color_selector("chams colour", &c_config::visuals::chams_colour);

			if (c_config::visuals::chams) {
				slider(100, "chams transparency", &c_config::visuals::chams_transparency, "%", 1);
				checkbox("ignore z axis", &c_config::visuals::chams_ignore_z, " ");
			}

			menu.tooltip = tab_tooltips[visuals];
			break;
		case home:
			groupbox(50, 10, 485, 300, "home", true);
			text("hello, uc!");
			text("thank you for taking your time to inject this meme.");
			text("\n"); // for spacing
			combobox(3, "config list", configs, &config_selected);
			checkbox("save config", &config_save, " ");
			checkbox("load config", &config_load, " ");
			menu.tooltip = tab_tooltips[home];
			break;
		case misc:
			groupbox(50, 10, 485, 300, "miscellaneous", false);
			checkbox("bunnyhop", &c_config::misc::bunnyhop, " ");
			checkbox("clantag spammer", &c_config::misc::clantag_changer, " ");
			checkbox("infinity duck", &c_config::misc::infinity_duck, " ");

			menu.tooltip = tab_tooltips[misc];
			break;
		}

		// tooltip thing
		render_manager::text(final_tooltip.c_str(), _pos.x + _width - 5 - netflix_text_size.right, _pos.y + _height - 13, render_manager::fonts::esp_font, color(125, 125, 125));
	}
}