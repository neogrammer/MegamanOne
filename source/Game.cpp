#include <pch.h>
#include <Game.h>
#include <Tilemap.h>
#include <Snail.h>
#include <type_traits>
#include <string>
#include <duck_fold.h>
#include <fsm_events.h>

void Game::createWorld()
{
	
	wndw::CreateWindow("MegamanOne", 1600U, 900U);

}


void Game::render()
{
	gWnd.setView(gWnd.getDefaultView());
	sf::Sprite bg{};
	bg.setTexture(Cfg::textures.get((int)Cfg::Textures::BGSpace));
	bg.move({ bgOffset,0.f });

	auto currLeft = gameView.getCenter().x - 800.f;

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
				bgOffset = 0;
				bg.setPosition({ currLeft, 0.f });
			}
		}
	}
	gWnd.setView(gameView);


	//when facing right tiles to the left should be behind megamans back foot
	for (auto& o : sprites)
	{
		if (&o->getRec() == &sprites[0]->getRec()) continue;
		gWnd.draw(*phys::spr(o->getRec()));
	}

	gWnd.draw(*phys::sprAnim(dPlayer->getRec(), dPlayer->getFrame(), *this->dPlayer));

	//tmap->render();
	//stage.render();
	//for (auto& p : aPlayer.getProjectiles())
	//{
	//	if (p.isMarkedForDeletion()) continue;
	//	//p.render();
	//}
	//aPlayer.render();


}

void Game::input()
{

	dPlayer->input();


		//	aPlayer.input(gameView, tmap->getSolidTiles());

//	stage.input();
}

Game::~Game()
{
	delete tmap;
	lua_close(lua);
}

void Game::run()
{
	

	
	frameTimer.restart();

	
	// game loop
	while (gWnd.isOpen())
	{

		// window events handled here
		sf::Event e;
		while (gWnd.pollEvent(e))
		{
			if ((e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) || e.type == sf::Event::Closed)
			{
				gWnd.close();
			}
		}

		// if not closed, update and draw the game as needed
		if (gWnd.isOpen())
		{
			gTime = frameTimer.restart().asSeconds();
			auto num = sf::Mouse::getPosition(gWnd);
			mpos = (sf::Vector2f)num;
		
			input();

			update();
			
			// now render the screen
			gWnd.clear(sf::Color(47, 147, 247, 255));
			render();
			gWnd.display();
		}

	}
}

void Game::update()
{
	dPlayer->update();
	dPlayer->handleSpriteCollisions(sprites);


	dPlayer->getRec().pos += dPlayer->getRec().vel * gTime;


	bgOffset += 10.f * gTime;
}


Game::Game()
	: objs{}
	, dPlayer{}
	, sprites{}
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


	sprites.clear();
	sprites.reserve(31);
	dPlayer = std::make_shared<DynoPlayer>(Cfg::Textures::PlayerAtlas, olc::vi2d{ 0,1 }, olc::vf2d{ 400.f, 400.f });
	sprites.push_back(dPlayer);


	dispatch(dPlayer->fsmHandler->getMachine(), evt_Fell{});
	dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
	dPlayer->resetAnim();
	gTime = 0.f;


	for (int i = 1; i < 20; i++)
	{
		std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ ((float)i * 50.f) + 200.f, 900.f - 200.f });
		sprites.push_back(sTile);
	}
	for (int i = 20; i < 25; i++)
	{
		std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ 200.f + 50.f,  900.f - 200.f - (((i - 20) + 1) * 50.f) });
		sprites.push_back(sTile);
	}
	for (int i = 25; i < 30; i++)
	{
		std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ 200.f + (19.f * 50.f),  900.f - 200.f - (((i - 25) + 1) * 50.f) });
		sprites.push_back(sTile);
	}

	std::cout << "Load Complete" << std::endl;

}
