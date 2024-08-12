#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <vector>
#include <string>
#include <SFML/Graphics/Rect.hpp>

struct Animation
{
	std::vector<sf::IntRect> frames;

	void addFrame(const sf::IntRect& iRect_);
	void addFrameSheet(const std::string& filename);

};

#endif
