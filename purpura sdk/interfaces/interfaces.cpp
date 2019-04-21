#include "interfaces.h"
#include "../utilities/utilities.h"

namespace interfaces {
	iv_engine_client*           engine_client = nullptr;
	i_surface*                  surface = nullptr;
	i_base_client_dll*          client = nullptr;
	i_client_entity_list*       client_ent_list = nullptr;
	i_client_mode*              client_mode = nullptr;
	i_panel*                    panel = nullptr;
	i_material_system*          mat_system = nullptr;
	void*                       render_view = nullptr;
	iv_model_render*            model_render = nullptr;
	i_move_helper*              movement_helper = nullptr;
	i_game_movement*            game_movement = nullptr;
	c_prediction*               game_prediction = nullptr;
	i_engine_trace*             engine_trace = nullptr;
	i_cvar*                     game_cvar = nullptr;
	i_physics_surface_props*    phys_surface = nullptr;
	i_inputsytem*               input_system = nullptr;
	c_global_vars*              global_vars = nullptr;

	void interfaces::init() {
		global_utils::console_log("trying to get interfaces...");

		engine_client = global_utils::get_interface <iv_engine_client>((char*) "engine.dll", (char*) "VEngineClient014");
		std::cout << "[interface:] engine_client: 0x" << engine_client << "\n";
		surface = global_utils::get_interface <i_surface>((char*) "vguimatsurface.dll", (char*) "VGUI_Surface031");
		std::cout << "[interface:] surface: 0x" << surface << "\n";
		client = global_utils::get_interface <i_base_client_dll>((char*) "client_panorama.dll", (char*) "VClient018");
		std::cout << "[interface:] client: 0x" << client << "\n";
		client_ent_list = reinterpret_cast <i_client_entity_list*> (global_utils::find_interface("client_panorama.dll", "VClientEntityList"));
		std::cout << "[interface:] client_ent_list: 0x" << client_ent_list << "\n";
		model_render = reinterpret_cast <iv_model_render*> (global_utils::find_interface("engine.dll", "VEngineModel"));
		std::cout << "[interface:] model_render: 0x" << model_render << "\n"; // returned null cuz im retart
		panel = reinterpret_cast <i_panel*> (global_utils::find_interface("vgui2.dll", "VGUI_Panel"));
		std::cout << "[interface:] panel: 0x" << panel << "\n";
		mat_system = reinterpret_cast <i_material_system*> (global_utils::find_interface("materialsystem.dll", "VMaterialSystem"));
		std::cout << "[interface:] mat_system: 0x" << mat_system << "\n";
		game_prediction = reinterpret_cast <c_prediction*> (global_utils::find_interface("client_panorama.dll", "VClientPrediction"));
		std::cout << "[interface:] game_prediction: 0x" << game_prediction << "\n";
		game_movement = reinterpret_cast <i_game_movement*> (global_utils::find_interface("client_panorama.dll", "GameMovement"));
		std::cout << "[interface:] game_movement: 0x" << game_movement << "\n";
		engine_trace = reinterpret_cast <i_engine_trace*> (global_utils::find_interface("engine.dll", "EngineTraceClient"));
		std::cout << "[interface:] engine_trace: 0x" << engine_trace << "\n";
		render_view = reinterpret_cast<void*> (global_utils::find_interface("engine.dll", "VEngineRenderView"));
		std::cout << "[interface:] render_view: 0x" << render_view << "\n";
		input_system = reinterpret_cast <i_inputsytem*> (global_utils::find_interface("inputsystem.dll", "InputSystemVersion"));
		std::cout << "[interface:] input_system: 0x" << input_system << "\n";
		game_cvar = reinterpret_cast <i_cvar*> (global_utils::find_interface("vstdlib.dll", "VEngineCvar"));
		std::cout << "[interface:] game_cvar: 0x" << game_cvar << "\n";
		phys_surface = reinterpret_cast <i_physics_surface_props*> (global_utils::find_interface("vphysics.dll", "VPhysicsSurfaceProps"));
		std::cout << "[interface:] phys_surface: 0x" << phys_surface << "\n";
		movement_helper = **reinterpret_cast<i_move_helper***>((global_utils::get_signature("client_panorama.dll", "8B 0D ? ? ? ? 8B 46 08 68") + 0x2));
		std::cout << "[interface:] movement_helper: 0x" << movement_helper << "\n";

		client_mode = **(i_client_mode***)((*(DWORD**)client)[10] + 0x5);
		std::cout << "[interface:] client_mode: 0x" << client_mode << "\n";
		global_vars = **reinterpret_cast<c_global_vars***>((*reinterpret_cast<uintptr_t**>(client))[0] + 0x1Bu);
		std::cout << "[interface:] global_vars: 0x" << global_vars << "\n";

		global_utils::console_log("got all interfaces...");
	}
}