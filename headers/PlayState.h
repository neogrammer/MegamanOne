#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include <GameStateMgr.h>
#include <GameState.h>
#include <SFML/Graphics/View.hpp>
#include<rec.h>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <DynoPlayer.h>
#include <StatTile.h>
#include <DFlyPad.h>
#include <DCannonTurtle.h>
#include <GameStateMgr.h>
class Tilemap;
class PlayState : public GameState
{
	DFlyPad flypad1{};
	DFlyPad flypad2{};
	DFlyPad flypad3{};

	std::shared_ptr<DCannonTurtle> dTurtle{};

	Tilemap* tmap{};
	ResolutionDir resDir = ResolutionDir::None;
	sf::View worldSpace_{};
	float bgOffset{ 1600.f };
	std::shared_ptr<DynoPlayer> dPlayer;
	std::vector<std::shared_ptr<DynoEnemy> > enemies{};


	// new collision variables
	std::vector<rec> objs;
	//bool playerGrounded{ false };
	//bool jumpPressed{ false };
//	bool playerFacingRight{ true };
public:
	PlayState(GameStateMgr* mgr_);
	void processEvent(sf::Event& e) override final;
	virtual ~PlayState();
	virtual void input();
	virtual void update();
	virtual void render();
	void createWorld();

	void drawBG();
	void setViewToPlayer();
	void drawPlatforms();
	void drawActors();
	void updatePlatforms();
	void updateEnemies();
	void updatePlayer();
	void updateProjectiles();

};

#endif