#include <pch.h>
#include <SProj.h>

SProj::SProj()
	: StatSprite{}
{
}

SProj::SProj(olc::vf2d pos_)
	: StatSprite{pos_}
{
}

SProj::~SProj()
{
}

rec& SProj::getRec()
{
	return StatSprite::getRec();
}

