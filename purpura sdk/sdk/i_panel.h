#include "../utilities/utilities.h"

class i_panel {
public:
	const char *get_name(unsigned int vgui_panel) {
		typedef const char*(__thiscall *o_fn)(PVOID, unsigned int);
		return global_utils::legacy_v_function<o_fn>(this, 36)(this, vgui_panel);
	}
};