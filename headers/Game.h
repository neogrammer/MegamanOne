#ifndef GAME_H__
#define GAME_H__
#include <ASprite.h>
#include <Player.h>
#include <Stage.h>
#include <SFML/Graphics/View.hpp>
#include<Cfg.h>
#include <SFML/System/Clock.hpp>

struct lua_State;
class Tilemap;

class Game
{
	Tilemap* tmap{};
	ASprite aFace{};
	Player aPlayer{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,50.f},{60.f,77.f} }, { 680.f, -100.f },AnimDirType::Right, true };
	ResolutionDir resDir = ResolutionDir::None;
	Stage stage{ 2 };
	sf::View worldSpace_{};
	float bgOffset{ 1600.f };
	lua_State* lua{};
	sf::Clock frameTimer{};
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