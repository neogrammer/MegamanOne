#include <pch.h>
#include <Game.h>
#include <Tilemap.h>
#include <Snail.h>

void Game::createWorld()
{
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
}

void Game::update()
{
	stage.update(lua);

	aPlayer.update();
	aPlayer.handleMapCollisions(tmap->getSolidTiles());
	aPlayer.handleMapCollisions(stage.getPlats());
	aPlayer.tickMovement();

	std::vector<ASprite*> sprites{};
	sprites.emplace_back(new ASprite{});
	ASprite& aSpr = *sprites[0];

	sprites[0] = nullptr;

	for (auto& p : aPlayer.getProjectiles())
	{
		p.updateCheckHandle(aPlayer, sprites, tmap->getSolidTiles());
	}
	sprites[0] = &aSpr;

	delete sprites[0];

	bgOffset += 10.f * gTime;


}

void Game::render()
{
	gWnd.setView(worldSpace_);
	sf::Sprite bg{};
	bg.setTexture(Cfg::textures.get((int)Cfg::Textures::BGSpace));
	bg.move({ bgOffset,0.f });

	auto currLeft = worldSpace_.getCenter().x - 800.f;
	if (bgOffset >= currLeft)
	{
		//create another background size.x to the left of the bgOffset
		sf::Sprite bgLeft{};
		bgLeft.setTexture(Cfg::textures.get((int)Cfg::Textures::BGSpace));
		bgLeft.setPosition({ bgOffset - bgLeft.getTexture()->getSize().x, 0.f });

		gWnd.draw(bgLeft);
		if (bgLeft.getPosition().x >= currLeft)
		{
			sf::Sprite bgLeftLeft{};
			bgLeftLeft.setTexture(Cfg::textures.get((int)Cfg::Textures::BGSpace));
			bgLeftLeft.setPosition({ bgLeft.getPosition().x - bgLeft.getTexture()->getSize().x, 0.0f });
			gWnd.draw(bgLeftLeft);
			if (bgLeftLeft.getPosition().x >= currLeft)
			{
				bgOffset = 0.0f;
				bg.setPosition({ currLeft, 0.f });

			}

		}
	}
	tmap->render();
	stage.render();
	for (auto& p : aPlayer.getProjectiles())
	{
		if (p.isMarkedForDeletion()) continue;

		p.render();
	}
	aPlayer.render();
}

void Game::input()
{
	aPlayer.input();
	if (aPlayer.getVelocity().x != 0.f && !aPlayer.isTileBelow(tmap->getSolidTiles()) && !aPlayer.isTileBelow(stage.getPlats()))
	{
		aPlayer.setAffectedByGravity(true);
		aPlayer.setCanJump(false);
	}
	stage.input();
}

Game::Game()
{
	std::cout << "Loading..." << std::endl;

	lua = luaL_newstate();
	luaL_openlibs(lua);

	tmap = new Tilemap{ Cfg::Textures::Tileset1, "tileset1", "tilemap1", 1 };

	worldSpace_ = sf::View({ 800.f, 450.f }, { 1600.f,900.f });


	lua_register(lua, "cpp_retry", Stage::lua_retry);

	lua_register(lua, "cpp_moveObject", Stage::lua_moveObject);
	lua_register(lua, "cpp_moveObjectUp", Stage::lua_moveObjectUp);

	lua_register(lua, "cpp_createPlatform", Stage::lua_createPlatform);
	if (scr::CheckLua(lua, luaL_dofile(lua, "assets/scripts/StageSetup.lua")))
	{
		lua_getglobal(lua, "LoadPlatforms");
		if (lua_isfunction(lua, -1))
		{
			lua_pushlightuserdata(lua, &stage);
			lua_pushnumber(lua, 1);
			if (!scr::CheckLua(lua, lua_pcall(lua, 2, 0, 0))) {
				throw std::runtime_error("Nope, Bad Lua");
			}
		}
		else
		{
			throw std::runtime_error("Nope, Bad Lua");
		}
	}
	else
	{
		throw std::runtime_error("Nope, Bad Lua");

	}

	createWorld();
	std::cout << "Load Complete" << std::endl;
}

Game::~Game()
{
	delete tmap;
	lua_close(lua);
}

void Game::run()
{
	
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
			update();
			
			gWnd.clear(sf::Color(47, 147, 247, 255));
			render();
			gWnd.display();
		}

	}





}
