#ifndef DYNOPLAYER_H__
#define DYNOPLAYER_H__
#include <DynoSprite.h>
class DynoPlayer : public DynoSprite
{
	Cfg::Textures texCopy;
	olc::vi2d texRecPosCopy;

public:
	DynoPlayer();
	explicit DynoPlayer(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos);

	virtual ~DynoPlayer() override;
	DynoPlayer(const DynoPlayer&) = default;
	DynoPlayer& operator=(const DynoPlayer&) = default;
	DynoPlayer(DynoPlayer&&) = default;
	DynoPlayer& operator=(DynoPlayer&&) = default;
	void setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_);
	void build(olc::vf2d pos = { 0.f,0.f }) override final;

	DynoPlayer& operator()() override final;

	rec& getRec();

};

#endif