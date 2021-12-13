#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include <cstdlib>
class WinScreen
{
public:
	WinScreen(sf::RenderWindow* hwnd, Input* in, int state);
	void handleInput(float dt);
	void update(float dt);
	void render();
private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
	sf::RenderWindow* window;
	Input* input;

	sf::Texture winScreenTexture;
	sf::RectangleShape winScreen;

};

