#include <pch.h>
#include <ASprite.h>
#include <Player.h>
using namespace olc::utils::geom2d;

std::vector<ASprite> tiles{};
ASprite aFace{};
Player aPlayer{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,50.f},{60.f,77.f} }, { 680.f, -100.f },AnimDirType::Right, true };
ResolutionDir resDir = ResolutionDir::None;

void createTiles();
void createTilemap();
void createWorld();
void updateWorld();
void render();
void input();

sf::Clock frameTimer{};
int main()
{

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
	return EXIT_SUCCESS;
}

void createTiles() 
{
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 730.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 780.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 630.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 580.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 530.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 830.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 480.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 430.f, 400.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 350.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 300.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 250.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 200.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,},  {50.f,50.f } }, { 680.f, 400.f },AnimDirType::Uni, false });

}
void createTilemap()
{
	tiles.clear();
	tiles.reserve(14);
	createTiles();
}
void createWorld()
{
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
	createTilemap();
}

void updateWorld()
{
	aPlayer.update();
	aPlayer.handleMapCollisions(tiles);
}

void render()
{
	for (auto& tile : tiles) { gWnd.draw(*tile.getSpr()); }

	aPlayer.render();
}

void input()
{
	aPlayer.input();
	if (aPlayer.getVelocity().x != 0.f && !aPlayer.isTileBelow(tiles)) { aPlayer.setAffectedByGravity(true); }
}