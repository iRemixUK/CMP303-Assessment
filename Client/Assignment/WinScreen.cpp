#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow* hwnd, Input* in, int state)
{
	window = hwnd;
	input = in;

	if (state == 1)
	{
		//state->setCurrentState(State::Player1Win);
		winScreenTexture.loadFromFile("gfx/Player1Win.png");
		winScreen.setTexture(&winScreenTexture);
		winScreen.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	}

	if (state == 2)
	{
		//state->setCurrentState(State::Player2Win);
		winScreenTexture.loadFromFile("gfx/Player2Win.png");
		winScreen.setTexture(&winScreenTexture);
		winScreen.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	}

}

void WinScreen::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		//state->setCurrentState(State::LEVEL);
	}
}

void WinScreen::update(float dt)
{

}

void WinScreen::render()
{
	beginDraw();
	window->draw(winScreen);
	endDraw();
}

void WinScreen::beginDraw()
{
	window->clear(sf::Color(255, 255, 255));
}

void WinScreen::endDraw()
{
	window->display();
}
