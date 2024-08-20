#include <pch.h>
#include "SplashState.h"

SplashState::SplashState(GameStateMgr* mgr_)
	: GameState(mgr_)
{
}

SplashState::~SplashState()
{
}

void SplashState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Title, true);
		}
	}
}

void SplashState::input()
{
	
}

void SplashState::update()
{
}

void SplashState::render()
{
	sf::Sprite logoScreen = {};
	logoScreen.setTexture(Cfg::textures.get((int)Cfg::Textures::Logo));
	gWnd.draw(logoScreen);
}