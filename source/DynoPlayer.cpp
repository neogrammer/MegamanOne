#include <pch.h>
#include <DynoPlayer.h>

DynoPlayer::DynoPlayer()
	: DynoSprite{}
	, texCopy{ Cfg::Textures::Count }
	, texRecPosCopy{ olc::vi2d{0,0} }
{
}

DynoPlayer::DynoPlayer(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos)
	: DynoSprite{pos}
	, texCopy{ tex_ }
	, texRecPosCopy{ texRecPos_ }
{
	build(pos);
}

DynoPlayer::~DynoPlayer()
{

}


void DynoPlayer::setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_)
{
	texCopy = texCopy_;
	texRecPosCopy = texRecPosCopy_;
}

void DynoPlayer::build(olc::vf2d pos)
{
	auto& r = this->getRec();
	r.set(pos, { 60.f, 84.f }, texCopy, texRecPosCopy, { 130,160 }, { 32,45 }, {0.f,0.f});
}

DynoPlayer& DynoPlayer::operator()()
{
	return *this;
}

rec& DynoPlayer::getRec()
{
	return DynoSprite::getRec();
}
