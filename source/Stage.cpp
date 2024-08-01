#include <pch.h>
#include <Stage.h>

Stage::Stage(int numPlatforms_)
{
	numPlatforms = numPlatforms_;
	platforms.clear();
	platforms.shrink_to_fit();
	platforms.reserve(numPlatforms);

	
}

Stage::~Stage()
{
}

void Stage::input()
{
	for (auto& plat : platforms)
	{
		plat.input();
	}
}

void Stage::update()
{
	for (auto& plat : platforms)
	{
		plat.update();
	}
}

void Stage::render()
{
	for (auto& plat : platforms)
	{
		plat.render();
	}
}

std::vector<Platform>& Stage::getPlats()
{
	 return platforms;
}

Platform* Stage::createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_)
{
	Platform* plat = &platforms.emplace_back(Platform{ Cfg::Textures::FlyPad, irect_, bbox_, {pos_.x,pos_.y} });
	plat->id = id_;
	return plat;
}
