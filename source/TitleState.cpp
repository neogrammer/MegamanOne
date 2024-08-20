#include <pch.h>
#include "TitleState.h"

TitleState::TitleState(GameStateMgr* mgr_)
	: GameState(mgr_)
{
}

TitleState::~TitleState()
{
}

void TitleState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Play, true);
		}
	}
}

void TitleState::input()
{
}

void TitleState::update()
{
}

void TitleState::render()
{
	sf::Sprite logoScreen = {};
	logoScreen.setTexture(Cfg::textures.get((int)Cfg::Textures::Title));
	gWnd.draw(logoScreen);
}
