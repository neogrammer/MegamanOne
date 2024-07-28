#include <pch.h>

using namespace olc::utils::geom2d;

sf::Vector2f playerPos{};
sf::Vector2f playerImgOrigin{};
sf::Vector2f playerVel{};
sf::IntRect playerRect{};
sf::IntRect playerBBox{};

sf::Vector2f getPlayerImgSize()
{
	return { (float)playerRect.width,(float)playerRect.height };
}

sf::Vector2f getPlayerImgHSize()
{
	return { (float)playerRect.width / 2.f,(float)playerRect.height / 2.f };
}


sf::Vector2f getPlayerBBoxSize()
{
	return { (float)playerBBox.width,(float)playerBBox.height };
}

sf::Vector2f getPlayerBBoxHalfSize()
{
	return { (float)playerBBox.width / 2.f,(float)playerBBox.height / 2.f };
}

sf::FloatRect getPlayerAABB()
{
	sf::FloatRect tmp{};
	tmp.left = playerPos.x;
	tmp.top = playerPos.y;
	tmp.left += (float)playerBBox.left;
	tmp.top += (float)playerBBox.top;
	tmp.width = (float)playerBBox.width;
	tmp.height = (float)playerBBox.height;

	return tmp;
}

sf::Vector2f getPlayerAABBCenter()
{
	sf::FloatRect tmp = getPlayerAABB();
	sf::Vector2f position{};
	position.x = tmp.left + getPlayerBBoxHalfSize().x;
	position.y = tmp.top + getPlayerBBoxHalfSize().y;

	return position;
}

void setPlayer(sf::Vector2f pos_, sf::Vector2f orig_, sf::IntRect texRect_, sf::IntRect bboxRect_, sf::Vector2f vel_)
{
	playerPos = pos_;
	playerImgOrigin = orig_;
	playerRect = texRect_;
	playerBBox = bboxRect_;
	playerVel = vel_;
}

void applyVelocity()
{
	playerPos.x += playerVel.x * gTime;
	playerPos.y += playerVel.y * gTime;
}


void setPos(sf::Vector2f pos_)
{
	playerPos.x = pos_.x;
	playerPos.y = pos_.y;
}


void move(sf::Vector2f pos_)
{
	playerPos.x += pos_.x * gTime;
	playerPos.y += pos_.y * gTime;
}


void setVelocity(sf::Vector2f vel_)
{
	playerVel.x = vel_.x;
	playerVel.y = vel_.y;
}

void accelerate(sf::Vector2f acc_)
{
	playerVel.x += acc_.x * gTime;
	playerVel.y += acc_.y * gTime;
}

void applyGravity()
{
	playerVel.y += 986.6667f * gTime;
}


int main(int argc, char* argv[])
{
	std::cout << "Loading..." << std::endl;

	Cfg::Initialize();

	std::cout << "Load Complete" << std::endl;
	wndw::CreateWindow("MegamanOne", 1600U, 900U);

	setPlayer({ (float)765.f, (float)240.f }, { 0.f,0.f }, { {0,160},{130,160} }, { {65,45}, {21,80} }, { 0.f,0.f });

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
			playerPos.x = (float)mpos.x;
			playerPos.y = (float)mpos.y;
		}

		gTime = frameTimer.restart().asSeconds();

		applyGravity();


		bool isContained = contains(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 100.f), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d( 50.f, 50.f)));
		bool isOverlapping = overlaps(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 100.f), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d(50.f, 50.f)));


		sf::FloatRect pRect = getPlayerAABB();
		sf::Vector2f pCenter{};
		pCenter.x = pRect.left + (pRect.width / 2.f);
		pCenter.y = pRect.top + (pRect.height / 2.f);

		sf::FloatRect pNextRect = pRect;
		pNextRect.left += playerVel.x *gTime;
		pNextRect.top += playerVel.y *gTime;
		sf::FloatRect broadRect{};
		broadRect.left = (pRect.left < pNextRect.left) ? pRect.left : pNextRect.left ;
		broadRect.top = (pRect.top < pNextRect.top) ? pRect.top : pNextRect.top;
		broadRect.width = pRect.width + abs(pNextRect.left - pRect.left);
		broadRect.height = pRect.height + abs(pNextRect.top - pRect.top);

		olc::v_2d pRectPos = olc::v_2d(pRect.getPosition().x, pRect.getPosition().y);
		olc::v_2d pRectSize = olc::v_2d(pRect.getSize().x, pRect.getSize().y);

		olc::v_2d nRectPos = olc::v_2d(pNextRect.getPosition().x, pNextRect.getPosition().y);
		olc::v_2d nRectSize = olc::v_2d(pNextRect.getSize().x, pNextRect.getSize().y);

		olc::v_2d pBRectPos = olc::v_2d(broadRect.getPosition().x, broadRect.getPosition().y);
		olc::v_2d pBRectSize = olc::v_2d(broadRect.getSize().x, broadRect.getSize().y);

		bool isPlayerContained = contains(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(pRectPos, pRectSize));
		bool isPlayerOverlapping = overlaps(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(pRectPos, pRectSize));

		bool isPlayerCollidingTile = overlaps(rect<float>(pRectPos, pRectSize), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d(50.f, 50.f)));

		bool broadCheck = false;
		std::vector<olc::v_2d<float>> bPts;
		bPts.clear();
		if (overlaps(rect<float>(pBRectPos, pBRectSize), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d(50.f, 50.f))))
		{
			broadCheck = true;		
			bPts = intersects(rect<float>(pBRectPos, pBRectSize), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d(50.f, 50.f)));
		
			
		}

		bool narrowCheck = false;
		std::vector<olc::v_2d<float>> nPts;
		nPts.clear();
		if (broadCheck == true)
		{

			int normx{ 0 };
			int normy{ 0 };

			bool wasOnX = false;
			bool wasOnY = false;

			if (pRect.left < 850.f && pRect.left + pRect.width > 800.f)
			{
				// was overlapping on the x axis prior to collision
				wasOnX = true;
			}

			if (pRect.top < 730.f && pRect.top + pRect.height > 680.f)
			{
				// was overlapping on the y axis prior to collision
				wasOnY = true;
			}

			auto closePt = closest(rect<float>(olc::v_2d((float)800.f - (pRectSize.x / 2.f), (float)680.f - (pRectSize.y / 2.f)), olc::v_2d(50.f + pRectSize.x, 50.f + pRectSize.y)), olc::v_2d{ pCenter.x, pCenter.y });
			playerPos.x = closePt.x - playerBBox.left - getPlayerBBoxHalfSize().x;
			playerPos.y = closePt.y - playerBBox.top - getPlayerBBoxHalfSize().y;
			
			// calculate normal and only stop the correct velocity based on which way hit
			if (wasOnX == true && wasOnY == false)
			{
				playerVel.y = 0.f;
			}
			else if (wasOnY == true && wasOnX == false)
			{
				playerVel.y = 0.f;
			}
			else if (wasOnY == false && wasOnX == false)
			{
				// both on false
				playerVel.y = 0.f;
				playerVel.y = 0.f;
			}
			else
			{
				std::cout << "This should not be displaying, wasOnX == true, and wasOnY == true as if there was already a collision that did not get resolved" << std::endl;
			}
		}

		std::vector<olc::v_2d<float>> pts;
		pts.clear();
		if (isOverlapping)
		{
			pts = intersects(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(olc::v_2d((float)800.f, (float)680.f), olc::v_2d(50.f, 50.f)));
		}
		std::vector<olc::v_2d<float>> playerPts;
		playerPts.clear();
		if (isPlayerOverlapping)
		{
			playerPts = intersects(circle<float>({ olc::v_2d(mpos.x, mpos.y) }, 200.f), rect<float>(pRectPos,pRectSize));
		}

		applyVelocity();
		
	

			gWnd.clear(sf::Color::Blue);

			auto p1 = mk::Spr(Cfg::Textures::PlayerAtlas, playerPos, playerRect);
			gWnd.draw(*p1);
			for (auto& pt : playerPts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}

			drw::CirS(sf::Vector2f(mpos), 200.f, (isPlayerContained) ? sf::Color::Black : sf::Color::White);
			drw::RectS({ (float)800,(float)680 }, { 50.f, 50.f }, (isContained) ? sf::Color::Red : sf::Color::White);

			for (auto& pt : pts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}
		
			for (auto& pt: bPts)
			{
				drw::CirF({ pt.x, pt.y }, 10.f, sf::Color::Green);
			}

			gWnd.display();
		}
	}
	return EXIT_SUCCESS;
}