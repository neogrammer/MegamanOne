#ifndef SNAIL_H__
#define SNAIL_H__

#include <Enemy.h>

class Projectile;

class Snail : public Enemy
{
public:
	Snail();
	~Snail() override = default;
	Snail(const Snail&) = default;
	Snail& operator=(const Snail&) = default;
	Snail(Snail&&) = default;
	Snail& operator=(Snail&&) = default;

	void setup();

	void input() override;
	void update() override;

};

#endif