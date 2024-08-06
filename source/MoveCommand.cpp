#include <pch.h>
#include "MoveCommand.h"
#include <globals.h>
#include <Projectile.h>
MoveCommand::MoveCommand(Enemy& enemy_, olc::vf2d target_, float completeTime_)
	: Command{ enemy_ }
	, completeTime{completeTime_}
	, timeElapsed{0.f}
	, target{ target_ }
	, path{ {enemy->bbRect().middle().x,enemy->bbRect().middle().y} , {target_.norm()} }
{
}

bool MoveCommand::tick()
{
	if (!done)
	{
		timeElapsed += gTime;

		float  soFar = timeElapsed / completeTime;

		enemy->setPos({ path.origin.x + soFar * path.direction.x * (target.x - path.origin.x), path.origin.y + soFar * path.direction.y * (target.y - path.origin.y) });

		if (soFar >= 1.f)
		{
			soFar = 1.f;
			
			done = true;
		}
	}

	return done;
}