#include <pch.h>
#include <Game.h>
#include <Tilemap.h>
#include <type_traits>
#include <string>
#include <duck_fold.h>
#include <fsm_events.h>
#include <BusterProj.h>

void Game::createWorld()
{
	
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
	gWnd.setPosition({ 120, 20 });

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
	if (!dPlayer->facingLeft)
	{
		if (gWnd.mapCoordsToPixel({ dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f , dPlayer->getRec().pos.y }).x > 800)
		{
			if (dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f <= 2400.f)
				gameView.setCenter({ dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f , gameView.getCenter().y });
		}
	}
	
	if (dPlayer->facingLeft)
	{
		if (gWnd.mapCoordsToPixel({ dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f , dPlayer->getRec().pos.y }).x < 800)
		{
			if (dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f >= 800.f)
				gameView.setCenter({dPlayer->getRec().pos.x + dPlayer->getRec().size.x / 2.f , gameView.getCenter().y });
		}
	}

	tmap->render();

	//when facing right tiles to the left should be behind megamans back foot
	/*for (auto& o : sprites)
	{
		if (&o->getRec() == &sprites[0]->getRec()) continue;
		gWnd.draw(*phys::spr(o->getRec()));
	}*/

	flypad1.render();
	flypad2.render();
	flypad3.render();
	if (dynamic_cast<DynoEnemy*>(dTurtle.get()) != nullptr)
	{
		if (dynamic_cast<DynoEnemy*>(dTurtle.get())->alive)
		{
			dTurtle->render();
		}
	}

	dPlayer->render();
	


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
	dTurtle->input();
	dPlayer->input();


		//	aPlayer.input(gameView, tmap->getSolidTiles());

//	stage.input();
}

Game::~Game()
{
	delete tmap;
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
	flypad1.update();
	flypad2.update();
	flypad3.update();
	dTurtle->update();
	dPlayer->update();
	dPlayer->handleSpriteCollisions(tmap->getSolidTiles());

	//std::vector<BaseSprite*> sprites = {};
	//sprites.clear();
	
	//dynamic_pointer_cast<DynoEnemy>(

	std::vector<DynoPlat*> plats = {};
	plats.push_back(&flypad1);
	plats.push_back(&flypad2);
	plats.push_back(&flypad3);
	dPlayer->handleSpriteCollisions(plats);
	dPlayer->handleSpriteCollisions(enemies);
	
	std::vector<std::shared_ptr<DynoEnemy> >::iterator iter;
	iter = enemies.begin();
	int count = 0;
	int it = -1;
	for (auto& e : enemies)
	{
		if (!e->alive)
		{
			it = count;
		}
		count++;
	}
	if (it != -1)
	{
		iter = enemies.begin() + it;
		enemies.erase(iter);
	}

	if (dPlayer->standingOnAPlatform && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		if (!dPlayer->isTileBelow(plats))
		{
			dPlayer->standingOnAPlatform = false;
		}
	}

	// platforms let the player ride them otherwise move as normal
	if (dPlayer->standingOnAPlatform == true)
	{

		dPlayer->platVel.x = dPlayer->platOn->getRec().pos.x - dPlayer->platOn->getRec().prevPos.x; //dPlayer->platOn->getRec().vel;
		dPlayer->platVel.y = dPlayer->platOn->getRec().pos.y - dPlayer->platOn->getRec().prevPos.y; //dPlayer->platOn->getRec().vel;
		dPlayer->getRec().vel.x += dPlayer->platOn->getRec().vel.x;
		//dPlayer->getRec().vel.x += dPlayer->platVel.x;
		dPlayer->getRec().vel.y = 0.f;
		dPlayer->getRec().pos.x += dPlayer->getRec().vel.x * gTime;
		dPlayer->getRec().pos.y = dPlayer->platOn->getRec().pos.y - dPlayer->getRec().size.y - 1.f;
	}
	else
	{
		dPlayer->getRec().pos += dPlayer->getRec().vel * gTime;
	}



	bgOffset += 10.f * gTime;
}


Game::Game()
	: objs{}
	, dPlayer{}
	//, sprites{}
	, flypad1{ {400.f,600.f}, {400.f, 200.f} , 200.f}
	, flypad2{ {200.f,860.f}, {200.f, 560.f} , 100.f }
	, flypad3{ {300.f,860.f}, {630.f, 860.f} , 300.f }
	, dTurtle{ std::make_shared<DCannonTurtle>(olc::vf2d{ 1300.f, 850.f - 68.f }, 2) }
	, enemies{}
{

	enemies.clear();
	enemies.shrink_to_fit();
	enemies.push_back(dTurtle);
	std::cout << "Loading..." << std::endl;

	tmap = new Tilemap{ Cfg::Textures::Tileset1, "tileset1", "tilemap1", 1 };

	worldSpace_ = sf::View({ 800.f, 450.f }, { 1600.f,900.f });


	createWorld();


	/*sprites.clear();
	sprites.reserve(31);*/
	dPlayer = std::make_shared<DynoPlayer>(Cfg::Textures::PlayerAtlas, olc::vi2d{ 0,1 }, olc::vf2d{ 400.f, 400.f });
	//sprites.push_back(dPlayer);


	dispatch(dPlayer->fsmHandler->getMachine(), evt_Fell{});
	dPlayer->currentAnim = dPlayer->fsmHandler->getMachine().getCurrentState();
	dPlayer->resetAnim();
	gTime = 0.f;


	//for (int i = 1; i < 20; i++)
	//{
	//	std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ ((float)i * 50.f) + 200.f, 900.f - 200.f });
	//	sprites.push_back(sTile);
	//}
	//for (int i = 20; i < 25; i++)
	//{
	//	std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ 200.f + 50.f,  900.f - 200.f - (((i - 20) + 1) * 50.f) });
	//	sprites.push_back(sTile);
	//}
	//for (int i = 25; i < 30; i++)
	//{
	//	std::shared_ptr<StatTile> sTile = std::make_shared<StatTile>(Cfg::Textures::Tileset1, olc::vi2d{ 9,3 }, olc::vf2d{ 200.f + (19.f * 50.f),  900.f - 200.f - (((i - 25) + 1) * 50.f) });
	//	sprites.push_back(sTile);
	//}

	std::cout << "Load Complete" << std::endl;
	Cfg::music.get((int)Cfg::Music::Stage1).setVolume(40);
	Cfg::music.get((int)Cfg::Music::Stage1).play();
}
