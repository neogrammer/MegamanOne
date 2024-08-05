#include <pch.h>
#include <Tile.h>
#include <Projectile.h>
Tile::Tile(Cfg::Textures tex_, sf::IntRect texRect_, olc::v_2d<float> pos_)
	: ASprite{ tex_, texRect_, {{0.f,0.f},{(float)texRect_.width,(float)texRect_.height}}, SpriteType::Tile, pos_}
{}
