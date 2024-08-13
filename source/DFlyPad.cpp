#include <pch.h>
#include <DFlyPad.h>

DFlyPad::DFlyPad()
	: DynoPlat{}
	, anim{}
	, pathStart{0.f,0.f}
	, pathEnd{ 0.f,0.f }
	, speed{ 0.f }
{

}

DFlyPad::DFlyPad(olc::vf2d pos_, olc::vf2d pathEnd_, float speed_)
	: DynoPlat{ pos_ }
	, anim{}
	, pathStart{pos_}
	, pathEnd{pathEnd_}
	, speed{speed_}
{
	build(pos_);
}


DFlyPad::~DFlyPad()
{

}


void DFlyPad::build(olc::vf2d pos)
{
	auto& r = this->getRec();
	r.set(pos, { 67.f, 20.f }, Cfg::Textures::FlyPad, { 0,0 }, { 67,40 }, { 0,0 }, { 0.f,0.f });
	animElapsed = 0.f;
	auto& f = anim.data.frames;
	auto& b = anim.data.bboxes;
	f = std::vector<sf::IntRect>{};
	b = std::vector<sf::FloatRect>{};

	f.clear();
	b.clear();
	f.reserve(3);
	b.reserve(3);

	for (int i = 0; i < 3; i++)
	{
		f.emplace_back(sf::IntRect{ {i*67,0},{67,40} });
		b.emplace_back(sf::FloatRect{ {0.f,0.f},{67.f,20.f} });
	}
	anim.data.animDelay = 0.13f;
	anim.data.facingLeft = true;
	anim.data.index = 0;
	anim.data.looping = true;
	anim.data.numFrames = 3;
	anim.data.onLastFrame = false;
	anim.data.playing = true;

	r.setTexRect(0,0);

}

sf::IntRect DFlyPad::getFrame()
{
	return anim.data.frames[anim.data.index];
}

rec& DFlyPad::getRec()
{
	return DynoPlat::getRec();
}

DFlyPad& DFlyPad::operator()()
{
	return *dynamic_cast<DFlyPad*>(this);
}

void DFlyPad::render()
{
	gWnd.draw(*phys::sprAnim(getRec(), getFrame(), *this));
}
void DFlyPad::update()
{
	animElapsed += gTime;
	if (animElapsed >= anim.data.animDelay)
	{
		animElapsed = 0.f;
		anim.animate();
	}

	if (toEnd)
	{
		auto vectorToEnd = pathEnd - pathStart;
		auto vN = vectorToEnd.norm();
		getRec().vel.x = vN.x * speed;
		getRec().vel.y = vN.y * speed;

		if (pathEnd.x > pathStart.x && vN.y == 0)
		{
			if (getRec().pos.x >= pathEnd.x)
			{
				toEnd = false;
			}
		}
		else if (pathEnd.x < pathStart.x && vN.y == 0)
		{
			if (getRec().pos.x <= pathEnd.x)
			{
				toEnd = false;
			}
		}
		else if (pathEnd.y > pathStart.y && vN.x == 0)
		{
			if (getRec().pos.y >= pathEnd.y)
			{
				toEnd = false;
			}
		}
		else if (pathEnd.y < pathStart.y && vN.x == 0)
		{
			if (getRec().pos.y <= pathEnd.y)
			{
				toEnd = false;
			}
		}

		
	}
	else
	{
		auto vectorToStart = pathStart - pathEnd;
		auto vN = vectorToStart.norm();
		getRec().vel.x = vN.x * speed;
		getRec().vel.y = vN.y * speed;


		if (pathStart.x > pathEnd.x && vN.y == 0)
		{
			if (getRec().pos.x >= pathStart.x)
			{
				toEnd = true;
			}
		}
		else if (pathStart.x < pathEnd.x && vN.y == 0)
		{
			if (getRec().pos.x <= pathStart.x)
			{
				toEnd = true;
			}
		}
		else if (pathStart.y > pathEnd.y && vN.x == 0)
		{
			if (getRec().pos.y >= pathStart.y)
			{
				toEnd = true;
			}
		}
		else if (pathStart.y < pathEnd.y && vN.x == 0)
		{
			if (getRec().pos.y <= pathStart.y)
			{
				toEnd = true;
			}
		}
	}

	getRec().pos += getRec().vel * gTime;

}
void DFlyPad::input()
{}


