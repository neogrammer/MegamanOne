#include <pch.h>
#include <GameState.h>

GameState::GameState(GameStateMgr* owner_)
	: paused{false}
	, owner{owner_}
{
}

GameState::~GameState()
{
	owner = nullptr;
}
