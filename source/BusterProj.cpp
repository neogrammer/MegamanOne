#include <pch.h>
#include <BusterProj.h>

BusterProj::BusterProj()
	: SProj{ {0.f,0.f} }
	, dirStr{}
{
}

BusterProj& BusterProj::operator()()
{
	return *this;
}

BusterProj::BusterProj(olc::vf2d pos_, bool leftDir_)
	: SProj{pos_}
	, dirStr{}
{
	if (leftDir_)
	{
		dirStr = "left";
	}
	else
	{
		dirStr = "right";
	}
	build(pos_);
}

BusterProj::~BusterProj()
{
}

void BusterProj::build(olc::vf2d pos_)
{
	auto& r = this->getRec();
	r.set(pos_, { 24.f, 18.f }, Cfg::Textures::BusterBullet, { 0, 0 }, { 24, 18 });
	
	if (dirStr == "right")
	{
		getRec().vel.x = 500.f;
	}
	else
	{
		getRec().vel.x = -500.f;
	}
}

void BusterProj::update()
{
	if (dirStr == "right")
	{
		getRec().vel.x = 500.f;
	}
	else
	{
		getRec().vel.x = -500.f;
	}

	getRec().pos += getRec().vel * gTime;
}

void BusterProj::render()
{
	gWnd.draw(*phys::spr(getRec()));
}

void BusterProj::input()
{
}

rec& BusterProj::getRec()
{
	return StatSprite::getRec();
}

