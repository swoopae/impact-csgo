#include "misc.h"

#include "../../interfaces/interfaces.h"

#include "../../utilities/globals.h"
#include "../../utilities/utilities.h"

#include "../../menu/settings.h"

void features::miscellaneous::bunnyhop(c_usercmd * cmd) {
	if (!c_config::misc::bunnyhop)
		return;

	if (global_variables::local_player->move_type() == move_types::ladder)
		return;

	static bool last_jumped = false;
	static bool should_fake = false;

	if (!last_jumped && should_fake) {
		should_fake = false;
		cmd->buttons |= in_jump;
	}
	else if (cmd->buttons & in_jump) {
		if (global_variables::local_player->flags() & fl_onground)
			should_fake = last_jumped = true;
		else {
			cmd->buttons &= ~in_jump;
			last_jumped = false;
		}
	}
	else should_fake = last_jumped = false;
}

void features::miscellaneous::clantag_spam() {
	if (!c_config::misc::clantag_changer)
		return;

	int server_time = ((float)interfaces::global_vars->interval_per_tick * global_variables::local_player->tickbase());
	static int counter = 0;
	int value = server_time % 30;

	if (counter % 19 == 0) {
		switch (value)
		{
		case 0:global_utils::set_clantag(" ", "[redacted]"); break;
		case 1:global_utils::set_clantag("n ", "[redacted]"); break;
		case 2:global_utils::set_clantag("ne ", "[redacted]"); break;
		case 3:global_utils::set_clantag("net ", "[redacted]"); break;
		case 4:global_utils::set_clantag("netf ", "[redacted]"); break;
		case 5:global_utils::set_clantag("netfl ", "[redacted]"); break;
		case 6:global_utils::set_clantag("netfli ", "[redacted]"); break;
		case 7:global_utils::set_clantag("netflix ", "[redacted]"); break;
		case 8:global_utils::set_clantag("netflix& ", "[redacted]"); break;
		case 9:global_utils::set_clantag("netflix&c ", "[redacted]"); break;
		case 10:global_utils::set_clantag("netflix&ch ", "[redacted]"); break;
		case 11:global_utils::set_clantag("netflix&che ", "[redacted]"); break;
		case 12:global_utils::set_clantag("netflix&chea ", "[redacted]"); break;
		case 13:global_utils::set_clantag("netflix&cheat ", "[redacted]"); break;
		case 14:global_utils::set_clantag("netflix&cheats ", "[redacted]"); break;
		case 15:global_utils::set_clantag("netflix&cheats ", "[redacted]"); break;
		case 16:global_utils::set_clantag("netflix&cheat ", "[redacted]"); break;
		case 17:global_utils::set_clantag("netflix&chea ", "[redacted]"); break;
		case 18:global_utils::set_clantag("netflix&che ", "[redacted]"); break;
		case 19:global_utils::set_clantag("netflix&ch ", "[redacted]"); break;
		case 20:global_utils::set_clantag("netflix&c ", "[redacted]"); break;
		case 21:global_utils::set_clantag("netflix& ", "[redacted]"); break;
		case 22:global_utils::set_clantag("netflix ", "[redacted]"); break;
		case 23:global_utils::set_clantag("netfli ", "[redacted]"); break;
		case 24:global_utils::set_clantag("netfl ", "[redacted]"); break;
		case 25:global_utils::set_clantag("netf ", "[redacted]"); break;
		case 26:global_utils::set_clantag("net ", "[redacted]"); break;
		case 27:global_utils::set_clantag("ne ", "[redacted]"); break;
		case 28:global_utils::set_clantag("n ", "[redacted]"); break;
		case 29:global_utils::set_clantag(" ", "[redacted]"); break;
		}
	}
	counter++;
}

void features::miscellaneous::on_create_move(c_usercmd* cmd) {
	this->bunnyhop(cmd);
	this->clantag_spam();
}