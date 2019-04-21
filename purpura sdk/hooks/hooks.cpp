#include "hooks.h"

#include "../utilities/globals.h"
#include "../utilities/render_manager.h"
#include "../utilities/math.h"

#include "../menu/menu.h"
#include "../menu/settings.h"

#include "../features/visuals/visuals.h"
#include "../features/misc/misc.h"
#include "../features/engine_prediction/engine_prediction.h"
#include "../features/legit/legit_lag_comp.h"
#include "../features/misc/sfx/hitsounds.h"

std::unique_ptr <vmt>   client_mode_hook;
std::unique_ptr <vmt>   panel_hook;
std::unique_ptr <vmt>   surface_hook;
std::unique_ptr <vmt>   render_view_hook;

void hooks::init() {
	global_utils::console_log("initialising hooks...");

	client_mode_hook = std::make_unique<vmt>(interfaces::client_mode);
	panel_hook = std::make_unique<vmt>(interfaces::panel);
	surface_hook = std::make_unique<vmt>(interfaces::surface);
	render_view_hook = std::make_unique<vmt>(interfaces::render_view);

	global_utils::console_log("hooks initialised, have fun!");

	client_mode_hook->hook(hooks::indexes::create_move, hooks::create_move_hook);
	client_mode_hook->hook(hooks::indexes::viewmodel_fov, hooks::viewmodel_fov_hook);
	panel_hook->hook(hooks::indexes::paint_traverse, hooks::paint_traverse_hook);
	surface_hook->hook(hooks::indexes::lock_cursor, hooks::lock_cursor_hook);
	render_view_hook->hook(hooks::indexes::scene_end, hooks::scene_end_hook);

	interfaces::engine_client->unrestricted_client_cmd("clear");
	interfaces::engine_client->unrestricted_client_cmd("echo [impact csgo]: hi uc! -swoopae");
}

void hooks::restore() {
	client_mode_hook->unhook(hooks::indexes::create_move);
	client_mode_hook->unhook(hooks::indexes::viewmodel_fov);
	panel_hook->unhook(hooks::indexes::paint_traverse);
	surface_hook->unhook(hooks::indexes::lock_cursor);
	render_view_hook->unhook(hooks::indexes::scene_end);
}

bool __fastcall hooks::create_move_hook(i_client_mode* thisptr, void* edx, float sample_frametime, c_usercmd* cmd) {
	static auto o_create_move = client_mode_hook->get_original < create_move_t >(hooks::indexes::create_move);

	o_create_move(thisptr, edx, sample_frametime, cmd);

	auto o_func = o_create_move(thisptr, edx, sample_frametime, cmd);

	if (!interfaces::engine_client->in_game_connected() || !cmd || !cmd->command_number)
		return o_func;

	global_variables::global_cmd = cmd;
	global_variables::local_player = interfaces::client_ent_list->get_client_entity(interfaces::engine_client->get_local_player());
	global_variables::b_send_packet = true;

	if (!global_variables::local_player)
		return o_func;

	uintptr_t *frame_pointer;
	__asm mov frame_pointer, ebp;

	global_variables::original_angles = cmd->viewangles;

	if (c_config::misc::infinity_duck)
		cmd->buttons |= cmd_buttons::in_bullrush;

	features::misc->on_create_move(global_variables::global_cmd);

	features::engine_pred->start_prediction(global_variables::local_player, global_variables::global_cmd);

	if (c_config::legit::legit_backtrack)
		features::lag_comp->on_create_move();

	features::engine_pred->end_prediction(global_variables::local_player);

	global_math::normalize_angles(global_variables::global_cmd->viewangles);

	*(bool*)(*frame_pointer - 0x1C) = global_variables::b_send_packet;

	return false;
}

float __stdcall hooks::viewmodel_fov_hook() {
	if (c_config::visuals::viewmodel_fov == 0)
		return 68.f;

	return c_config::visuals::viewmodel_fov;
}

void __fastcall hooks::paint_traverse_hook(PVOID p_panel, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) {
	static auto o_paint_traverse = panel_hook->get_original < paint_traverse_t >(hooks::indexes::paint_traverse);

	static unsigned int panel_id;

	o_paint_traverse(p_panel, vgui_panel, force_repaint, allow_force);

	if (!panel_id)
		if (!strcmp("MatSystemTopPanel", interfaces::panel->get_name(vgui_panel)))
			panel_id = vgui_panel;

	if (panel_id == vgui_panel)
	{
		// walter mark
		render_manager::text("[impact csgo]", 15, 15, render_manager::fonts::menu_font, color(127, 193, 255, 235));

		// render features
		features::vis->render();

		// render menu
		menu.draw();
	}
}

void __fastcall hooks::lock_cursor_hook(i_surface* thisptr, void* edx) {
	static auto o_lock_cursor = surface_hook->get_original < lock_cursor_t >(hooks::indexes::lock_cursor);

	if (!menu.menu_opened)
		return o_lock_cursor(thisptr, edx);

	interfaces::surface->unlock_cursor();
}

void __fastcall hooks::scene_end_hook(void *ecx, void *edx) {
	static auto o_scene_chad = render_view_hook->get_original < scene_end_t >(hooks::indexes::scene_end);

	o_scene_chad(ecx, edx);

	// chams region
	if (!c_config::visuals::chams)
		return;

	for (int i = 1; i < 65; ++i) {
		auto ent = interfaces::client_ent_list->get_client_entity(i);

		if (ent && ent->health() && ent->team() != global_variables::local_player->team() && !ent->dormant()) {
			static i_material *mat = NULL;

			if (!mat)
				mat = interfaces::mat_system->find_material("chams", TEXTURE_GROUP_MODEL);

			if (mat) {
				interfaces::model_render->override_material(mat);
				mat->set_flag(MATERIAL_VAR_IGNOREZ, c_config::visuals::chams_ignore_z);
				mat->alpha_modulate(c_config::visuals::chams_transparency, 100.f);
				mat->color_modulate(c_config::visuals::chams_colour.r,
					c_config::visuals::chams_colour.g,
					c_config::visuals::chams_colour.b);
				ent->draw_model(0x1, 255);
				interfaces::model_render->override_material(nullptr);
				mat->alpha_modulate(1.f);
			}
		}
	}
}