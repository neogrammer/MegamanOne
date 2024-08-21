#include <pch.h>
#include "PausedState.h"

PausedState::PausedState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}

PausedState::~PausedState()
{
}

void PausedState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::P)
	{
		owner->popTop();
	}
}

void PausedState::input()
{
}

void PausedState::update()
{
}

void PausedState::render()
{
	

	sf::RectangleShape screenOverlay{ {1600.f, 900.f} };

	sf::Text pausedText{};
	pausedText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	pausedText.setString("Paused");
	pausedText.setCharacterSize(44U);
	pausedText.setPosition({ 750.f, 420.f });
	pausedText.setFillColor(sf::Color::White);
	pausedText.setOutlineColor(sf::Color::Green);
	pausedText.setOutlineThickness(3);

	screenOverlay.setFillColor(sf::Color(0, 0, 0, 50));

	gWnd.draw(screenOverlay);
	gWnd.draw(pausedText);

}
