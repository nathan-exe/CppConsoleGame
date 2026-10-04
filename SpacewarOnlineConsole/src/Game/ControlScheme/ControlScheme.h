#pragma once

struct ControlScheme {
	ControlScheme(const char up, const char left, const char down, const char right, const char shoot)
		: key_up(up),key_left(left), key_down(down), key_right(right),key_shoot(shoot)
	{}

	const char key_up;
	const char key_left;
	const char key_down;
	const char key_right;
	const char key_shoot;
};