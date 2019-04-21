#include "entities.h"
#include "i_base_handle.h"
#include "../interfaces/interfaces.h"

// this is incorrect please fix later owo cutie
c_base_combat_weapon* c_base_entity::active_weapon() {
	const auto weapon_data = get_value < unsigned long >(netvar_manager->get_offset("DT_BaseCombat_Character", "m_hActiveWeapon"));
	return reinterpret_cast<c_base_combat_weapon*>(interfaces::client_ent_list->get_client_entity_from_handle(weapon_data));
}