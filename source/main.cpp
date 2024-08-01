#include <pch.h>
#include <ASprite.h>
#include <Player.h>
#include <Tilemap.h>
#include <Stage.h>
using namespace olc::utils::geom2d;

Tilemap* tmap;
ASprite aFace{};
Player aPlayer{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,50.f},{60.f,77.f} }, { 680.f, -100.f },AnimDirType::Right, true };
ResolutionDir resDir = ResolutionDir::None;
Stage stage{ 1 };
void createWorld();
void updateWorld();
void render();
void input();

sf::Clock frameTimer{};
int main()
{
	lua_State* lua;
	lua = luaL_newstate();
	luaL_openlibs(lua);
	
	/*sol::state_view L{ lua };
	L.open_libraries(sol::lib::base, sol::lib::bit32, sol::lib::coroutine, sol::lib::debug, sol::lib::ffi, sol::lib::io, sol::lib::jit, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
	L.safe_script_file("assets/scripts/StageSetup.lua");
	L["LoadPlatforms"](&stage, 1);*/

	lua_register(lua, "cpp_moveObject", Stage::lua_moveObject);
	lua_register(lua, "cpp_createPlatform", Stage::lua_createPlatform);
	if (scr::CheckLua(lua, luaL_dofile(lua, "assets/scripts/StageSetup.lua")))
	{
		lua_getglobal(lua, "LoadPlatforms");
		if (lua_isfunction(lua, -1))
		{
			lua_pushlightuserdata(lua, &stage);
			lua_pushnumber(lua, 1);
			if (!scr::CheckLua(lua, lua_pcall(lua, 2, 0, 0)))
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	
	
	tmap = new Tilemap{ Cfg::Textures::Tileset1, "tileset1", "tilemap1", 1 };

	std::cout << "Loading..." << std::endl;
	Cfg::Initialize();
	createWorld();

	std::cout << "Load Complete" << std::endl;
	aPlayer.setPos({ 680.f, -100.f });
	aPlayer.setVelocity({ 0.f, 0.f });
	frameTimer.restart();
	while (gWnd.isOpen())
	{
		sf::Event e;
		while (gWnd.pollEvent(e))
		{
			if ((e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) || e.type == sf::Event::Closed)
			{
				gWnd.close();
			}
		}
		if (gWnd.isOpen())
		{
			gTime = frameTimer.restart().asSeconds();
			auto num = sf::Mouse::getPosition(gWnd);
			mpos = (sf::Vector2f)num;

			input();
			updateWorld();
			stage.update(lua);
			gWnd.clear(sf::Color(46, 146, 246, 255));
			render();
			gWnd.display();
		}

	}


	delete tmap;
	
	lua_close(lua);

	return EXIT_SUCCESS;
}


void createWorld()
{
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
}

void updateWorld()
{
	aPlayer.update();
	aPlayer.handleMapCollisions(tmap->getSolidTiles());
	aPlayer.handleMapCollisions(stage.getPlats());

	
	
}

void render()
{

	tmap->render();
	stage.render();
	aPlayer.render();
}

void input()
{

	aPlayer.input();
	if (aPlayer.getVelocity().x != 0.f &&  !aPlayer.isTileBelow(tmap->getSolidTiles()) && !aPlayer.isTileBelow(stage.getPlats()))
	{ 
		aPlayer.setAffectedByGravity(true); 
		aPlayer.setCanJump(false);
	}

	stage.input();

}