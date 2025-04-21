#pragma once

struct InputCommands
{
	//the mode the program is currently using
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
	bool paste, pasteHeld;
	bool deleteKey, deleteKeyHeld;		//the second var will check if delete is being held, then prevent it from deleting multiple
	bool rotRight;
	bool rotLeft;
	bool ctrl, shift;
	bool leftMouseDown = false;
	bool rightMouseDown = false;

	int mouseY = 0;
	int mouseX = 0;
};
