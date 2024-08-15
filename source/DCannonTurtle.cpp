#include <pch.h>
#include <DCannonTurtle.h>

DCannonTurtle::DCannonTurtle()
{

}

DCannonTurtle::DCannonTurtle(olc::vf2d pos_)
	: DynoEnemy{pos_}
{
	build(pos_);

	animMap[std::pair("idle", true)] = std::make_unique<Animation>();
	animMap[std::pair("idle", true)]->data.name = "none";
	animMap[std::pair("idle", true)]->data.fallbackName = "none";
	animMap[std::pair("idle", true)]->data.numFrames = 4;
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

	for (int i = 0; i < 4; i++)
	{
		animMap[std::pair("idle", true)]->data.frames.emplace_back(sf::IntRect{{i * 96,0},{96,96}});
		animMap[std::pair("idle", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
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
	animMap[std::pair("idleHit", true)]->data.numFrames = 4;
	animMap[std::pair("idleHit", true)]->data.index = 0;
	animMap[std::pair("idleHit", true)]->data.animDelay = 0.3f;
	animMap[std::pair("idleHit", true)]->data.pauseDelay = 0.f;
	animMap[std::pair("idleHit", true)]->data.playing = true;
	animMap[std::pair("idleHit", true)]->data.facingLeft = true;
	animMap[std::pair("idleHit", true)]->data.onLastFrame = false;
	animMap[std::pair("idleHit", true)]->data.looping = false;
	animMap[std::pair("idleHit", true)]->data.repeatTimes = 1;
	animMap[std::pair("idleHit", true)]->data.frames = std::vector<sf::IntRect>{};
	animMap[std::pair("idleHit", true)]->data.frames.clear();
	animMap[std::pair("idleHit", true)]->data.bboxes = std::vector<sf::FloatRect>{};
	animMap[std::pair("idleHit", true)]->data.bboxes.clear();

	for (int i = 0; i < 4; i++)
	{
		animMap[std::pair("idleHit", true)]->data.frames.emplace_back(sf::IntRect{ {i * 96,96*3},{96,96} });
		animMap[std::pair("idleHit", true)]->data.bboxes.emplace_back(sf::FloatRect{ {10.f,25.f},{81.f,68.f} });
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
	life -= damage_;
	currentAnim = "idleHit";
	resetAnim();
	getRec().texRectPos = { animMap[std::pair(currentAnim, true)]->data.frames[animMap[std::pair(currentAnim, true)]->getIndex()].left, animMap[std::pair(currentAnim, true)]->data.frames[animMap[std::pair(currentAnim, true)]->getIndex()].top };
	if (life <= 0)
	{
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
	animElapsed += gTime;
	if (animElapsed >= animMap[std::pair(currentAnim, true)]->data.animDelay)
	{
		animElapsed = 0.f;
		animMap[std::pair(currentAnim, true)]->animate();
	}

}

void DCannonTurtle::render()
{
	if (DynoEnemy::wasHit)
	{
		auto spr = *phys::sprAnim(this->getRec(), this->getFrame(), *this);
		spr.setColor(sf::Color::White);
		gWnd.draw(spr);
		DynoEnemy::wasHit = false;
	}
	else
	{
		gWnd.draw(*phys::spr(this->getRec()));
	}

}
