#ifndef GAME_H__
#define GAME_H__
#include <SFML/Graphics/View.hpp>
#include<rec.h>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <DynoPlayer.h>
#include <StatTile.h>
#include <DFlyPad.h>


struct lua_State;
class Tilemap;

class Game
{
	DFlyPad flypad1{};
	DFlyPad flypad2{};
	DFlyPad flypad3{};

	Tilemap* tmap{};
	ResolutionDir resDir = ResolutionDir::None;
	sf::View worldSpace_{};
	float bgOffset{ 1600.f };
	lua_State* lua{};
	sf::Clock frameTimer{};
	std::shared_ptr<DynoPlayer> dPlayer;
	std::vector<std::shared_ptr<BaseSprite> > sprites;
	
	// new collision variables
	std::vector<rec> objs;
	//bool playerGrounded{ false };
	//bool jumpPressed{ false };
//	bool playerFacingRight{ true };

	void input();
	void update();
	void render();
	void createWorld();

public:

	Game();
	~Game();
	void run();
};

#endif