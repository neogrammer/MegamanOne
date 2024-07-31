#include <pch.h>
#include <ASprite.h>
#include <Player.h>
#include <Tilemap.h>
using namespace olc::utils::geom2d;

Tilemap* tmap;
ASprite aFace{};
Player aPlayer{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,50.f},{60.f,77.f} }, { 680.f, -100.f },AnimDirType::Right, true };
ResolutionDir resDir = ResolutionDir::None;
ASprite aPlatform{ Cfg::Textures::FlyPad, {{0,0},{67,40}}, {{0.f,0.f},{67.f,20.f}}, SpriteType::Platform, {200.f, 700.f} };

void createWorld();
void updateWorld();
void render();
void input();

sf::Clock frameTimer{};
int main()
{
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

			gWnd.clear(sf::Color(46, 146, 246, 255));
			render();
			gWnd.display();
		}
	}

	delete tmap;

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
}

void render()
{

	tmap->render();
	gWnd.draw(*aPlatform.getSpr());
	aPlayer.render();
}

void input()
{
	aPlayer.input();
	if (aPlayer.getVelocity().x != 0.f &&  !aPlayer.isTileBelow(tmap->getSolidTiles()))
	{ 
		aPlayer.setAffectedByGravity(true); 
		aPlayer.setCanJump(false);
	}
}