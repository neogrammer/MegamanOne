#ifndef DYNOENEMY_H__
#define DYNOENEMY_H__
#include <DynoSprite.h>
#include <Animation.h>
#include <SProj.h>

class DynoEnemy : public DynoSprite
{
protected:
	Cfg::Textures tex;
	std::map<std::pair<std::string, bool>, std::unique_ptr<Animation>> animMap;

	std::list<std::unique_ptr<SProj> > liveBullets;



public:
	std::string currentAnim{ "idle" };
	float animElapsed{ 0.f };
	int life{ 7 };
	int lifeMax{ 7 };

	bool wasHit{ false };
	float hitElapsed{ 0.f };
	float hitDelay{ 0.05f };
	bool alive{ true };
	DynoEnemy();
	DynoEnemy(olc::vf2d pos_);
	virtual ~DynoEnemy() override;

	DynoEnemy(const DynoEnemy&) = default;
	DynoEnemy& operator=(const DynoEnemy&) = default;
	DynoEnemy(DynoEnemy&&) = default;
	DynoEnemy& operator=(DynoEnemy&&) = default;

	sf::IntRect getFrame();
	void resetAnim();
	rec& getRec();
	virtual void build(olc::vf2d pos) override = 0;
	virtual DynoEnemy& operator()() override = 0;
	virtual void input() override = 0;
	virtual void update() override = 0;
	virtual void render() override = 0;

	virtual void hit(int damage_) = 0 ;

};

#endif