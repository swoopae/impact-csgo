#include "legit_lag_comp.h"

#include "../../utilities/globals.h"

matrix3x4_t bone_matrix[128];
features::backtrack_tick backtrack[64][14];

void features::legit_lag_comp::on_create_move() {
	int best_target = -1;
	float best_fov = 90.f;

	if (global_variables::local_player->health() <= 0)
		return;

	for (int i = 0; i <= 65; i++) {
		c_base_entity* ent = interfaces::client_ent_list->get_client_entity(i);

		if (!ent) continue;
		if (ent->health() < 0) continue;
		if (ent->dormant()) continue;
		if (ent->team() == global_variables::local_player->team()) continue;

		if (ent->health() > 0) {
			float sim_time = ent->simulation_time();
			ent->setup_bones(bone_matrix, 128, 0x0100, 0.f);

			backtrack[i][global_variables::global_cmd->command_number % 14] = backtrack_tick
			{
				sim_time,
				ent->bone_pos(8),
				ent->abs_origin(),
				ent->abs_angles(),
				bone_matrix[128]
			};

			vec3_t view_direction = angle_vector(global_variables::global_cmd->viewangles);
			float fov = distance_point_to_line(ent->bone_pos(8), global_variables::local_player->bone_pos(8), view_direction);

			if (best_fov > fov) {
				best_fov = fov;
				best_target = i;
			}
		}
	}
	float best_target_simulation_time = 0.f;

	if (best_target != -1) {
		float temp = FLT_MAX;
		vec3_t view_direction = angle_vector(global_variables::global_cmd->viewangles);

		for (int t = 0; t < 14; ++t) {
			float fov = distance_point_to_line(backtrack[best_target][t].hitbox_position, global_variables::local_player->bone_pos(8), view_direction);
			if (temp > fov && backtrack[best_target][t].simulation_time > global_variables::local_player->simulation_time() - 1) {
				temp = fov;
				best_target_simulation_time = backtrack[best_target][t].simulation_time;
			}
		}

		if (global_variables::global_cmd->buttons & in_attack) {
			global_variables::global_cmd->tick_count = (int)(0.5f + (float)(best_target_simulation_time) / interfaces::global_vars->interval_per_tick);
		}
	}
}