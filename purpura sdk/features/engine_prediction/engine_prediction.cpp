#include "engine_prediction.h"

int *random_prediction_seed;
float old_curtime;
float old_frame_time;

void features::engine_prediction::start_prediction(c_base_entity* local_player, c_usercmd* cmd) {
	if (!random_prediction_seed)
		random_prediction_seed = *reinterpret_cast<int**>(global_utils::get_signature("client_panorama.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);

	c_move_data move_data;

	// store these bitches
	old_curtime = interfaces::global_vars->curtime;
	old_frame_time = interfaces::global_vars->frametime;

	interfaces::global_vars->curtime = local_player->tickbase() * interfaces::global_vars->interval_per_tick;
	interfaces::global_vars->frametime = interfaces::global_vars->interval_per_tick;

	// ida said i should do this so i will
	cmd->buttons |= *reinterpret_cast<uint8_t*>(uintptr_t(local_player) + 0x3310);

	interfaces::game_movement->start_track_prediction_errors(local_player);

	memset(&move_data, 0, sizeof(move_data));

	interfaces::movement_helper->set_host(local_player);
	interfaces::game_prediction->setup_move(local_player, cmd, interfaces::movement_helper, &move_data);

	interfaces::game_movement->process_movement(local_player, &move_data);

	interfaces::game_prediction->finish_move(local_player, cmd, &move_data);
}

void features::engine_prediction::end_prediction(c_base_entity* local_player) {
	// reset everything
	interfaces::game_movement->finish_track_prediction_errors(local_player);
	interfaces::movement_helper->set_host(0);
	interfaces::global_vars->curtime = old_curtime;
	interfaces::global_vars->frametime = old_frame_time;
	*random_prediction_seed = -1;
}