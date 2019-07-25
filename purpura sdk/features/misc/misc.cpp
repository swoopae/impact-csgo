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

	static std::string cur_clantag = " impacthack " ;
	static float oldtime;

	if (interfaces::global_vars->curtime - oldtime >= 0.5f) {
		std::string temp = (std::string&)cur_clantag;
		cur_clantag.erase(0, 1);
		cur_clantag += temp[0];
		global_utils::set_clantag(cur_clantag.c_str(), "impacthack");
		oldtime = interfaces::global_vars->curtime;
	}
}

void features::miscellaneous::on_create_move(c_usercmd* cmd) {
	this->bunnyhop(cmd);
	this->clantag_spam();
}
