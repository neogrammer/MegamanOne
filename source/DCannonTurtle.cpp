#include <pch.h>
#include <DCannonTurtle.h>

DCannonTurtle::DCannonTurtle()
{

}

DCannonTurtle::DCannonTurtle(olc::vf2d pos_, int jumpLimit_)
	: DynoEnemy{pos_}
	, waitingToJump{ true }
	, jumpWaitTime{ 4.f }
	, jumpWaitElapsed{ 0.f }
	, jumpLimit{jumpLimit_}
	, jumpCount{ 0 }
{
	build(pos_);

	animMap[std::pair("idle", true)] = std::make_unique<Animation>();
	animMap[std::pair("idle", true)]->data.name = "none";
	animMap[std::pair("idle", true)]->data.fallbackName = "none";
	animMap[std::pair("idle", true)]->data.numFrames = 1;
	animMap[std::pair("idle", true)]->data.index = 0;
	animMap[std::pair("idle", true)]->data.animDelay = 0.3f;
	animMap[std::pair("idle", true)]->data.pauseDelay = 2.f;
	animMap[std::pair("idle", true)]->data.playing = true;
	animMap[std::pair("idle", true)]->data.facingLeft = true;
	animMap[std::pair("idle", true)]->data.onLastFrame = false;
	animMap[std::pair("idle", true)]->data.looping = true;
	animMap[std::pair("idle", true)]->data.repeatTimes = 1;
	animMap[std::pair("idle", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("idle", true)]->data.frames.clear();
	animMap[std::pair("idle", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("idle", true)]->data.bboxes.clear();
	animMap[std::pair("idle", true)]->data.frames.reserve(4);
	animMap[std::pair("idle", true)]->data.bboxes.reserve(4);

	for (int i = 0; i < 1; i++)
	{
		animMap[std::pair("idle", true)]->data.frames.emplace_back(sf::IntRect{{0,0},{96,96}});
		animMap[std::pair("idle", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}

	animMap[std::pair("jump", true)] = std::make_unique<Animation>();
	animMap[std::pair("jump", true)]->data.name = "none";
	animMap[std::pair("jump", true)]->data.fallbackName = "none";
	animMap[std::pair("jump", true)]->data.numFrames = 3;
	animMap[std::pair("jump", true)]->data.index = 0;
	animMap[std::pair("jump", true)]->data.animDelay = 0.2f;
	animMap[std::pair("jump", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("jump", true)]->data.playing = true;
	animMap[std::pair("jump", true)]->data.facingLeft = true;
	animMap[std::pair("jump", true)]->data.onLastFrame = false;
	animMap[std::pair("jump", true)]->data.looping = false;
	animMap[std::pair("jump", true)]->data.repeatTimes = 1;
	animMap[std::pair("jump", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("jump", true)]->data.frames.clear();
	animMap[std::pair("jump", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("jump", true)]->data.bboxes.clear();
	animMap[std::pair("jump", true)]->data.frames.reserve(4);
	animMap[std::pair("jump", true)]->data.bboxes.reserve(4);

	for (int i = 1; i < 4; i++)
	{
		animMap[std::pair("jump", true)]->data.frames.emplace_back(sf::IntRect{ {i*96,0},{96,96} });
		animMap[std::pair("jump", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}

	animMap[std::pair("shoot", true)] = std::make_unique<Animation>();
	animMap[std::pair("shoot", true)]->data.name = "none";
	animMap[std::pair("shoot", true)]->data.fallbackName = "none";
	animMap[std::pair("shoot", true)]->data.numFrames = 5;
	animMap[std::pair("shoot", true)]->data.index = 0;
	animMap[std::pair("shoot", true)]->data.animDelay = 0.3f;
	animMap[std::pair("shoot", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("shoot", true)]->data.playing = true;
	animMap[std::pair("shoot", true)]->data.facingLeft = true;
	animMap[std::pair("shoot", true)]->data.onLastFrame = false;
	animMap[std::pair("shoot", true)]->data.looping = false;
	animMap[std::pair("shoot", true)]->data.repeatTimes = 1;
	animMap[std::pair("shoot", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("shoot", true)]->data.frames.clear();
	animMap[std::pair("shoot", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("shoot", true)]->data.bboxes.clear();

	for (int i = 0; i < 5; i++)
	{
		animMap[std::pair("shoot", true)]->data.frames.emplace_back(sf::IntRect{ {i * 96,96},{96,96} });
		animMap[std::pair("shoot", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}

	animMap[std::pair("idleHit", true)] = std::make_unique<Animation>();
	animMap[std::pair("idleHit", true)]->data.name = "none";
	animMap[std::pair("idleHit", true)]->data.fallbackName = "none";
	animMap[std::pair("idleHit", true)]->data.numFrames = 1;
	animMap[std::pair("idleHit", true)]->data.index = 0;
	animMap[std::pair("idleHit", true)]->data.animDelay = 0.3f;
	animMap[std::pair("idleHit", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("idleHit", true)]->data.playing = true;
	animMap[std::pair("idleHit", true)]->data.facingLeft = true;
	animMap[std::pair("idleHit", true)]->data.onLastFrame = false;
	animMap[std::pair("idleHit", true)]->data.looping = true;
	animMap[std::pair("idleHit", true)]->data.repeatTimes = 1;
	animMap[std::pair("idleHit", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("idleHit", true)]->data.frames.clear();
	animMap[std::pair("idleHit", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("idleHit", true)]->data.bboxes.clear();
	animMap[std::pair("idleHit", true)]->data.frames.reserve(4);
	animMap[std::pair("idleHit", true)]->data.bboxes.reserve(4);

	for (int i = 0; i < 1; i++)
	{
		animMap[std::pair("idleHit", true)]->data.frames.emplace_back(sf::IntRect{ {0,288},{96,96} });
		animMap[std::pair("idleHit", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}

	animMap[std::pair("jumpHit", true)] = std::make_unique<Animation>();
	animMap[std::pair("jumpHit", true)]->data.name = "none";
	animMap[std::pair("jumpHit", true)]->data.fallbackName = "none";
	animMap[std::pair("jumpHit", true)]->data.numFrames = 3;
	animMap[std::pair("jumpHit", true)]->data.index = 0;
	animMap[std::pair("jumpHit", true)]->data.animDelay = 0.2f;
	animMap[std::pair("jumpHit", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("jumpHit", true)]->data.playing = true;
	animMap[std::pair("jumpHit", true)]->data.facingLeft = true;
	animMap[std::pair("jumpHit", true)]->data.onLastFrame = false;
	animMap[std::pair("jumpHit", true)]->data.looping = false;
	animMap[std::pair("jumpHit", true)]->data.repeatTimes = 1;
	animMap[std::pair("jumpHit", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("jumpHit", true)]->data.frames.clear();
	animMap[std::pair("jumpHit", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("jumpHit", true)]->data.bboxes.clear();
	animMap[std::pair("jumpHit", true)]->data.frames.reserve(4);
	animMap[std::pair("jumpHit", true)]->data.bboxes.reserve(4);

	for (int i = 1; i < 4; i++)
	{
		animMap[std::pair("jumpHit", true)]->data.frames.emplace_back(sf::IntRect{ {i * 96,288},{96,96} });
		animMap[std::pair("jumpHit", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}

	animMap[std::pair("shootHit", true)] = std::make_unique<Animation>();
	animMap[std::pair("shootHit", true)]->data.name = "none";
	animMap[std::pair("shootHit", true)]->data.fallbackName = "none";
	animMap[std::pair("shootHit", true)]->data.numFrames = 5;
	animMap[std::pair("shootHit", true)]->data.index = 0;
	animMap[std::pair("shootHit", true)]->data.animDelay = 0.3f;
	animMap[std::pair("shootHit", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("shootHit", true)]->data.playing = true;
	animMap[std::pair("shootHit", true)]->data.facingLeft = true;
	animMap[std::pair("shootHit", true)]->data.onLastFrame = false;
	animMap[std::pair("shootHit", true)]->data.looping = false;
	animMap[std::pair("shootHit", true)]->data.repeatTimes = 1;
	animMap[std::pair("shootHit", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("shootHit", true)]->data.frames.clear();
	animMap[std::pair("shootHit", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("shootHit", true)]->data.bboxes.clear();

	for (int i = 0; i < 5; i++)
	{
		animMap[std::pair("shootHit", true)]->data.frames.emplace_back(sf::IntRect{ {i * 96,96*4},{96,96} });
		animMap[std::pair("shootHit", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
	}
	currentAnim = "idle";
}



DCannonTurtle::~DCannonTurtle()
{

}

void DCannonTurtle::hit(int damage_)
{
	wasHit = true;
	hitElapsed = 0.f;
	life -= damage_;

	if (currentAnim == "idle")
	{
		int idx = animMap[std::pair(currentAnim, true)]->data.index;
		currentAnim = "idleHit";
		animMap[std::pair(currentAnim, true)]->data.index = idx;
	}
	else if (currentAnim == "jump")
	{
		int idx = animMap[std::pair(currentAnim, true)]->data.index;
		currentAnim = "jumpHit";
		animMap[std::pair(currentAnim, true)]->data.index = idx;
	}
	else if (currentAnim == "shoot")
	{
		int idx = animMap[std::pair(currentAnim, true)]->data.index;
		currentAnim = "shootHit";
		animMap[std::pair(currentAnim, true)]->data.index = idx;
	}

	resetAnim();
	if (life <= 0)
	{
		snd::PlayDieSound();
		alive = false;
	}
}

DCannonTurtle& DCannonTurtle::operator()()
{
	return *dynamic_cast<DCannonTurtle*>(this);
}

rec& DCannonTurtle::getRec()
{
	return DynoEnemy::getRec();
}

void DCannonTurtle::build(olc::vf2d pos)
{
	auto& r = this->getRec();
	r.set(pos, { 81.f, 68.f }, Cfg::Textures::CannonTurtle, {0,0}, { 96,96 }, { 10,25 }, { 0.f,0.f });
	this->animElapsed = 0.f;
}

void DCannonTurtle::input()
{
}

void DCannonTurtle::update()
{

	if (jumpCount < jumpLimit)
	{
		if (waitingToJump)
		{
			jumpWaitElapsed += gTime;
			if (jumpWaitElapsed > jumpWaitTime)
			{

				jumpCount += 1;
				waitingToJump = false;
				jumpWaitElapsed = 0.f;
				jumping = true;
				currentAnim = "jump";
				getRec().vel.y = -350.f;
				getRec().vel.x = -150.f;
				startYJump = getRec().pos.y;

				getRec().pos += getRec().vel * gTime;
			}
		}
		else
		{
			if (jumping)
			{
				getRec().vel.y += 600.f * gTime;

				if (getRec().pos.y + getRec().vel.y * gTime >= startYJump)
				{
					getRec().pos.y = startYJump;
					waitingToJump = true;
					jumping = false;
					jumpWaitElapsed = 0.f;
					currentAnim = "idle";
					getRec().vel = { 0.f,0.f };
				}
				else
				{
					getRec().pos += getRec().vel * gTime;
				}
			}
		}
	}



	animElapsed += gTime;
	if (animElapsed >= animMap[std::pair(currentAnim, true)]->data.animDelay)
	{
		animElapsed = 0.f;
		animMap[std::pair(currentAnim, true)]->animate();
	}

	if (wasHit)
	{
		hitElapsed += gTime;
		if (hitElapsed > hitDelay)
		{
			

			wasHit = false;
			if (currentAnim == "idleHit")
			{
				int idx = animMap[std::pair(currentAnim, true)]->data.index;
				currentAnim = "idle";
				animMap[std::pair(currentAnim, true)]->data.index = idx;

			}
			else if (currentAnim == "jumpHit")
			{
				int idx = animMap[std::pair(currentAnim, true)]->data.index;
				currentAnim = "jump";
				animMap[std::pair(currentAnim, true)]->data.index = idx;

			}
			else if (currentAnim == "shootHit")
			{
				int idx = animMap[std::pair(currentAnim, true)]->data.index;
				currentAnim = "shoot";
				animMap[std::pair(currentAnim, true)]->data.index = idx;

			}


		}
	}

}

void DCannonTurtle::render()
{
	if (DynoEnemy::wasHit)
	{
		auto spr = *phys::sprAnim(this->getRec(), this->getFrame(), *this);
		spr.setColor(sf::Color::White);
		gWnd.draw(spr);
	}
	else
	{
		gWnd.draw(*phys::sprAnim(this->getRec(), this->getFrame(), *this));
	}

}
