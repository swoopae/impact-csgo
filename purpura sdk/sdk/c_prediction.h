#pragma once
#include "..\utilities\utilities.h"

#define MAX_SPLITSCREEN_PLAYERS 1

class c_base_handle;
class c_base_entity;
class i_client_entity;
class c_usercmd;

class i_move_helper
{
public:
	virtual void _vpad() = 0;
	virtual void set_host(c_base_entity* host) = 0;
};
//extern i_move_helper* g_pMoveHelper;

struct c_move_data { byte data[184]; };

class i_game_movement
{
public:
	virtual			~i_game_movement(void) {}

	virtual void	process_movement(c_base_entity *player, c_move_data *movement) = 0;
	virtual void	reset(void) = 0;
	virtual void	start_track_prediction_errors(c_base_entity *player) = 0;
	virtual void	finish_track_prediction_errors(c_base_entity *player) = 0;
	virtual void	difference_print(char const *fmt, ...) = 0;

	virtual vec3_t const&	player_minimums(bool ducked) const = 0;
	virtual vec3_t const&	player_maximums(bool ducked) const = 0;
	virtual vec3_t const&   player_view_offset(bool ducked) const = 0;

	virtual bool			is_moving_player_stuck(void) const = 0;
	virtual c_base_entity*	get_moving_player(void) const = 0;
	virtual void			unblock_pusher(c_base_entity* player, c_base_entity *pusher) = 0;

	virtual void    SetupMovementBounds(c_move_data *movement) = 0;
};
//extern i_game_movement* g_pMovement;

class c_prediction
{
public:
	virtual ~c_prediction(void) = 0;
	virtual void initialize(void) = 0;
	virtual void shutdown(void) = 0;
public:
	virtual void update
	(
		int startframe,
		bool validframe,
		int incoming_acknowledged,
		int outgoing_command
	);

	virtual void pre_entity_packet_recieved(int commands_acknowledged, int current_world_update_packet);
	virtual void post_entity_packet_recieved(void);
	virtual void post_network_data_recieved(int commands_acknowledged);

	virtual void on_recieve_uncompressed_packed(void);

	// engine needs to be able to get predicted values
	virtual void get_view_origin(vec3_t& org);
	virtual void set_view_origin(vec3_t& org);
	virtual void get_view_angles(vec3_t& ang); //index: 10
	virtual void set_view_angles(vec3_t& ang);

	virtual void get_local_view_angles(vec3_t& ang);
	virtual void set_local_view_angles(vec3_t& ang);

	virtual bool in_prediction(void) const;
	virtual bool is_first_time_predicted(void) const;

	virtual int get_last_acknowledged_cmd_number(void) const;

#if !defined( NO_ENTITY_PREDICTION )
	virtual int get_incoming_packet_number(void) const;
#endif

	virtual void check_moving_ground(i_client_entity* player, double frametime);
	virtual void run_command(i_client_entity* player, c_usercmd* cmd, i_move_helper* moveHelper);

	virtual void setup_move(c_base_entity* player, c_usercmd* cmd, i_move_helper* helper, c_move_data* movement); //index: 20
	virtual void finish_move(c_base_entity* player, c_usercmd* cmd, c_move_data* movement);
	virtual void set_ideal_pitch(int slot, i_client_entity* player, const vec3_t& origin, const vec3_t& angles, const vec3_t& viewheight);

	virtual void check_error(int slot, i_client_entity* player, int commands_acknowledged);

public:
	virtual void _update
	(
		int nSlot,
		bool received_new_world_update,
		bool validframe,
		int incoming_acknowledged,
		int outgoing_command
	);

	// check if prediction works
	bool perform_prediction(int slot, i_client_entity* local_player, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);
	void shift_intermediate_data_forward(int slot, int slots_to_remove, int previous_last_slot);
	void restore_entity_to_predicted_frame(int slot, int predicted_frame);
	int first_command_to_execute(int slot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

	// hurr durr dont call so we dont magdump hurr durr *snoorrrrrt* le funny amiright guys
	void dump_entity(i_client_entity* ent, int commands_acknowledged);
	void shutdown_predictables(void);
	void reinit_predictables(void);
	void remove_stale_predicted_entities(int slot, int last_command_packet);
	void restore_original_ent_state(int slot);
	void run_simulation(int current_command, float curtime, c_usercmd* cmd, i_client_entity* local_player);
	void untouch(int slot);
	void store_prediction_results(int slot, int predicted_frame);

	// always returns no beacuse we should never magdump
	bool should_dump_entity(i_client_entity* ent);
	void smooth_view_on_moving_platform(i_client_entity* player, vec3_t& offset);
	void reset_simulation_tick();

	void show_prediction_list_entry(int list_row, int show_list, i_client_entity* ent, int& totalsize, int& totalsize_intermediate);
	void finish_prediction_list(int list_row, int show_list, int totalsize, int totalsize_intermediate);
	void check_predict_convar();

#if !defined( NO_ENTITY_PREDICTION )
	// nothing idk
#endif
};

//extern CPrediction* g_pPrediction;