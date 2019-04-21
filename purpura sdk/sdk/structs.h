#pragma once

enum class move_types {
	none = 0,
	isometric,
	walk,
	step,
	fly,
	fly_gravity,
	physics,
	push,
	noclip,
	ladder,
	observer,
	custom,
	last = custom,
	max_bits = 4
};