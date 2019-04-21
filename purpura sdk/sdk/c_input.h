#pragma once

#include "../utilities/vector.h"

#include "crc_checksum.h"

#include <cstring>

// Removed all the useless shit about joysticks and cleaned up code slightly

// --------------------------------------- DEFINES

enum cmd_buttons {
	in_attack = (1 << 0),
	in_jump = (1 << 1),
	in_duck = (1 << 2),
	in_forward = (1 << 3),
	in_back = (1 << 4),
	in_use = (1 << 5),
	in_cancel = (1 << 6),
	in_left = (1 << 7),
	in_right = (1 << 8),
	in_moveleft = (1 << 9),
	in_moveright = (1 << 10),
	in_attack2 = (1 << 11),
	in_run = (1 << 12),
	in_reload = (1 << 13),
	in_alt1 = (1 << 14),
	in_alt2 = (1 << 15),
	in_score = (1 << 16),
	in_speed = (1 << 17),
	in_walk = (1 << 18),
	in_zoom = (1 << 19),
	in_weapon1 = (1 << 20),
	in_weapon2 = (1 << 21),
	in_bullrush = (1 << 22),
	in_grenade1 = (1 << 23),
	in_grenade2 = (1 << 24),
	in_attack3 = (1 << 25)
};

// --------------------------------------- CLASSES

class bf_read;
class bf_write;

class c_usercmd
{
public:
	c_usercmd()
	{
		memset(this, 0, sizeof(*this));
	};
	virtual ~c_usercmd() {};

	crc32_t get_checksum(void) const
	{
		crc32_t crc;

		crc32_init(&crc);

		crc32_process_buffer(&crc, &command_number, sizeof(command_number));
		crc32_process_buffer(&crc, &tick_count, sizeof(tick_count));
		crc32_process_buffer(&crc, &viewangles, sizeof(viewangles));
		crc32_process_buffer(&crc, &aimdirection, sizeof(aimdirection));
		crc32_process_buffer(&crc, &forwardmove, sizeof(forwardmove));
		crc32_process_buffer(&crc, &sidemove, sizeof(sidemove));
		crc32_process_buffer(&crc, &upmove, sizeof(upmove));
		crc32_process_buffer(&crc, &buttons, sizeof(buttons));
		crc32_process_buffer(&crc, &impulse, sizeof(impulse));
		crc32_process_buffer(&crc, &weaponselect, sizeof(weaponselect));
		crc32_process_buffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		crc32_process_buffer(&crc, &random_seed, sizeof(random_seed));
		crc32_process_buffer(&crc, &mousedx, sizeof(mousedx));
		crc32_process_buffer(&crc, &mousedy, sizeof(mousedy));

		crc32_final(&crc);
		return crc;
	}

	int     command_number;     // 0x04 For matching server and client commands for debugging
	int     tick_count;         // 0x08 the tick the client created this command
	vec3_t  viewangles;         // 0x0C Player instantaneous view angles.
	vec3_t  aimdirection;       // 0x18
	float   forwardmove;        // 0x24
	float   sidemove;           // 0x28
	float   upmove;             // 0x2C
	int     buttons;            // 0x30 Attack button states
	char    impulse;            // 0x34
	int     weaponselect;       // 0x38 Current weapon id
	int     weaponsubtype;      // 0x3C
	int     random_seed;        // 0x40 For shared random functions
	short   mousedx;            // 0x44 mouse accum in x from create move
	short   mousedy;            // 0x46 mouse accum in y from create move
	bool    hasbeenpredicted;   // 0x48 Client only, tracks whether we've predicted this command at least once
	char    pad_0x4c[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};

class c_verified_usercmd
{
public:
	c_usercmd  m_cmd;
	crc32_t   m_crc;
};

class c_input
{
public:
	void*               pvftable;                     //0x00
	bool                m_f_track_ir_available;       //0x04
	bool                m_f_mouse_initialized;        //0x05
	bool                m_f_mouse_is_active;          //0x06
	bool                m_f_joystick_advanced_init;   //0x07
	char                pad_0x08[0x2C];               //0x08
	void*               m_pkeys;                      //0x34
	char                pad_0x38[0x6C];               //0x38
	int					pad_0x41;
	int					pad_0x42;
	bool                m_f_cam_intercepting_mouse;   //0x9C
	bool                m_f_cam_in_thirdperson;       //0x9D
	bool                m_f_cam_movingwithmouse;      //0x9E
	vec3_t				m_vec_camera_offset;          //0xA0
	bool                m_fcameradistancemove;        //0xAC
	int                 m_ncameraoldx;                //0xB0
	int                 m_ncameraoldy;                //0xB4
	int                 m_ncamerax;                   //0xB8
	int                 m_ncameray;                   //0xBC
	bool                m_cam_is_orthographic;        //0xC0
	vec3_t              m_ang_previous_viewangles;    //0xC4
	vec3_t              m_ang_previous_viewangles_t;  //0xD0
	float               m_fl_last_forward_move;       //0xDC
	int                 m_n_clear_input_state;        //0xE0
	char                pad_0xe4[0x8];                //0xE4
	c_usercmd*          m_p_commands;                 //0xEC
	c_verified_usercmd* m_p_verified_commands;        //0xF0
};

// --------------------------------------- ENUMS

enum button_code_t : int
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1
};

enum mouse_code_state_t
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED,
	BUTTON_DOUBLECLICKED,
};