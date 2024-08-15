#ifndef DCANNONTURTLE_H__
#define DCANNONTURTLE_H__
#include <DynoEnemy.h>
class DCannonTurtle : public DynoEnemy
{
public:
	
	
	DCannonTurtle();
	explicit DCannonTurtle(olc::vf2d pos_);
	~DCannonTurtle() override;

	DCannonTurtle(const DCannonTurtle&) = default;
	DCannonTurtle& operator=(const DCannonTurtle&) = default;
	DCannonTurtle(DCannonTurtle&&) = default;
	DCannonTurtle& operator=(DCannonTurtle&&) = default;

	rec& getRec();
	void build(olc::vf2d pos) override final;
	DCannonTurtle& operator()() override final;
	void input() override final;
	void update() override final;
	void render() override final;
	void hit(int damage_) override;

};



#endif