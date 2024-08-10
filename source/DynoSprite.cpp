#include <pch.h>
#include <DynoSprite.h>

DynoSprite::DynoSprite()
	: BaseSprite{}
{
}

DynoSprite::DynoSprite(olc::vf2d pos_)
	: BaseSprite{pos_}
{
}

DynoSprite::~DynoSprite()
{

}


rec& DynoSprite::getRec()
{
	return BaseSprite::getRec();
}

