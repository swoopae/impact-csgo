#pragma once

#include "../../sdk/c_input.h"

namespace features {
	class miscellaneous {
	public:
		void bunnyhop(c_usercmd * cmd);
		void clantag_spam();
		void on_create_move(c_usercmd * cmd);
	};

	extern miscellaneous* misc;
}