#ifndef DYNOPLAT_H__
#define DYNOPLAT_H__
#include <DynoSprite.h>

class DynoPlat : public DynoSprite
{
public:
	DynoPlat();
	DynoPlat(olc::vf2d pos_);
	~DynoPlat();

	DynoPlat(const DynoPlat&) = default;
	DynoPlat& operator=(const DynoPlat&) = default;
	DynoPlat(DynoPlat&&) = default;
	DynoPlat& operator=(DynoPlat&&) = default;

	virtual void build(olc::vf2d pos) override = 0;

	virtual DynoPlat& operator()() override = 0;

	virtual rec& getRec() override;
	virtual void render() override = 0;
	virtual void update() override = 0;
	virtual void input() override = 0;
};

#endif