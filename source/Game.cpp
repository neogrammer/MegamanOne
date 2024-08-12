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

void Game::update()
{
	//stage.update(lua);

	//aPlayer.applyExternalForces();
	//aPlayer.update();
	//aPlayer.handleMapCollisions(tmap->getSolidTiles());
	//aPlayer.handleMapCollisions(stage.getPlats());

	//aPlayer.tickMovement();

	//std::vector<ASprite*> sprites{};
	//sprites.emplace_back(new ASprite{});
	//ASprite& aSpr = *sprites[0];

	//sprites[0] = nullptr;

	//for (auto& p : aPlayer.getProjectiles())
	//{
	//	p.updateCheckHandle(aPlayer, sprites, tmap->getSolidTiles());
	//}
	//sprites[0] = &aSpr;

	//delete sprites[0];

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
	//for (auto& p : aPlayer.getProjectiles())
	//{
	//	if (p.isMarkedForDeletion()) continue;
	//	//p.render();
	//}
	//aPlayer.render();
	/*sf::RectangleShape display;
	display.setSize({ 300.f,200.f });
	display.setFillColor(sf::Color::Black);
	display.setOutlineColor(sf::Color::White);
	display.setOutlineThickness(3);
	display.setPosition({ gameView.getCenter().x - 450.f - 300.f - 10.f, 50.f });*/

	//gWnd.draw(display);

	/*sf::Text t1;
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
	t7.setCharacterSize(24);*/
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprites[0]->getRec().vel.x = -250.f;
		playerFacingRight = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprites[0]->getRec().vel.x = 250.f;
		playerFacingRight = true;

	}

	if (playerGrounded == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			dispatch(dPlayer->fsmHandler->getMachine(), evt_Jumped{});
			dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();

			playerGrounded = false;
			sprites[0]->getRec().vel.y = -2000.f;
			if (playerFacingRight)
				sprites[0]->getRec().vel.x = -40000.f;
			else
				sprites[0]->getRec().vel.x = 40000.f;

			
		}
	}



		//	aPlayer.input(gameView, tmap->getSolidTiles());

//	stage.input();
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

Game::~Game()
{
	delete tmap;
	lua_close(lua);
}

void Game::run()
{
	

	
	frameTimer.restart();

	dispatch(dPlayer->fsmHandler->getMachine(), evt_Fell{});
	dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
	dPlayer->resetAnim();
	gTime = 0.f;

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

			//input();
			// add keybased updates to playere here
			sprites[0]->getRec().vel.x = 0.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				sprites[0]->getRec().vel.x += 300.f;
				dPlayer->facingLeft = false;
				if (dPlayer->currentAnim != "startingRun" && dPlayer->currentAnim != "running" && dPlayer->currentAnim != "landing" && dPlayer->currentAnim != "peakingJump" && dPlayer->currentAnim != "jumping" && dPlayer->currentAnim != "falling")
				{
					dispatch(dPlayer->fsmHandler->getMachine(), evt_StartedMoving{});
					
						dPlayer->fsmHandler->getMachine().setJustChanged(false);
						dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
						dPlayer->resetAnim();
					
					
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sprites[0]->getRec().vel.x -= 300.f;
				dPlayer->facingLeft = true;
				if (dPlayer->currentAnim != "startingRun" && dPlayer->currentAnim != "running" && dPlayer->currentAnim != "landing" && dPlayer->currentAnim != "peakingJump" && dPlayer->currentAnim != "jumping" && dPlayer->currentAnim != "falling")
				{
					dispatch(dPlayer->fsmHandler->getMachine(), evt_StartedMoving{});
					
						dPlayer->fsmHandler->getMachine().setJustChanged(false);
						dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
						dPlayer->resetAnim();
					
				}
			}
			
			if (sprites[0]->getRec().vel.x == 0.f && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				dispatch(dPlayer->fsmHandler->getMachine(), evt_StoppedMoving{});
				if (dPlayer->fsmHandler->getMachine().wasJustChanged())
				{
					dPlayer->fsmHandler->getMachine().setJustChanged(false);
					dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
					dPlayer->resetAnim();
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				jumpPressed = true;
				if (playerGrounded == true && sprites[0]->getRec().vel.y == 0.f)
				{
					dispatch(dPlayer->fsmHandler->getMachine(), evt_Jumped{});
					dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
					dPlayer->resetAnim();

					playerGrounded = false;
					sprites[0]->getRec().vel.y = -1208.81f;
				}
			}
			else
			{
				jumpPressed = false;
			}

			
			
			dPlayer->update();


			//gravity
			sprites[0]->getRec().vel.y += powf(59.8f,2) * gTime;
			


			//aRay myRay{ {sprites[0]->getRec().pos.x, sprites[0]->getRec().pos.y }, {sprites[0]->getRec().pos.x + sprites[0]->getRec().vel.x, sprites[0]->getRec().pos.y + sprites[0]->getRec().vel.y}};
			//sprites[0]->getRec().vel += myRay.dir() * 250.f * gTime;

			//aRay myRay{{objs[0].pos.x, objs[0].pos.y}, {mpos.x, mpos.y}};
			/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sprites[0]->getRec().vel += myRay.dir() * 100.f * gTime;
			}*/
			// add gravity here

			// check collisions
			olc::vf2d cp;
			olc::vi2d cn;
			float ct;

			std::vector<std::pair<int, float> > z;
			for (int i = 1; i < sprites.size(); i++)
			{
				rec target;
				target.set({ sprites[i]->getRec().pos.x, sprites[i]->getRec().pos.y}, {50.f,50.f}, Cfg::Textures::Tileset1, {9, 3}, {50,50}, {0, 0}, {0.f,0.f});
				if (phys::DynamicRectVsRect(sprites[0]->getRec(), target, cp, cn, ct, gTime))
				{
					if (cn.y == -1 && dPlayer->getRec().vel.y > 10.f && dPlayer->currentAnim != "running" && dPlayer->currentAnim != "peakingJump")
					{
						dispatch(dPlayer->fsmHandler->getMachine(), evt_Landed{});
						dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
						dPlayer->resetAnim();
						playerGrounded = true;
					}
					z.push_back({ i, ct });

				}
			}

			// sort
			std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
				{
					return a.second < b.second;
				});


			// resolve in correct order
			for (auto j : z)
			{
				rec target;
				target.set({sprites[j.first]->getRec().pos.x, sprites[j.first]->getRec().pos.y}, {50.f,50.f}, Cfg::Textures::Tileset1, {9, 3}, {50,50}, {0, 0}, {0.f,0.f});
				if (phys::DynamicRectVsRect(sprites[0]->getRec(), target, cp, cn, ct, gTime))
				{
					sprites[0]->getRec().vel += cn * olc::vf2d{ std::abs(sprites[0]->getRec().vel.x), std::abs(sprites[0]->getRec().vel.y) } *(1 - ct);
				}
			}

			// finally update the position of the player
			sprites[0]->getRec().pos += sprites[0]->getRec().vel * gTime;


			// now render the screen
			gWnd.clear(sf::Color(47, 147, 247, 255));

			render();

			//when facing right tiles to the left should be behind megamans back foot
			for (auto& o : sprites)
			{
				if (&o->getRec() == &sprites[0]->getRec()) continue;
				if (o->getRec().pos.x + (o->getRec().size.x / 2.f) <= sprites[0]->getRec().pos.x + (sprites[0]->getRec().size.x / 2.f))
					gWnd.draw(*phys::spr(o->getRec()));
			}

			

			// tiles in front get overlaid his front foot
			for (auto& o : sprites)
			{
				if (&o->getRec() == &sprites[0]->getRec()) continue;
				if (o->getRec().pos.x + (o->getRec().size.x / 2.f) > sprites[0]->getRec().pos.x + (sprites[0]->getRec().size.x / 2.f))
					gWnd.draw(*phys::spr(o->getRec()));
			}

			gWnd.draw(*phys::sprAnim(dPlayer->getRec(), dPlayer->getFrame(), *this->dPlayer));


			gWnd.display();
		}

	}
}
