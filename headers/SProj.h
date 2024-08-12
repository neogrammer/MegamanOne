#ifndef DPROJ_H__
#define DPROJ_H__
#include <StatSprite.h>
class SProj : public StatSprite
{

public:
	bool marked{ false };


	SProj();
	SProj(olc::vf2d pos_);

	virtual ~SProj() override;
	virtual void build(olc::vf2d pos) = 0;
	virtual SProj& operator()() override = 0;
	virtual rec& getRec() override;

	virtual void update() override = 0;
	virtual void render() override = 0;
	virtual void input() override = 0;
};

#endif