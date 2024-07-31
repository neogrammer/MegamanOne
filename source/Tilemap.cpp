#include <pch.h>
#include <Tilemap.h>
#include <Tileset.h>
#include <fstream>

Tilemap::Tilemap(Cfg::Textures tex_, const std::string& tilesetName_, const std::string& mapName_, int zone)
	: tileset{std::make_unique<Tileset>(tex_, tilesetName_)}
{
	std::ifstream file;
	file.open("assets/data/tilemaps/" + mapName_ + "/zone" + std::to_string(zone) + ".map");
	
	file >>width >> height;
	tiles.clear();
	obstacles.clear();
	tiles.reserve((std::size_t)width * height);
	obstacles.reserve((std::size_t)width * height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int num;
			file >> num;
			auto  tmp = tileset->getTexRect(num);
			auto pos = sf::Vector2f((float)x * (float)tileset->getTileSize(), (float)y * (float)tileset->getTileSize());
			tiles.emplace_back(Tile{ tex_, tmp, { pos.x, pos.y } });
			if (tileset->isSolid(num))
			{
				obstacles.push_back(tiles.back());
			}
		}
	}
	obstacles.shrink_to_fit();
}

void Tilemap::render()
{
	for (auto& tile : obstacles)
	{
		gWnd.draw(*tile.getSpr());
	}
}

std::vector<Tile>& Tilemap::getSolidTiles()
{
	return obstacles;
}
