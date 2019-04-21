#pragma once

#include "client_class.h"

class i_base_client_dll {
public:
	c_client_class * get_client_classes() {
		using original_fn = c_client_class * (__thiscall*)(i_base_client_dll*);
		return (*(original_fn**)this)[8](this);
	}
};

class i_client_entity {
public:
	int entity_index() {
		void *nigga_toilet = (void*)(this + 0x8);

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::legacy_v_function<o_fn>(nigga_toilet, 10)(nigga_toilet);
	}
};