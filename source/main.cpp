#include <pch.h>
#include <ASprite.h>
using namespace olc::utils::geom2d;

std::vector<ASprite> tiles{};
ASprite player{};
ASprite aFace{};
ASprite aTile{};

const int NUM_TILES = 1;
bool RIGHT_HELD = false;
ResolutionDir resDir = ResolutionDir::None;

void createPlayer();
void createTiles();
void createTilemap();
void createWorld();
bool PointVsRect(const olc::vf2d& p, const rect<float>& r);
bool RectVsRect(const rect<float>& r1, const rect<float>& r2);
void RayVsRect();
void DynamicVsRect();
void updatePlayer();
void updateWorld();
void render();
void input();


rect<float> r1;

const int MaxSpeed = 400;
bool LEFT_HELD = false;
bool showFace = false;

sf::Clock frameTimer{};
sf::CircleShape spot{};
int main()
{

	std::cout << "Loading..." << std::endl;
	Cfg::Initialize();
	createWorld();
	std::cout << "Load Complete" << std::endl;

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



			input();
			updateWorld();


			gWnd.clear(sf::Color(46, 146, 246, 255));
			render();
			gWnd.display();

		}
	}
	return EXIT_SUCCESS;
}

void createPlayer() {
	player = ASprite{ Cfg::Textures::PlayerAtlas, {{0,160},{130,160}},{ {32.f,50.f},{60.f,79.f} }, { 680.f, -100.f },AnimDirType::Right, true };
	aFace = ASprite{ Cfg::Textures::China, {{0,0},{130,160}}, {{0.f,0.f},{130.f,160.f}} ,  player.getPos() , AnimDirType::Uni, true };
	player.setVelocity({ 0.0f,0.0f });
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
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 430.f, 350.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 430.f, 300.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 430.f, 250.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 430.f, 200.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 350.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 300.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 250.f },AnimDirType::Uni, false });
	tiles.emplace_back(ASprite{ { Cfg::Textures::Tileset1 }, { {0,0},{50,50} }, { {0,0,}, { 50.f,50.f } }, { 880.f, 200.f },AnimDirType::Uni, false });

}
void createTilemap()
{
	tiles.clear();
	tiles.reserve(17);
	createTiles();
	aTile = ASprite(Cfg::Textures::Tileset1, { {0,0},{50,50} }, { {0,0,},   {50.f,50.f } }, { 680.f, 400.f }, AnimDirType::Uni, true);
	aTile.setVelocity({ 0.f,0.f });
}
void createWorld()
{

	wndw::CreateWindow("MegamanOne", 1600U, 900U);

	createTilemap();
	createPlayer();

	r1 = { {680.f,500.f},{50.f,50.f} };

	spot.setRadius(3.f);
	spot.setOrigin({ 3.f,3.f });
	spot.setFillColor(sf::Color::Red);
	spot.setPosition({ -6.f,-6.f });

}
bool PointVsRect(const olc::vf2d& p, const rect<float>& r) {
	return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}
bool RectVsRect(const rect<float>& r1, const rect<float>& r2) {
	return (r1.pos.x <  r2.right().start.x && r1.right().start.x > r2.pos.x &&
		r1.pos.y <  r2.bottom().start.y && r1.bottom().start.y > r2.pos.y);
}
void DynamicVsRect() {}
void updatePlayer() {}
void updateWorld() {

	// HOUSEKEEPING
	std::vector<olc::vf2d> aVec;
	aVec.clear();

	//GAME LOGIC


	//PHYSICS SYSTEM
	// update all the members for each object instance of a class in play, just save the getSpr() calling until after collisions   ( update - collision Detect - collision Resolve - update positions after all calculations)
	// collision detection here
	if (player.isAffectedByGravity())
	{
		player.applyGravity(28.f);
	}

	resDir = ResolutionDir::None;
	if (RectVsRect(aTile.bbRect(), player.bbRect()))
	{
		aVec = intersects(aTile.bbRect(), player.bbRect());

		if (aVec.size() > 0)
		{
			int num{ 0 };
			for (int i = 0; i < aVec.size(); i++)
			{
				if (player.prevOverlapIsX(aTile)) 
				{
					// this is the point we want to shoot a ray through
					// resolve on the y
					num = i;

					if (player.getVelocity().y < 0.f)
					{
						// collision happened above
						std::cout << "Collision happened above" << std::endl;
						resDir = ResolutionDir::Down;
						break;
					}
					else if(player.getVelocity().y > 0.f)
					{
						// collision happened below
						
						std::cout << "Collision happened below need to push up " << std::endl;
						resDir = ResolutionDir::Up;
						break;

					}
				}
				else	if (player.prevOverlapIsY(aTile)) 
				{
					// this is the point we want to shoot a ray through
					// resolve on the x
					num = i;

					if (player.getVelocity().x < 0.f)
					{
						// collision happened on the left side
						std::cout << "Collision happened on the left" << std::endl;
						resDir = ResolutionDir::Right;
						break;
					}
					else if(player.getVelocity().x > 0.f)
					{
						// collision happened on the right side
						std::cout << "Collision happened on the right" << std::endl;
						resDir = ResolutionDir::Left;
						break;
					}
				}
			}
			spot.setPosition({ aVec[0].x, aVec[0].y });
			std::cout << "Player sprite position: x = " << player.getPos().x - player.getBBOffset().x << " , y = " << player.getPos().y - player.getBBOffset().y << "\n";
			std::cout << "position of player bounding box:  x = " << player.getPos().x << " , y = " << player.getPos().y << " ... and\n";
			std::cout << "position of collision point:  x = " << aVec[0].x << " , y = " << aVec[0].y << std::endl;
			//std::cout << "position of spot collision point:  x = " << spot.getPosition().x - spot.getOrigin().x << " , y = " << spot.getPosition().y - spot.getOrigin().y << std::endl;


			//player.getActualCollisionPt({ spot.getPosition().x,spot.getPosition().y }).x
			//std::cout << "collided x at: " << (spot.getPosition().x - player.getPos().x) << "and collided y at: " << player.getActualCollisionPt({ spot.getPosition().x,spot.getPosition().y }).y << " as the first collision point recorded" << std::endl;
			showFace = true;
			if (resDir == ResolutionDir::Up)
			{
				player.setPos({ player.getPos().x,  aTile.getPos().y - player.getBBSize().y - 0.1f });
				player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
				player.setAffectedByGravity(false);
				//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
				//player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
			}
			else if (resDir == ResolutionDir::Down)
			{
				player.setPos({ player.getPos().x,  aTile.getPos().y + aTile.getBBSize().y + 0.1f });
				player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
				//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
				//player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
			}
			else if (resDir == ResolutionDir::Left)
			{
				player.setPos({ aTile.getPos().x - player.getBBSize().x - 0.1f , player.getPos().y });
				player.setVelocity({ aTile.getVelocity().x, player.getVelocity().y });

				//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
				//player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
			}
			else if (resDir == ResolutionDir::Right)
			{
				player.setPos({ aTile.getPos().x + aTile.getBBSize().x + 0.1f,  player.getPos().y });
				player.setVelocity({ aTile.getVelocity().x, player.getVelocity().y });

				//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
				//player.setVelocity({ player.getVelocity().x, aTile.getVelocity().y });
			}
		}
	
	}
	else
	{

		for (auto& tile : tiles)
		{
			//if (resDir != ResolutionDir::None) break;
			if (RectVsRect(tile.bbRect(), player.bbRect()))
			{
				aVec = intersects(tile.bbRect(), player.bbRect());
				if (aVec.size() > 0)
				{
					int num{ 0 };
					for (int i = 0; i < aVec.size(); i++)
					{
						if (player.prevOverlapIsX(tile))
						{
							// this is the point we want to shoot a ray through
							// resolve on the y
							num = i;

							if (player.getVelocity().y < 0.f)
							{
								// collision happened above
								std::cout << "Collision happened above" << std::endl;
								resDir = ResolutionDir::Down;
								break;
							}
							else if (player.getVelocity().y > 0.f)
							{
								// collision happened below

								std::cout << "Collision happened below need to push up " << std::endl;
								resDir = ResolutionDir::Up;
								break;

							}
						}
						else if (player.prevOverlapIsY(tile))
						{
							// this is the point we want to shoot a ray through
							// resolve on the x
							num = i;

							if (player.getVelocity().x < 0.f)
							{
								// collision happened on the left side
								std::cout << "Collision happened on the left" << std::endl;
								resDir = ResolutionDir::Right;
								break;
							}
							else if (player.getVelocity().x > 0.f)
							{
								// collision happened on the right side
								std::cout << "Collision happened on the right" << std::endl;
								resDir = ResolutionDir::Left;
								break;
							}
						}
					}
					spot.setPosition({ aVec[0].x, aVec[0].y });
					std::cout << "Player sprite position: x = " << player.getPos().x - player.getBBOffset().x << " , y = " << player.getPos().y - player.getBBOffset().y << "\n";
					std::cout << "position of player bounding box:  x = " << player.getPos().x << " , y = " << player.getPos().y << " ... and\n";
					std::cout << "position of collision point:  x = " << aVec[0].x << " , y = " << aVec[0].y << std::endl;
					//std::cout << "position of spot collision point:  x = " << spot.getPosition().x - spot.getOrigin().x << " , y = " << spot.getPosition().y - spot.getOrigin().y << std::endl;


					//player.getActualCollisionPt({ spot.getPosition().x,spot.getPosition().y }).x
					//std::cout << "collided x at: " << (spot.getPosition().x - player.getPos().x) << "and collided y at: " << player.getActualCollisionPt({ spot.getPosition().x,spot.getPosition().y }).y << " as the first collision point recorded" << std::endl;
					showFace = true;
					if (resDir == ResolutionDir::Up)
					{
						player.setPos({ player.getPos().x,  tile.getPos().y - player.getBBSize().y - 0.1f });
						player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
						player.setAffectedByGravity(false);
						//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
						//player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
					}
					else if (resDir == ResolutionDir::Down)
					{
						player.setPos({ player.getPos().x,  tile.getPos().y + tile.getBBSize().y + 0.1f});
						player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
						//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
						//player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
					}
					else if (resDir == ResolutionDir::Left)
					{
						player.setPos({ tile.getPos().x - player.getBBSize().x - 0.1f , player.getPos().y});
						player.setVelocity({ tile.getVelocity().x, player.getVelocity().y });

						//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
						//player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
					}
					else if (resDir == ResolutionDir::Right)
					{
						player.setPos({ tile.getPos().x + tile.getBBSize().x + 0.1f,  player.getPos().y });
						player.setVelocity({ tile.getVelocity().x, player.getVelocity().y });

						//player.setPos({ player.getPos().x - (player.getPos().y - player.getPrevPos().y) - 0.1f, player.getPos().y - (player.getPos().y - player.getPrevPos().y) - 0.1f });
						//player.setVelocity({ player.getVelocity().x, tile.getVelocity().y });
					}

				}

			}
		}

		showFace = false;
	}

	// collision resolution here
	if (aVec.size() > 0)
	{
		if (resDir == ResolutionDir::Up)
		{
			//	auto disp = player.getPos().y + player.getBBox().getSize().y - aTile.getPos().y;
			auto plum = aTile.getPos().y - player.getBBSize().y - 0.1f;
		}
		//player.setVelocity({ player.getVelocity().x, plum });
	}

	// update actual positions now, once only
	player.tickMovement();
	aTile.tickMovement();
}

void render() {
	for (auto& tile : tiles)
	{
		gWnd.draw(*tile.getSpr());
	}
	gWnd.draw(*mk::Spr(Cfg::Textures::Tileset1, { aTile.getPos().x, aTile.getPos().y}, {{0,0},{50,50}}));
	if (showFace)
	{
		aFace.setPos(player.getPos());
		gWnd.draw(*aFace.getSpr());
	}
	else
	{
		player.render();
		//gWnd.draw(*player.getSpr());
	}

	gWnd.draw(spot);

	sf::CircleShape shp{ 3.f };
	shp.setPosition({spot.getPosition()});
	shp.setFillColor(sf::Color::Red);
	shp.setOrigin({ 3.f,3.f });

	gWnd.draw(shp);
}

void input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!RIGHT_HELD)
		{
			// first moment of push

		}

		RIGHT_HELD = true;

		//player.setVelocity({ player.getVelocity().x + 40.f, player.getVelocity().y });
		
		if (player.getVelocity().x <= MaxSpeed)
		{
			player.setVelocity({ player.getVelocity().x + 450 * gTime, player.getVelocity().y });
			//nowFacingRight
		}
	}
	else
	{
		RIGHT_HELD = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!LEFT_HELD)
		{
			// first moment of push

		}

		LEFT_HELD = true;

		//player.setVelocity({ player.getVelocity().x - 40.f, player.getVelocity().y });

		if (player.getVelocity().x >= -MaxSpeed)
		{
			player.setVelocity({ player.getVelocity().x - 450 * gTime, player.getVelocity().y });
			//nowFacingLeft
		}
	}
	else
	{

		LEFT_HELD = false;
	}


}