#ifndef GAMESTATE_H__
#define GAMESTATE_H__
#include <GameStateMgr.h>

class GameState
{
protected:

	bool paused;

	GameStateMgr* owner;
public:
	GameState(GameStateMgr* owner_);
	virtual ~GameState();

	virtual void processEvent(sf::Event& e) = 0;
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

};

#endif