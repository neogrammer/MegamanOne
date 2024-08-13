#include <pch.h>
#include <DynoPlat.h>

DynoPlat::DynoPlat()
	: DynoSprite{}
{
}

DynoPlat::DynoPlat(olc::vf2d pos_)
	: DynoSprite{ pos_ }
{

}


DynoPlat::~DynoPlat()
{

}


rec& DynoPlat::getRec()
{
	return DynoSprite::getRec();
}




