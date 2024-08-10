#ifndef BASESPRITE_H__
#define BASESPRITE_H__
#include <globals.h>
class BaseSprite
{
	rec rec_{};
public:
	BaseSprite();
	explicit BaseSprite(olc::vf2d pos_);
	virtual ~BaseSprite();
	BaseSprite(const BaseSprite&) = default;
	BaseSprite(BaseSprite&&) = default;
	BaseSprite& operator=(const BaseSprite&) = default;
	BaseSprite& operator=(BaseSprite&&) = default;


	// Builder Function
	virtual void build(olc::vf2d pos = { 0.f,0.f }) = 0;
	virtual BaseSprite& operator()() = 0;
	rec& getRec();

	
};

#endif