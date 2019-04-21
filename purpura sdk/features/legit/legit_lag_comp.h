#pragma once

#include "../../interfaces/interfaces.h"
#include "../../utilities/math.h"

namespace features {
	struct backtrack_tick {
		float simulation_time;
		vec3_t hitbox_position;
		vec3_t origin;
		vec3_t angles;
		matrix3x4_t bt_matrix[128];
	};
	class legit_lag_comp {
	public:
		void on_create_move();
		vec3_t angle_vector(vec3_t to_convert) {
			auto y_sin = sin(to_convert.y / 180.f * static_cast<float>(pi_aprox));
			auto y_cos = cos(to_convert.y / 180.f * static_cast<float>(pi_aprox));

			auto x_sin = sin(to_convert.x / 180.f * static_cast<float>(pi_aprox));
			auto x_cos = cos(to_convert.x / 180.f * static_cast<float>(pi_aprox));

			return vec3_t(x_cos * y_cos, x_cos * y_sin, -x_sin);
		}

		float distance_point_to_line(vec3_t point, vec3_t origin, vec3_t direction) {
			auto delta = point - origin;

			auto temp = delta.Dot(direction) / (direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
			if (temp < 0.000001f)
				return FLT_MAX;

			auto temp_meme = origin + (direction * temp);
			return (point - temp_meme).Length();
		}
	};
	extern legit_lag_comp* lag_comp;
}