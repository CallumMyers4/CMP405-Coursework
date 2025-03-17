#pragma once

struct InputCommands
{
	enum class Modes
	{
		normal = 1,
		translate = 2,
		rotate = 3,
		scale = 4

	};

	//store which mode is currently active
	Modes currentMode = Modes::normal;

	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	bool focus, unfocus;
	bool rotRight;
	bool rotLeft;
	bool ctrl;
	bool leftMouseDown = false;
	bool rightMouseDown = false;

	int mouseY = 0;
	int mouseX = 0;
};
