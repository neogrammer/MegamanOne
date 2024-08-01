#include <pch.h>
#include <Stage.h>

Stage::Stage(int numPlatforms_)
{
	numPlatforms = numPlatforms_;
	platforms.clear();
	platforms.shrink_to_fit();
	platforms.reserve(numPlatforms);

	
}

void Stage::input()
{
}

void Stage::update()
{
}

void Stage::render()
{
}

Platform* Stage::createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_)
{
	Platform* plat = &platforms.emplace_back(Platform{ Cfg::Textures::FlyPad, irect_, bbox_, {pos_.x,pos_.y} });
	plat->id = id_;
	return plat;
}
