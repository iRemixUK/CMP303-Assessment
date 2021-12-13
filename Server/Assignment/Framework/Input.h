// Input class
// Class stores the current state on keyboard and mouse input.
// Store which keys are pressed or released, mouse position and mouse button presses.
// @author Paul Robertson

#pragma once

class Input
{
private:
	// Mouse structure, store mouse relevant information
	struct Mouse
	{
		int x, y;
		bool left, right;
	};

public:
	Input();
	// Functions for setting key as pressed, released and checking current state.
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	// Functions are mouse input, including getting and setting current position and mouse button presses.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setMouseLDown(bool down);
	bool isMouseLDown();
	void setMouseRDown(bool down);
	bool isMouseRDown();
	
private:
	// Array of booleans representing keys (pressed = true, released = false)
	bool keys[256]{ false };
	// Mouse variable
	Mouse mouse;
};
