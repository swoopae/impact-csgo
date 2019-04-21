#include "entities.h"
#include "i_base_handle.h"
#include "../interfaces/interfaces.h"

c_base_combat_weapon* c_base_entity::active_weapon() {
	static int offset = netvar_manager->get_offset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	const auto weapon_data = get_value<c_base_handle>(offset);
	return reinterpret_cast<c_base_combat_weapon*>(interfaces::client_ent_list->get_client_entity_from_handle(weapon_data));
}
