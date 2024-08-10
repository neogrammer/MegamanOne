#include <pch.h>
#include <BaseSprite.h>

BaseSprite::BaseSprite()
	: rec_{ rec{} }
{
}

BaseSprite::BaseSprite(olc::vf2d pos_)
	: rec_{ rec{} }
{
}

BaseSprite::~BaseSprite()
{}



rec& BaseSprite::getRec()
{
	return rec_;
}


