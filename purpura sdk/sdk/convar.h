#pragma once

class convar
{
public:
	char pad_0x00[0x4];
	convar* p_next;
	int32_t b_registered;
	char* psz_name;
	char* psz_help_string;
	int32_t n_flags;
	char pad_0x18[0x4];
	convar* p_parent;
	char* psz_default_value;
	char* str_string;
	int32_t str_length;
	float f_value;
	int32_t n_value;
	int32_t b_has_min;
	float f_min_val;
	int32_t b_has_max;
	float f_max_val;
	void* fn_change_callback;

	float get_float(void) const {
		auto temp = *(int*)(&f_value);
		auto temp_result = (int)(temp ^ (DWORD)this);
		return *(float*)(&temp_result);
	}

	int get_int(void) const {
		auto temp = *(int*)(&f_value);
		auto temp_result = (int)(temp ^ (DWORD)this);
		return *(int*)(&temp_result);
	}

	bool get_bool(void) const {
		return !!get_int();
	}

	void set_value(const char* value) {
		typedef void(__thiscall* original_fn)(void*, const char*);
		return global_utils::legacy_v_function<original_fn>(this, 14)(this, value);
	}
};

class i_cvar
{
public:
	convar* find_var(const char* var_name) {
		typedef convar*(__thiscall* find_var_fn)(void*, const char*);
		return global_utils::legacy_v_function<find_var_fn>(this, 14)(this, var_name);
	}

	void console_color_print_f(const color& col, const char* cool_char) {
		typedef void*(__thiscall* console_color_print_fn)(void*, const color&, const char*);
		global_utils::legacy_v_function<console_color_print_fn>(this, 24)(this, col, cool_char);
	}
};