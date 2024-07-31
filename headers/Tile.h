#ifndef TILE_H__
#define TILE_H__

#include <ASprite.h>

class Tile : public ASprite
{
public:
	Tile(Cfg::Textures tex_, sf::IntRect texRect_, olc::v_2d<float> pos_ = { 0.f,0.f });
	~Tile() override = default;
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;
};

#endif