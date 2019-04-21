#include "utilities.h"
#include "../interfaces/interfaces.h"

typedef void* (*create_interface_fn) (const char *name, int *return_code);

void* global_utils::find_interface(const char* module, const char* interface_name) {
	void* interf = nullptr;
	auto create_interface = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));

	char possible_interface_name[1024];
	for (int i = 1; i < 100; i++)
	{
		sprintf(possible_interface_name, "%s0%i", interface_name, i);
		interf = create_interface(possible_interface_name, 0);
		if (interf)
			break;

		sprintf(possible_interface_name, "%s00%i", interface_name, i);
		interf = create_interface(possible_interface_name, 0);
		if (interf)
			break;
	}

	return interf;
}

bool global_utils::world_to_screen(const vec3_t &origin, vec3_t &screen) {
	const auto screen_transform = [&origin, &screen]() -> bool
	{
		static std::uintptr_t p_viewmatrix;
		if (!p_viewmatrix)
		{
			p_viewmatrix = static_cast <std::uintptr_t> (global_utils::get_signature("client_panorama.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
			p_viewmatrix += 3;
			p_viewmatrix = *reinterpret_cast<std::uintptr_t*>(p_viewmatrix);
			p_viewmatrix += 176;
		}

		const VMatrix& w2s_matrix = *reinterpret_cast<VMatrix*>(p_viewmatrix);
		screen.x = w2s_matrix.m[0][0] * origin.x + w2s_matrix.m[0][1] * origin.y + w2s_matrix.m[0][2] * origin.z + w2s_matrix.m[0][3];
		screen.y = w2s_matrix.m[1][0] * origin.x + w2s_matrix.m[1][1] * origin.y + w2s_matrix.m[1][2] * origin.z + w2s_matrix.m[1][3];
		screen.z = 0.0f;

		float w = w2s_matrix.m[3][0] * origin.x + w2s_matrix.m[3][1] * origin.y + w2s_matrix.m[3][2] * origin.z + w2s_matrix.m[3][3];

		if (w < 0.001f)
		{
			screen.x *= 100000;
			screen.y *= 100000;
			return true;
		}

		float invw = 1.f / w;
		screen.x *= invw;
		screen.y *= invw;

		return false;
	};

	if (!screen_transform())
	{
		int width, height;
		interfaces::engine_client->get_screen_size(width, height);

		screen.x = (width * 0.5f) + (screen.x * width) * 0.5f;
		screen.y = (height * 0.5f) - (screen.y * height) * 0.5f;

		return true;
	}
	return false;
}