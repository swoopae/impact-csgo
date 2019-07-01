#include "visuals.h"

#include "../../sdk/iv_engine_client.h"
#include "../../sdk/entities.h"

#include "../../utilities/render_manager.h"
#include "../../utilities/math.h"

#include "../../menu/settings.h"

#include <algorithm>

// hee hee
// some code might make no sense here - i didnt initially write the visuals myself so no bully

int y_position_displace = 1;

const bool features::visuals::calculate_box_position(c_base_entity* entity, features::visuals::esp_box &box) {
	vec3_t top, down, s[2], air;

	vec3_t adjust = vec3_t(0, 0, -15 * entity->crouch_ammount());

	down = entity->abs_origin();

	if (!(entity->flags() & fl_onground) && (entity->move_type() != move_types::ladder))
		air = vec3_t(0, 0, 10);
	else
		air = vec3_t(0, 0, 0);

	down = entity->abs_origin() + air;

	if ((entity->flags() & fl_ducking))
	{
		top = down + vec3_t(0, 0, 58) + adjust;
	}
	else {
		top = down + vec3_t(0, 0, 72) + adjust;
	}

	if (global_utils::world_to_screen(top, s[1]) && global_utils::world_to_screen(down, s[0]))
	{
		vec3_t delta = s[1] - s[0];

		box.h = static_cast<int>(fabsf(delta.y) + 6);
		box.w = static_cast<int>(box.h / 2 + 5);

		box.x = static_cast<int>(s[1].x - (box.w / 2) + 2);
		box.y = static_cast<int>(s[1].y - 1);

		return true;
	}

	return false;
}
void features::visuals::render_box(esp_box box) {
	render_manager::rect(box.x, box.y, box.w, box.h, c_config::visuals::esp_box_colour);
	render_manager::rect(box.x + 1, box.y + 1, box.w - 2, box.h - 2, color(25, 25, 25, 120));
	render_manager::rect(box.x - 1, box.y - 1, box.w + 2, box.h + 2, color(25, 25, 25, 120));
}

void features::visuals::render_health_bar(esp_box box, int entity_index) {
	c_base_entity* entity = interfaces::client_ent_list->get_client_entity(entity_index);

	int pixel_value = entity->health() * box.h / 100;

	render_manager::filled_rect(box.x - 6, box.y - 1, 4, box.h + 2, color(0, 0, 0, 240));
	render_manager::filled_rect(box.x - 5, box.y + box.h - pixel_value, 2, pixel_value, c_config::visuals::esp_box_colour);
}

void features::visuals::render_health(esp_box box, int entity_index) {
	c_base_entity* entity = interfaces::client_ent_list->get_client_entity(entity_index);

	std::string final_text = std::to_string(entity->health()) + " hp";

	render_manager::text(final_text.c_str(), box.x + box.w + 2, box.y + y_position_displace, render_manager::fonts::esp_font, c_config::visuals::esp_health_colour);

	y_position_displace += 12;
}

void features::visuals::render_armour(esp_box box, int entity_index) {
	c_base_entity* entity = interfaces::client_ent_list->get_client_entity(entity_index);

	std::string final_text = std::to_string(entity->armour()) + " ap";

	render_manager::text(final_text.c_str(), box.x + box.w + 2, box.y + y_position_displace, render_manager::fonts::esp_font, c_config::visuals::esp_armour_colour);

	y_position_displace += 12;
}

void features::visuals::render_money(esp_box box, int entity_index) {
	c_base_entity* entity = interfaces::client_ent_list->get_client_entity(entity_index);

	std::string final_text = "$ " + std::to_string(entity->money());

	render_manager::text(final_text.c_str(), box.x + box.w + 2, box.y + y_position_displace, render_manager::fonts::esp_font, c_config::visuals::esp_money_colour);

	y_position_displace += 12;
}

void features::visuals::render_weapon(esp_box box, int entity_index) {
	c_base_entity* entity = interfaces::client_ent_list->get_client_entity(entity_index);

	auto current_weapon = entity->active_weapon();
	std::string weapon_name = current_weapon->sanitized_weapon_name();

	std::transform(weapon_name.begin(), weapon_name.end(), weapon_name.begin(), ::tolower);

	RECT thing = get_text_size(render_manager::fonts::esp_font, weapon_name.c_str());

	int difference = thing.left / 2;

	render_manager::text(weapon_name.c_str(), (box.x + box.w / 2) - difference, box.y + box.h + 2, render_manager::fonts::esp_font, c_config::visuals::esp_weapon_colour);
}

void features::visuals::render_name(esp_box box, int entity_index) {
	static auto clean_name = [](char * name) -> std::string {
		name[127] = '\0';

		std::string tmp(name);

		if (tmp.length() > 20) {
			tmp.erase(20, (tmp.length() - 20));
			tmp.append("...");
		}

		return tmp;
	};

	player_info_t info;

	interfaces::engine_client->get_player_info(entity_index, &info);

	std::string name = clean_name(info.name);
	std::string bot, final_string;

	if (info.fakeplayer)
		bot = "[bot] ";

	final_string = bot + name;

	RECT thing = get_text_size(render_manager::fonts::esp_font, final_string.c_str());

	int difference = thing.left / 2;

	render_manager::text(final_string.c_str(), (box.x + box.w / 2) - difference, box.y - 15, render_manager::fonts::esp_font, c_config::visuals::esp_name_colour);
}

features::visuals::esp_box box_info;

void features::visuals::render() {
	if (!interfaces::engine_client->in_game_connected())
		return;

	auto local = interfaces::client_ent_list->get_client_entity(interfaces::engine_client->get_local_player());

	for (int i = 0; i < 65; ++i) {
		c_base_entity* entity = interfaces::client_ent_list->get_client_entity(i);

		if (!entity || entity->team() == local->team() || entity->dormant() || !entity->is_alive())
			continue;

		if (!this->calculate_box_position(entity, box_info))
			continue;

		y_position_displace = 1;

		if (c_config::visuals::esp_boxes)
			this->render_box(box_info);

		if (c_config::visuals::esp_names)
			this->render_name(box_info, i);

		if (c_config::visuals::esp_weapon)
			this->render_weapon(box_info, i);

		if (c_config::visuals::esp_health)
			this->render_health(box_info, i);

		if (c_config::visuals::esp_health_bar)
			this->render_health_bar(box_info, i);

		if (c_config::visuals::esp_armour)
			this->render_armour(box_info, i);

		if (c_config::visuals::esp_money)
			this->render_money(box_info, i);
	}
}
