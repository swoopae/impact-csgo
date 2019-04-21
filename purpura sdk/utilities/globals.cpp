#include "globals.h"
#include "../sdk/entities.h"

namespace global_variables {
	c_usercmd*     global_cmd = nullptr;
	c_base_entity* local_player = nullptr;
	bool           b_send_packet = true;
	vec3_t         original_angles;
}