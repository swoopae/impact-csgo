#include "c_input.h"

class i_inputsytem
{
public:
	void enable_input(bool b_enable)
	{
		using original_fn = void(__thiscall*)(void*, bool);
		return (*(original_fn**)this)[11](this, b_enable);
	}

	button_code_t vkey_to_button_code(int n_virtual_key)
	{
		typedef button_code_t(__thiscall * original_fn)(void*, int);
		return (*(original_fn * *)this)[45](this, n_virtual_key);
	}

	const char* button_code_to_string(button_code_t button_code)
	{
		typedef const char* (__thiscall * original_fn)(void*, button_code_t);
		return (*(original_fn * *)this)[40](this, button_code);
	}

	bool is_button_down(button_code_t button_code)
	{
		typedef bool(__thiscall * original_fn)(void*, button_code_t);
		return (*(original_fn * *)this)[15](this, button_code);
	}
};