#ifndef DYNOENEMY_H__
#define DYNOENEMY_H__
#include <DynoSprite.h>
class DynoEnemy : public DynoSprite
{
public:
	DynoEnemy();
	DynoEnemy(olc::vf2d pos_);
	virtual ~DynoEnemy() override;

	DynoEnemy(const DynoEnemy&) = default;
	DynoEnemy& operator=(const DynoEnemy&) = default;
	DynoEnemy(DynoEnemy&&) = default;
	DynoEnemy& operator=(DynoEnemy&&) = default;

	rec& getRec();
	virtual void build(olc::vf2d pos) override = 0;
	virtual DynoEnemy& operator()() override = 0;
	virtual void input() override = 0;
	virtual void update() override = 0;
	virtual void render() override = 0;


};

#endif