#ifndef STATTILE_H__
#define STATTILE_H__
#include <StatSprite.h>
class StatTile : public StatSprite
{
	Cfg::Textures texCopy;
	olc::vi2d texRecPosCopy;

public:
	StatTile();
	explicit StatTile(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos);

	virtual ~StatTile() override;
	StatTile(const StatTile&) = default;
	StatTile& operator=(const StatTile&) = default;
	StatTile(StatTile&&) = default;
	StatTile& operator=(StatTile&&) = default;

	void setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_);
	void build(olc::vf2d pos = { 0.f,0.f }) override final;
	StatTile& operator()() override final;

	rec& getRec();
};

#endif