#include <pch.h>
#include <Game.h>
#include <Tilemap.h>
#include <type_traits>
#include <string>
#include <duck_fold.h>
#include <fsm_events.h>
#include <BusterProj.h>


void Game::render()
{
	gameStateMgr->render();
}

void Game::input()
{
	gameStateMgr->input();
}

Game::~Game()
{
}

void Game::run()
{
	
	gTime = frameTimer.restart().asSeconds();
	
	
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
			gameStateMgr->processEvent(e);
		}

		// if not closed, update and draw the game as needed
		if (gWnd.isOpen())
		{
			gTime = frameTimer.restart().asSeconds();
			auto num = sf::Mouse::getPosition(gWnd);
			mpos = (sf::Vector2f)num;
		
			//gameStateMgr->input();
			input();

			//gameStateMgr->update();
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
	gameStateMgr->update();
}
Game::Game()
	: gameStateMgr{std::make_unique<GameStateMgr>()}
{
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
	gWnd.setPosition({ 120, 20 });
}
