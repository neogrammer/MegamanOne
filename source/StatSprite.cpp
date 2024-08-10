#include <pch.h>
#include <StatSprite.h>

StatSprite::StatSprite()
	: BaseSprite{}
{
}

StatSprite::StatSprite(olc::vf2d pos_)
	: BaseSprite{ pos_ }
{
}

StatSprite::~StatSprite()
{

}



rec& StatSprite::getRec()
{
	return BaseSprite::getRec();
}
