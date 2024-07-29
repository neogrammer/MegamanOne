#include <pch.h>
#include <ASprite.h>

std::vector<ASprite> tiles{};
ASprite player{};

void createPlayer();
void createTile();
void createTilemap();
void createWorld();
void PointVsRect();
void RectVsRect();
void RayVsRect();
void DynamicVsRect();
void updatePlayer();
void updateWorld();
void render();
void input();


using namespace olc::utils::geom2d;

int main()
{

	std::cout << "Loading..." << std::endl;
	Cfg::Initialize();
	createWorld();
	std::cout << "Load Complete" << std::endl;
	wndw::CreateWindow("MegamanOne", 1600U, 900U);

	sf::Vector2i mpos;
	sf::Clock frameTimer{};

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
			mpos = sf::Mouse::getPosition(gWnd);
			input();
			updateWorld();

			mpos = sf::Mouse::getPosition(gWnd);
			gTime = frameTimer.restart().asSeconds();

			gWnd.clear(sf::Color::Blue);
			render();
			gWnd.display();
		}
	}

	return EXIT_SUCCESS;
}

void createPlayer() {}
void createTile() {}
void createTilemap() {}
void createWorld() {}
void PointVsRect(){}
void RectVsRect() {}
void RayVsRect() {}
void DynamicVsRect() {}
void updatePlayer() {}
void updateWorld() {}
void render() {}
void input() {}