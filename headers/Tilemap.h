#ifndef TILEMAP_H__
#define TILEMAP_H__
#include <Cfg.h>
#include <vector>
#include <StatTile.h>
#include <string>
#include <memory>
class Projectile;
class Tileset;
class Tilemap
{
	std::unique_ptr<Tileset> tileset;;
	std::vector<StatTile> tiles;
	std::vector<StatTile> obstacles;

	int width;
	int height;
public:
	Tilemap() = delete;
	explicit Tilemap(Cfg::Textures tex_, const std::string& tilesetName_, const std::string& mapName_, int zone = 1);
	~Tilemap();
	Tilemap(const Tilemap&) = delete;
	Tilemap& operator=(const Tilemap&) = delete;
	Tilemap(Tilemap&&) = delete;
	Tilemap& operator=(Tilemap&&) = delete;

	void render();
	std::vector<StatTile>& getSolidTiles();
};

#endif