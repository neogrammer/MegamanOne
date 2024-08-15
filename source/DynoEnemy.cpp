#include <pch.h>
#include <DynoEnemy.h>

DynoEnemy::DynoEnemy()
	: DynoSprite{}
	, tex{Cfg::Textures::Count}
	, liveBullets{ std::list<std::unique_ptr<SProj>>{} }
	, animElapsed{ 0.f }

{
}

DynoEnemy::DynoEnemy(olc::vf2d pos_)
	: DynoSprite{pos_}
	, tex{ Cfg::Textures::CannonTurtle }
	, liveBullets{ std::list<std::unique_ptr<SProj>>{} }
	, animElapsed{ 0.f }

{
	animMap.clear();
}


sf::IntRect DynoEnemy::getFrame()
{
	auto itr = animMap.find(std::pair(currentAnim, true));
	if (itr == animMap.end()) return { {0,0},{0,0} };
	return itr->second->data.frames.at(itr->second->data.index);
}
void DynoEnemy::resetAnim()
{
	animMap[std::pair(currentAnim, true)]->data.index = 0;
	animElapsed = 0.f;
}

DynoEnemy::~DynoEnemy()
{
}

rec& DynoEnemy::getRec()
{
	return DynoSprite::getRec();
}


