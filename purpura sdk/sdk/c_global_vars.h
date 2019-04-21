#pragma once

class c_global_vars
{
public:
	float     realtime;
	int       framecount;
	float     absolute_frame_time;
	float     absolute_frame_start_time_std_dev;
	float     curtime;
	float     frametime;
	int       max_clients;
	int       tickcount;
	float     interval_per_tick;
	float     interpolation_amount;
	int       sim_ticks_this_frame;
	int       network_protocol;
	void*     p_save_data;
	bool      b_client;
	bool      b_remote_client;
};