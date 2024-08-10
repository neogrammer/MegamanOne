#ifndef DYNOSPRITE_H__
#define DYNOSPRITE_H__
#include <BaseSprite.h>
class DynoSprite : public BaseSprite
{
public:
	DynoSprite();
	virtual ~DynoSprite() override;
	DynoSprite(const DynoSprite&) = delete;
	DynoSprite& operator=(const DynoSprite&) = delete;
	DynoSprite(DynoSprite&&) = delete;
	DynoSprite& operator=(DynoSprite&&) = delete;

};

#endif