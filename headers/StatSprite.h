#ifndef STATSPRITE_H__
#define STATSPRITE_H__
#include <BaseSprite.h>
class StatSprite : public BaseSprite
{
public:
	StatSprite();
	explicit StatSprite(olc::vf2d pos_ );
	virtual ~StatSprite() override;
	StatSprite(const StatSprite&) = default;
	StatSprite& operator=(const StatSprite&) = default;
	StatSprite(StatSprite&&) = default;
	StatSprite& operator=(StatSprite&&) = default;

	virtual void build(olc::vf2d pos = { 0.f,0.f }) override = 0;

	virtual StatSprite& operator()() override = 0;

	rec& getRec();

};

#endif