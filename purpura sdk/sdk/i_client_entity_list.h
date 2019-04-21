#pragma once

#include "i_client_entity.h"
#include "i_base_handle.h"
#include "entities.h"

class i_client_entity_list
{
public:

	virtual i_client_networkable* get_client_networkable(int ent_num) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
	virtual c_base_entity*        get_client_entity(int ent_num) = 0;
	virtual i_client_entity*      get_client_entity_from_handle(c_base_handle h_ent) = 0;
	virtual int                   number_of_entities(bool b_include_non_networkable) = 0;
	virtual int                   get_highest_entity_index(void) = 0;
	virtual void                  set_max_entities(int max_ents) = 0;
	virtual int                   get_max_entities() = 0;
};
