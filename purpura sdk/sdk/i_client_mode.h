#pragma once

#include "i_client_entity.h"

class i_client_mode {
public:
	bool should_draw_entity(i_client_entity *p_entity) {
		typedef bool(__thiscall *o_fn)(void*, i_client_entity*);
		return global_utils::legacy_v_function<o_fn>(this, 14)(this, p_entity);
	}
};

/*
using original_fn = bool(__thiscall*)(i_client_mode*, i_client_entity);
return (*(original_fn**)this)[14](this, *p_entity); // nu stiu daca e corect momentan nu ma intereseaza
*/