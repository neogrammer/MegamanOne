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

	virtual void build(olc::vf2d pos) override = 0;

	virtual DynoSprite& operator()() override = 0;

	virtual rec& getRec() override;
	virtual void render() override = 0;
	virtual void update() override = 0;
	virtual void input() override = 0;

};

#endif