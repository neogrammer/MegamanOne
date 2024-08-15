#ifndef DCANNONTURTLE_H__
#define DCANNONTURTLE_H__
#include <DynoEnemy.h>
class DCannonTurtle : public DynoEnemy
{
public:
	bool waitingToJump{ true };
	float jumpWaitTime{ 4.f };
	float jumpWaitElapsed{ 0.f };
	bool jumping{ false };
	float startYJump{ 0.f };
	int jumpLimit{ 0 };
	int jumpCount{ 0 };
	
	DCannonTurtle();
	explicit DCannonTurtle(olc::vf2d pos_, int jumpLimit_);
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