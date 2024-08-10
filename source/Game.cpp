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

	aPlayer.applyExternalForces();
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

	//tmap->render();
	//stage.render();
	for (auto& p : aPlayer.getProjectiles())
	{
		if (p.isMarkedForDeletion()) continue;
		//p.render();
	}
	//aPlayer.render();
	sf::RectangleShape display;
	display.setSize({ 300.f,200.f });
	display.setFillColor(sf::Color::Black);
	display.setOutlineColor(sf::Color::White);
	display.setOutlineThickness(3);
	display.setPosition({ gameView.getCenter().x - 450.f - 300.f - 10.f, 50.f });

	//gWnd.draw(display);

	sf::Text t1;
	t1.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t1.setCharacterSize(24);
	t1.setFillColor(sf::Color::White);
	t1.setString(std::to_string(aPlayer.getPos().x) + ' ' +  std::to_string(aPlayer.getPos().y));
	t1.setPosition({ gameView.getCenter().x - 450.f - 300.f, 60.f});

	sf::Text t2;
	t2.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t2.setCharacterSize(24);
	t2.setFillColor(sf::Color::White);
	t2.setString(std::to_string(aPlayer.getPrevPos().x) + ' ' + std::to_string(aPlayer.getPrevPos().y));
	t2.setPosition({ gameView.getCenter().x - 450.f - 300.f, 85.f });
	sf::Text t3;
	t3.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t3.setFillColor(sf::Color::White);
	t3.setCharacterSize(24);
	t3.setString(std::to_string(aPlayer.getVelocity().x) + ' ' + std::to_string(aPlayer.getVelocity().y));
	t3.setPosition({ gameView.getCenter().x - 450.f - 300.f, 110.f});
	sf::Text t4;
	t4.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t4.setFillColor(sf::Color::White);
	t4.setString(std::to_string(aPlayer.getPos().x) + ' ' + std::to_string(aPlayer.getPos().y));
	t4.setPosition({ gameView.getCenter().x - 450.f - 300.f, 135.f});
	t4.setCharacterSize(24);
	sf::Text t5;
	t5.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t5.setCharacterSize(24);
	t5.setFillColor(sf::Color::White);
	t5.setString(std::to_string(aPlayer.getPos().x) + ' ' + std::to_string(aPlayer.getPos().y));
	t5.setPosition({ gameView.getCenter().x - 450.f - 300.f, 160.f });
	sf::Text t6;
	t6.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t6.setFillColor(sf::Color::White);
	t6.setCharacterSize(24);
	t6.setString(std::to_string(aPlayer.getPos().x) + ' ' + std::to_string(aPlayer.getPos().y));
	t6.setPosition({ gameView.getCenter().x - 450.f - 300.f,  185.f });
	sf::Text t7;
	t7.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	t7.setFillColor(sf::Color::White);
	t7.setString(std::to_string(aPlayer.getPos().x) + ' ' + std::to_string(aPlayer.getPos().y));
	t7.setPosition({ gameView.getCenter().x - 450.f - 300.f, 210.f });
	t7.setCharacterSize(24);
	//gWnd.draw(t1);
	//gWnd.draw(t2);
	//gWnd.draw(t3);
	//gWnd.draw(t4);
	//gWnd.draw(t5);
	//gWnd.draw(t6);
	//gWnd.draw(t7);




}

void Game::input()
{
	aPlayer.input(gameView, tmap->getSolidTiles());
	/*if (aPlayer.getVelocity().x != 0.f && !aPlayer.isTileBelow(tmap->getSolidTiles()) && !aPlayer.isTileBelow(stage.getPlats()))
	{
		aPlayer.setAffectedByGravity(true);
		aPlayer.setCanJump(false);
	}*/
	stage.input();
}

Game::Game()
	: objs{}
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
	
	objs.clear();
	{
		rec pr;
		pr.set({ 400.f, 400.f }, { 60.f, 83.f }, Cfg::Textures::PlayerAtlas, { 0,1 }, { 130, 160 }, { 32,45 }, {0.f,0.f});
		objs.push_back(pr);
	}

	objs.reserve(static_cast<std::vector<rec, std::allocator<rec>>::size_type>(1) + 30);
	for (int i = 1; i < 20; i++)
	{
		objs.emplace_back(rec{});
		objs[i].set({ ((float)i * 50.f) + 200.f, 900.f - 200.f }, { 50.f,50.f}, Cfg::Textures::Tileset1, { 9,3 }, {50,50 }, { 0,0 }, { 0.f, 0.f });
	}
	for (int i = 20; i < 25; i++)
	{
		objs.emplace_back(rec{});
		objs[i].set({ 200.f + 50.f,  900.f - 200.f - (((i - 20) + 1) * 50.f) }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0,0 }, { 0.f, 0.f });
	}
	for (int i = 25; i < 30; i++)
	{
		objs.emplace_back(rec{});
		objs[i].set({ 200.f + (19.f * 50.f),  900.f - 200.f - (((i - 25) + 1) * 50.f) }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9,3 }, { 50,50 }, { 0,0 }, { 0.f, 0.f });
	}
	

	aPlayer.setPos({ 800.f - (aPlayer.getBBSize().x / 2.f), -100.f});
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

			//input();
			update();

			aRay myRay{{objs[0].pos.x, objs[0].pos.y}, {mpos.x, mpos.y}};
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				objs[0].vel += myRay.dir() * 100.f * gTime;
			}

			olc::vf2d cp;
			olc::vi2d cn;
			float ct;
			std::vector<std::pair<int, float> > z;
			for (int i = 1; i < objs.size(); i++)
			{
				rec target;
				target.set({ objs[i].pos.x, objs[i].pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
				if (phys::DynamicRectVsRect(objs[0], target, cp, cn, ct, gTime))
				{
					z.push_back({ i, ct });
				}
			}
			std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
				{
					return a.second < b.second;
				});

			for (auto j : z)
			{
				rec target;
				target.set({ objs[j.first].pos.x, objs[j.first].pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
				if (phys::DynamicRectVsRect(objs[0], target, cp, cn, ct, gTime))
				{
					objs[0].vel += cn * olc::vf2d{ std::abs(objs[0].vel.x), std::abs(objs[0].vel.y) } *(1 - ct);
				}
			}
			objs[0].pos += objs[0].vel * gTime;

			gWnd.clear(sf::Color(47, 147, 247, 255));

			render();

			for (auto& o : objs)
			{
				if (&o == &objs[0]) continue;
				if (o.pos.x + (o.size.x / 2.f) <= objs[0].pos.x + (objs[0].size.x / 2.f))
					gWnd.draw(*phys::spr(o));
			}

			gWnd.draw(*phys::spr(objs[0]));

			for (auto& o : objs)
			{
				if (&o == &objs[0]) continue;
				if (o.pos.x + (o.size.x / 2.f) > objs[0].pos.x + (objs[0].size.x / 2.f))
					gWnd.draw(*phys::spr(o));
			}




			gWnd.display();
		}

	}
}
