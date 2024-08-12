#ifndef GAME_H__
#define GAME_H__
#include <ASprite.h>
#include <Player.h>
#include <Stage.h>
#include <SFML/Graphics/View.hpp>
#include<rec.h>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <DynoPlayer.h>
#include <StatTile.h>
#include <DynoPlayer.h>

struct lua_State;
class Tilemap;

#include <Snail.h>
#include <Projectile.h>

class Game
{
	Tilemap* tmap{};
	ASprite aFace{};
	Player aPlayer{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,45.f},{60.f,78.f} }, { 680.f, -100.f },AnimDirType::Right, true };
	ResolutionDir resDir = ResolutionDir::None;
	Stage stage{ 2 };
	sf::View worldSpace_{};
	float bgOffset{ 1600.f };
	lua_State* lua{};
	sf::Clock frameTimer{};
	std::shared_ptr<DynoPlayer> dPlayer;
	std::vector<std::shared_ptr<BaseSprite> > sprites;
	
	// new collision variables
	std::vector<rec> objs;
	bool playerGrounded{ false };
	bool jumpPressed{ false };
	bool playerFacingRight{ true };

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