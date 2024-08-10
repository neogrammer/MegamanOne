#ifndef DYNOSPRITE_H__
#define DYNOSPRITE_H__
#include <BaseSprite.h>
class DynoSprite : public BaseSprite
{
public:
	DynoSprite();
	explicit DynoSprite(olc::vf2d pos_);
	virtual ~DynoSprite() override;
	DynoSprite(const DynoSprite&) = default;
	DynoSprite& operator=(const DynoSprite&) = default;
	DynoSprite(DynoSprite&&) = default;
	DynoSprite& operator=(DynoSprite&&) = default;

	virtual void build(olc::vf2d pos = { 0.f,0.f }) override = 0;

	virtual DynoSprite& operator()() override = 0;

	rec& getRec();
};

#endif