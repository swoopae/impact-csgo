#pragma once

#include "../utilities/netvar_manager.h"
#include "../utilities/utilities.h"

#include "recv.h"
#include "client_class.h"
#include "structs.h"
#include "collideable.h"
#include "weapon_definitions.h"

#define bone_hitbox_cool	0x00000100 // 256

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};

// predefine so we can get active weapon in c_base_entity
class c_base_combat_weapon;

class c_base_entity {
private:
	template<class T>
	T get_pointer(const int offset) {
		return reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}

	template<class T>
	T get_value(const int offset) {
		return *reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}
public:
	// --------------------------- OFFSETS ---------------------------
	void* animating() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}
	c_client_class* get_client_class() {
		void* __networkable = this->networkable();
		typedef c_client_class*(__thiscall* orig_fn)(void*);
		return global_utils::legacy_v_function<orig_fn>(__networkable, 2)(__networkable);
	}
	bool dormant() {
		return *reinterpret_cast <bool*> (uintptr_t(this) + 0xED);
	}
	int team() {
		return get_value < int >(netvar_manager->get_offset("DT_BaseEntity", "m_iTeamNum"));
	}
	bool life_state() {
		return get_value < bool >(netvar_manager->get_offset("DT_BasePlayer", "m_lifeState"));
	}
	int health() {
		return get_value < int >(netvar_manager->get_offset("DT_BasePlayer", "m_iHealth"));
	}
	int armour() {
		return get_value < int >(netvar_manager->get_offset("DT_CSPlayer", "m_ArmorValue"));
	}
	bool helmet() {
		return get_value < float >(netvar_manager->get_offset("DT_CSPlayer", "m_bHasHelmet"));
	}
	bool heavy_armour() {
		return get_value < float >(netvar_manager->get_offset("DT_CSPlayer", "m_bHasHeavyArmor"));
	}
	entity_flags flags() {
		return get_value < entity_flags >(netvar_manager->get_offset("DT_BasePlayer", "m_fFlags"));
	}
	move_types move_type() {
		return get_value < move_types >(netvar_manager->get_offset("DT_BaseEntity", "m_nRenderMode") + 1);
	}
	vec3_t origin() {
		return get_value < vec3_t >(netvar_manager->get_offset("DT_BaseEntity", "m_vecOrigin"));
	}
	vec3_t obb_min() {
		return get_value < vec3_t >(netvar_manager->get_offset("DT_BaseEntity", "m_vecMins"));
	}
	vec3_t obb_max() {
		return get_value < vec3_t >(netvar_manager->get_offset("DT_BaseEntity", "m_vecMaxs"));
	}
	float crouch_ammount() {
		return get_value < float >(netvar_manager->get_offset("DT_BasePlayer", "m_flDuckAmount"));
	}
	int money() {
		return get_value < int >(netvar_manager->get_offset("DT_CSPlayer", "m_iAccount"));
	}
	int tickbase() {
		return get_value < int >(netvar_manager->get_offset("DT_BasePlayer", "localdata", "m_nTickBase"));
	}
	float simulation_time() {
		return get_value < float >(netvar_manager->get_offset("DT_BaseEntity", "m_flSimulationTime"));
	}
	c_base_combat_weapon* active_weapon();

	// --------------------------- OTHERS ---------------------------
	vec3_t& abs_origin() {
		return global_utils::call_v_table<vec3_t&(__thiscall*)(void*)>(this, 10)(this);
	}
	bool is_alive() {
		return this->health() > 0 && !this->life_state();
	}
	int draw_model(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn**)animating())[9](animating(), flags, alpha);
	}
	bool setup_bones(matrix3x4_t* out, int max_bones, int mask, float time) {
		if (!this) return false;
		using original_fn = bool(__thiscall*)(void*, matrix3x4_t*, int, int, float);
		return (*(original_fn**)animating())[13](animating(), out, max_bones, mask, time);
	}
	vec3_t bone_pos(int i) {
		matrix3x4_t bone_matrix[128];
		if (this->setup_bones(bone_matrix, 128, bone_hitbox_cool, GetTickCount64())) {
			return vec3_t(bone_matrix[i][0][3], bone_matrix[i][1][3], bone_matrix[i][2][3]);
		}
		return vec3_t(0, 0, 0);
	}
	vec3_t& abs_angles() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[11](this);
	}
	int ent_index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)networkable())[10](networkable());
	}
};

class c_base_combat_weapon : public c_base_entity {
private:
	template<class T>
	T get_pointer(const int offset) {
		return reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}

	template<class T>
	T get_value(const int offset) {
		return *reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}
public:
	// --------------------------- OFFSETS ---------------------------
	item_definition_index get_item_definition_index() {
		return get_value< item_definition_index >(netvar_manager->get_offset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex"));
	}
	float get_next_primary_attack() {
		return get_value< float >(netvar_manager->get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextPrimaryAttack"));
	}
	int get_ammo() {
		return get_value< int >(netvar_manager->get_offset("DT_BaseCombatWeapon", "m_iClip1")); // ooooooooof
	}

	// --------------------------- OTHERS ---------------------------
	weapon_info_t* get_cs_weapon_data() {
		static auto system = *reinterpret_cast<c_weapon_system**>(global_utils::get_signature("client_panorama.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0") + 0x2u);
		return system->get_weapon_data(this->get_item_definition_index());
	}
	std::string sanitized_weapon_name() {
		std::string weapon_name = std::string(this->get_cs_weapon_data()->szWeaponName);
		weapon_name.erase(0, 7);
		return weapon_name;
	}
};