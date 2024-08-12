#include <pch.h>
#include <StatTile.h>

StatTile::StatTile()
	: StatSprite{}
	, texCopy{Cfg::Textures::Count}
	, texRecPosCopy{olc::vi2d{0,0}}
{

}

StatTile::StatTile(Cfg::Textures tex_,olc::vi2d texRecPos_, olc::vf2d pos)
	:  StatSprite{pos}
	, texCopy{tex_}
	, texRecPosCopy{texRecPos_}
{
	build(pos);
}

StatTile::~StatTile()
{

}

void StatTile::setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_)
{
	texCopy = texCopy_;
	texRecPosCopy = texRecPosCopy_;
}

void StatTile::build(olc::vf2d pos)
{
	auto& r = this->getRec();
	r.set(pos, { 50.f,50.f }, texCopy, texRecPosCopy);
}


StatTile& StatTile::operator()()
{
	return *this;
}

rec& StatTile::getRec()
{
	return StatSprite::getRec();
}

void StatTile::render()
{
}

void StatTile::update()
{
}

void StatTile::input()
{
}
