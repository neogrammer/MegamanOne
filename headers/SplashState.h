#ifndef SPLASHSTATE_H__
#define SPLASHSTATE_H__
#include <GameStateMgr.h>
#include <GameState.h>
class SplashState : public GameState
{
public:
	SplashState(GameStateMgr* mgr_);
	virtual ~SplashState();
	void processEvent(sf::Event& e) override final;
	virtual void input();
	virtual void update();
	virtual void render();

};

#endif