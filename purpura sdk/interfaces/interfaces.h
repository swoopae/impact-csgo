#pragma once

#include "../sdk/i_surface.h"
#include "../sdk/i_panel.h"
#include "../sdk/iv_engine_client.h"
#include "../sdk/i_client_mode.h"
#include "../sdk/i_client_entity.h"
#include "../sdk/i_client_entity_list.h"
#include "../sdk/c_global_vars.h"
#include "../sdk/i_input_system.h"
#include "../sdk/i_material_system.h"
#include "../sdk/iv_model_render.h"
#include "../sdk/c_prediction.h"
#include "../sdk/i_engine_trace.h"
#include "../sdk/i_physics.h"
#include "../sdk/convar.h"

namespace interfaces {
	extern iv_engine_client* engine_client;
	extern i_surface* surface;
	extern i_panel* panel;
	extern i_base_client_dll* client;
	extern i_client_entity_list* client_ent_list;
	extern i_client_mode* client_mode;
	extern i_inputsytem* input_system;
	extern i_material_system* mat_system;
	extern iv_model_render* model_render;
	extern i_move_helper* movement_helper;
	extern i_game_movement* game_movement;
	extern c_prediction* game_prediction;
	extern i_engine_trace* engine_trace;
	extern i_cvar* game_cvar;
	extern i_physics_surface_props* phys_surface;
	extern void* render_view; // whatever
	extern c_global_vars* global_vars;

	void init();
}