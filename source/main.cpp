#include <pch.h>
#include <Dynamic.h>
using namespace olc::utils::geom2d;
//
//sf::Vector2f playerPos{};
//sf::Vector2f playerImgOrigin{};
//sf::Vector2f playerVel{};
//sf::IntRect playerRect{};
//sf::IntRect playerBBox{};

struct Tile
{
	float left;
	float top;
	float width;
	float height;
	sf::IntRect texRect;
	Cfg::Textures texType;
};
//
//sf::Vector2f getPlayerImgSize()
//{
//	return { (float)playerRect.width,(float)playerRect.height };
//}
//
//sf::Vector2f getPlayerImgHSize()
//{
//	return { (float)playerRect.width / 2.f,(float)playerRect.height / 2.f };
//}
//
//
//sf::Vector2f getPlayerBBoxSize()
//{
//	return { (float)playerBBox.width,(float)playerBBox.height };
//}
//
//sf::Vector2f getPlayerBBoxHalfSize()
//{
//	return { (float)playerBBox.width / 2.f,(float)playerBBox.height / 2.f };
//}
//
//sf::FloatRect getPlayerAABB()
//{
//	sf::FloatRect tmp{};
//	tmp.left = playerPos.x;
//	tmp.top = playerPos.y;
//	tmp.left += (float)playerBBox.left;
//	tmp.top += (float)playerBBox.top;
//	tmp.width = (float)playerBBox.width;
//	tmp.height = (float)playerBBox.height;
//
//	return tmp;
//}
//
//sf::Vector2f getPlayerAABBCenter()
//{
//	sf::FloatRect tmp = getPlayerAABB();
//	sf::Vector2f position{};
//	position.x = tmp.left + getPlayerBBoxHalfSize().x;
//	position.y = tmp.top + getPlayerBBoxHalfSize().y;
//
//	return position;
//}
//
//void setPlayer(sf::Vector2f pos_, sf::Vector2f orig_, sf::IntRect texRect_, sf::IntRect bboxRect_, sf::Vector2f vel_)
//{
//	playerPos = pos_;
//	playerImgOrigin = orig_;
//	playerRect = texRect_;
//	playerBBox = bboxRect_;
//	playerVel = vel_;
//}
//
//void applyVelocity()
//{
//	playerPos.x += playerVel.x * gTime;
//	playerPos.y += playerVel.y * gTime;
//}
//
//
//void setPos(sf::Vector2f pos_)
//{
//	playerPos.x = pos_.x;
//	playerPos.y = pos_.y;
//}
//
//
//void move(sf::Vector2f pos_)
//{
//	playerPos.x += pos_.x * gTime;
//	playerPos.y += pos_.y * gTime;
//}
//
//
//void setVelocity(sf::Vector2f vel_)
//{
//	playerVel.x = vel_.x;
//	playerVel.y = vel_.y;
//}
//
//void accelerate(sf::Vector2f acc_)
//{
//	playerVel.x += acc_.x * gTime;
//	playerVel.y += acc_.y * gTime;
//}
//
//void applyGravity()
//{
//	playerVel.y += 986.6667f * gTime;
//}
void setupTile(Tile& tile_, float x_, float y_, int left_, int top_, int w_, int h_, Cfg::Textures texType_)
{
	tile_.left = x_;
	tile_.top = y_;
	tile_.texType = texType_;
	tile_.width = (float)w_;
	tile_.height = (float)h_;
	tile_.texRect = { {left_,top_},{w_,h_} };
}

int main(int argc, char* argv[])
{
	std::cout << "Loading..." << std::endl;

	Cfg::Initialize();

	std::cout << "Load Complete" << std::endl;
	wndw::CreateWindow("MegamanOne", 1600U, 900U);

	Dynamic player{};
	player.setup(Cfg::Textures::PlayerAtlas, { (float)765.f, (float)240.f }, { 0.f,0.f }, { {0,160},{130,160} }, { {65,45}, {21,80} }, { 0.f,0.f });
	Tile tile{};
	setupTile(tile, 800.f, 680.f, 0, 0, 50, 50, Cfg::Textures::Tileset1);

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

		mpos = sf::Mouse::getPosition(gWnd);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player.pos = { (float)mpos.x, (float)mpos.y };

		}

		gTime = frameTimer.restart().asSeconds();

		player.applyGravity();

		bool isContained = contains(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(olc::v_2d((float)tile.left, (float)tile.top), olc::v_2d((float)tile.width, tile.height)));
		bool isOverlapping = overlaps(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(olc::v_2d((float)tile.left, (float)tile.top), olc::v_2d((float)tile.width, tile.height)));
		std::vector<olc::v_2d<float>> pts;
		pts.clear();
		if (isOverlapping)
		{
			pts = intersects(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(olc::v_2d((float)tile.left, (float)tile.top), olc::v_2d((float)tile.width, tile.height)));
		}


		
		sf::FloatRect plRect = player.getAABB();
		sf::Vector2f plCenter{};
		plCenter.x = plRect.left + (plRect.width / 2.f);
		plCenter.y = plRect.top + (plRect.height / 2.f);

		sf::FloatRect plNextRect = plRect;
		plNextRect.left += player.vel.x * gTime;
		plNextRect.top += player.vel.y * gTime;
		sf::FloatRect plBroadRect{};
		plBroadRect.left = (plRect.left < plNextRect.left) ? plRect.left : plNextRect.left;
		plBroadRect.top = (plRect.top < plNextRect.top) ? plRect.top : plNextRect.top;
		plBroadRect.width = plRect.width + abs(plNextRect.left - plRect.left);
		plBroadRect.height = plRect.height + abs(plNextRect.top - plRect.top);

		olc::v_2d plRectPos = olc::v_2d(plRect.getPosition().x, plRect.getPosition().y);
		olc::v_2d plRectSize = olc::v_2d(plRect.getSize().x, plRect.getSize().y);

		olc::v_2d plNRectPos = olc::v_2d(plNextRect.getPosition().x, plNextRect.getPosition().y);
		olc::v_2d plNRectSize = olc::v_2d(plNextRect.getSize().x, plNextRect.getSize().y);

		olc::v_2d plBRectPos = olc::v_2d(plBroadRect.getPosition().x, plBroadRect.getPosition().y);
		olc::v_2d plBRectSize = olc::v_2d(plBroadRect.getSize().x, plBroadRect.getSize().y);

		bool broadCheckPlayer = false;
		std::vector<olc::v_2d<float>> bPlayerPts;
		bPlayerPts.clear();
		if (overlaps(rect<float>(plBRectPos, plBRectSize), rect<float>(olc::v_2d((float)tile.left, (float)tile.top), olc::v_2d((float)tile.width, tile.height))))
		{
			broadCheckPlayer = true;
			bPlayerPts = intersects(rect<float>(plBRectPos, plBRectSize), rect<float>(olc::v_2d((float)tile.left, (float)tile.top), olc::v_2d((float)tile.width, tile.height)));


		}

		bool narrowCheckPlayer = false;
		
		if (broadCheckPlayer == true)
		{
			bool wasOnX = false;
			bool wasOnY = false;

			if (plRect.left < tile.left + tile.width && plRect.left + plRect.width > tile.left)
			{
				// was overlapping on the x axis prior to collision
				wasOnX = true;
			}

			if (plRect.top < tile.top + tile.height && plRect.top + plRect.height > tile.top)
			{
				// was overlapping on the y axis prior to collision
				wasOnY = true;
			}

			auto closePt = closest(rect<float>(olc::v_2d((float)tile.left - (plRectSize.x / 2.f), (float)tile.top - (plRectSize.y / 2.f)), olc::v_2d((float)tile.width + plRectSize.x, (float)tile.height + plRectSize.y)), olc::v_2d{ plCenter.x, plCenter.y });
			player.pos.x = closePt.x - player.bbox.left - player.getBBoxHSize().x;
			player.pos.y = closePt.y - player.bbox.top - player.getBBoxHSize().y;

			// calculate normal and only stop the correct velocity based on which way hit
			if (wasOnX == true && wasOnY == false)
			{
				player.vel.y = 0.f;
			}
			else if (wasOnY == true && wasOnX == false)
			{
				player.vel.y = 0.f;
			}
			else if (wasOnY == false && wasOnX == false)
			{
				// both on false
				player.vel.y = 0.f;
				player.vel.y = 0.f;
			}
			else
			{
				std::cout << "This should not be displaying, wasOnX == true, and wasOnY == true as if there was already a collision that did not get resolved" << std::endl;
			}
		}



		player.applyVelocity();
		
		
		bool isPlayerContained = contains(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(plRectPos, plRectSize));
		bool isPlayerOverlapping = overlaps(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(plRectPos, plRectSize));

		std::vector<olc::v_2d<float>> nPlayerPts;
		nPlayerPts.clear();
		if (isPlayerOverlapping)
		{
			nPlayerPts = intersects(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(plRectPos, plRectSize));
		}


			gWnd.clear(sf::Color::Blue);
			drw::CirS(sf::Vector2f(mpos), 200.f, (isPlayerContained) ? sf::Color::Black : sf::Color::White);
			auto t1 = mk::Spr(tile.texType, { tile.left,tile.top }, { {tile.texRect.left,tile.texRect.top},{tile.texRect.width,tile.texRect.height} });
			gWnd.draw(*t1);

			auto p = player.spr();
			gWnd.draw(*p);

			for (auto& pt : pts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}
		
			for (auto& pt: bPlayerPts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}

			for (auto& pt : nPlayerPts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}

			gWnd.display();
		}
	}
	return EXIT_SUCCESS;
}