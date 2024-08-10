#ifndef STATSPRITE_H__
#define STATSPRITE_H__
#include <BaseSprite.h>
class StatSprite : public BaseSprite
{
public:
	StatSprite();
	virtual ~StatSprite() override;
	StatSprite(const StatSprite&) = delete;
	StatSprite& operator=(const StatSprite&) = delete;
	StatSprite(StatSprite&&) = delete;
	StatSprite& operator=(StatSprite&&) = delete;
};

#endif