#ifndef GAMESTATEMGR_H__
#define GAMESTATEMGR_H__
#include <string>

#include <memory>
#include <utility>
#include <stack>
#include <unordered_map>
#include <Cfg.h>
class GameState;

class GameStateMgr
{
	GameStateType nextState{ GameStateType::None };
	bool needsToSwitchState{ false };
	bool popOffCurrent{ true };

	std::stack<GameState*> stateStack;

	std::unordered_map<GameStateType, std::unique_ptr<GameState> > stateMap{};
public:
	GameStateMgr();
	~GameStateMgr();
	GameStateMgr& operator=(const GameStateMgr&) = delete;
	GameStateMgr(const GameStateMgr&) = delete;
	GameStateMgr& operator=(GameStateMgr&&) = delete;
	GameStateMgr(GameStateMgr&&) = delete;

	void input();
	void update();
	void render();
	void safeStateSwitch();
	void processEvent(sf::Event& e_);
	void changeState(GameStateType type_, bool popCurrent_ = true);


};

#endif