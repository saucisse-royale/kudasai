#pragma once

enum InputStateManagerType {
	KEY, MOUSE, MOVE
};

struct InputStateManager
{
	InputStateManagerType type;
	int code;
	bool press;
	double x;
	double y;
};

