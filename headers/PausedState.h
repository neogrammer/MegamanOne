#ifndef PAUSEDSTATE_H__
#define PAUSEDSTATE_H__
#include <GameStateMgr.h>
#include <GameState.h>
class PausedState : public GameState
{
public:
	PausedState(GameStateMgr* mgr_);
	virtual ~PausedState();
	void processEvent(sf::Event& e) override final;

	virtual void input();
	virtual void update();
	virtual void render();

};

#endif