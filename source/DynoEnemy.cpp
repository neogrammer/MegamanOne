#include <pch.h>
#include <DynoEnemy.h>

DynoEnemy::DynoEnemy()
	: DynoSprite{}
{
}

DynoEnemy::DynoEnemy(olc::vf2d pos_)
	: DynoSprite{pos_}
{
}

DynoEnemy::~DynoEnemy()
{
}

rec& DynoEnemy::getRec()
{
	return DynoSprite::getRec();
}
