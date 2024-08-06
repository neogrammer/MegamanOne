#include <pch.h>
#include <Enemy.h>
#include <Projectile.h>
#include <MoveCommand.h>
#include "Snail.h"

Snail::Snail()
	: Enemy{ Cfg::Textures::SnailEnemy, { {0,0},{70,46} }, { {15.f,16.f},{20.f,30.f} }, SpriteType::Enemy, { 1300.f, 900.f - 50.f - 30.f }, AnimDirType::Left, false }
{

	this->currentAnim = "idle";
	this->facingLeft = false;
	// right animations
	this->animMap.emplace(std::pair{ "walk", false }, AnimData2{});
	this->animMap[std::pair("walk", false)].numFrames = loadAnimation(this->animMap[std::pair("walk", false)].frames, 8, 8, 0, 1, 0);
	this->animMap[std::pair("walk", false)].animDelay = 0.3f;
	this->animMap[std::pair("walk", false)].pauseDelay = 0.f;
	// left animations
	this->animMap.emplace(std::pair{ "walk", true }, AnimData2{});
	this->animMap[std::pair("walk", true)].numFrames = loadAnimation(this->animMap[std::pair("walk", true)].frames, 8, 8, 0, 0, 0);
	this->animMap[std::pair("walk", true)].animDelay = 0.3f;
	this->animMap[std::pair("walk", true)].pauseDelay = 0.f;

	this->animMap.emplace(std::pair{ "hide", false }, AnimData2{});
	this->animMap[std::pair("hide", false)].numFrames = loadAnimation(this->animMap[std::pair("hide", false)].frames, 8, 8, 0, 6, 0);
	this->animMap[std::pair("hide", false)].animDelay = 0.1f;
	this->animMap[std::pair("hide", false)].pauseDelay = 0.f;
	this->animMap[std::pair("hide", false)].looping = false;

	// left animations
	this->animMap.emplace(std::pair{ "hide", true }, AnimData2{});
	this->animMap[std::pair("hide", true)].numFrames = loadAnimation(this->animMap[std::pair("hide", true)].frames, 8, 8, 0, 1, 0);
	this->animMap[std::pair("hide", true)].animDelay = 0.1f;
	this->animMap[std::pair("hide", true)].pauseDelay = 0.f;
	this->animMap[std::pair("hide", true)].looping = false;

	this->animMap.emplace(std::pair{ "unhide", false }, AnimData2{});
	this->animMap[std::pair("unhide", false)].numFrames = loadAnimation(this->animMap[std::pair("unhide", false)].frames, 8, 8, 0, 7, 0);
	this->animMap[std::pair("unhide", false)].animDelay = 0.05f;
	this->animMap[std::pair("unhide", false)].pauseDelay = 0.f;
	this->animMap[std::pair("unhide", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "unhide", true }, AnimData2{});
	this->animMap[std::pair("unhide", true)].numFrames = loadAnimation(this->animMap[std::pair("unhide", true)].frames, 8, 8, 0, 2, 0);
	this->animMap[std::pair("unhide", true)].animDelay = 0.05f;
	this->animMap[std::pair("unhide", true)].pauseDelay = 0.f;
	this->animMap[std::pair("unhide", true)].looping = false;

	this->animMap.emplace(std::pair{ "die", false }, AnimData2{});
	this->animMap[std::pair("die", false)].numFrames = loadAnimation(this->animMap[std::pair("die", false)].frames, 8, 8, 0, 8, 0);
	this->animMap[std::pair("die", false)].animDelay = 0.05f;
	this->animMap[std::pair("die", false)].pauseDelay = 0.f;
	this->animMap[std::pair("die", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "die", true }, AnimData2{});
	this->animMap[std::pair("die", true)].numFrames = loadAnimation(this->animMap[std::pair("die", true)].frames, 8, 8, 0, 3, 0);
	this->animMap[std::pair("die", true)].animDelay = 0.05f;
	this->animMap[std::pair("die", true)].pauseDelay = 0.f;
	this->animMap[std::pair("die", true)].looping = false;

	this->animMap.emplace(std::pair{ "idle", false }, AnimData2{});
	this->animMap[std::pair("idle", false)].numFrames = loadAnimation(this->animMap[std::pair("idle", false)].frames, 1, 1, 0, 9, 0);
	this->animMap[std::pair("idle", false)].animDelay = 0.05f;
	this->animMap[std::pair("idle", false)].pauseDelay = 0.f;
	this->animMap[std::pair("idle", false)].looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "idle", true }, AnimData2{});
	this->animMap[std::pair("idle", true)].numFrames = loadAnimation(this->animMap[std::pair("idle", true)].frames, 1, 1, 0, 4, 0);
	this->animMap[std::pair("idle", true)].animDelay = 0.05f;
	this->animMap[std::pair("idle", true)].pauseDelay = 0.f;
	this->animMap[std::pair("idle", true)].looping = true;

	this->animMap.emplace(std::pair{ "hit", false }, AnimData2{});
	this->animMap[std::pair("hit", false)].numFrames = loadAnimation(this->animMap[std::pair("hit", false)].frames, 1, 1, 0, 9, 2);
	this->animMap[std::pair("hit", false)].animDelay = 0.16f;
	this->animMap[std::pair("hit", false)].pauseDelay = 0.f;
	this->animMap[std::pair("hit", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "hit", true }, AnimData2{});
	this->animMap[std::pair("hit", true)].numFrames = loadAnimation(this->animMap[std::pair("hit", true)].frames, 1, 1, 0, 4, 2);
	this->animMap[std::pair("hit", true)].animDelay = 0.16f;
	this->animMap[std::pair("hit", true)].pauseDelay = 0.f;
	this->animMap[std::pair("hit", true)].looping = false;

	loadBBoxes("assets/data/bboxes/enemies/snail.bbox");
}

void Snail::setup()
{
	Enemy::setup(Cfg::Textures::SnailEnemy, { {0,0},{70,46} }, { {15.f,16.f},{20.f,30.f} }, SpriteType::Enemy, { 1300.f, 900.f - 50.f - 30.f }, AnimDirType::Left, false);
}

void Snail::input()
{
}

void Snail::update()
{
	if (cmdList.size() > 0)
	{
		if (cmdList.front()->isDone())
		{
			//erase from list
			cmdList.pop_front();
		}
	}
	setPrevPos(getPos());
	if (cmdList.size() > 0)
	{
		this->cmdList.front()->tick();
	}

	if (getPos().x < getPrevPos().x)
	{
		facingLeft = true;
		if (currentAnim != "walk")
		{
			currentAnim = "walk";
		}
	}
	else if (getPos().x > getPrevPos().x)
	{
		facingLeft = false;
		if (currentAnim != "walk")
		{
			currentAnim = "walk";
		}
	}
	else
	{
		if (currentAnim != "idle")
		{
			currentAnim = "idle";
		}
	}

	// Handle animation frame switching and pause at the start of an animation if it has a pause delay of more than 0.f
	this->pauseElapsed += gTime;
	if (this->pauseElapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].pauseDelay && this->animPaused == true)
	{
		this->elapsed = std::min(this->pauseElapsed - gTime, 0.f);
		this->animPaused = false;
		this->elapsed = -gTime;
	}


	if (this->animPaused == false)
	{
		this->elapsed += gTime;
	

		if (this->elapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].animDelay)
		{
			this->elapsed = 0.f;
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].animate();
			this->index = this->animMap[std::pair(this->currentAnim, this->facingLeft)].index;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = this->index;
			if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].onLastFrame)
			{
				this->animPaused = true;
				this->pauseElapsed = 0.f;
			}

		}
	}


	bbox = animMap[std::pair(currentAnim, facingLeft)].bboxes[index];
	texRect = animMap[std::pair(currentAnim, facingLeft)].frames[index];
}
