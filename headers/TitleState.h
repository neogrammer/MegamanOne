#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include <GameStateMgr.h>
#include <GameState.h>
class TitleState : public GameState
{
public:
	TitleState(GameStateMgr* mgr_);
	virtual ~TitleState();
	void processEvent(sf::Event& e) override final;

	virtual void input();
	virtual void update();
	virtual void render();

};

#endif