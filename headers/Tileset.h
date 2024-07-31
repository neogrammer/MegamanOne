#ifndef TILESET_H__
#define TILESET_H__
#include <Cfg.h>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class Tileset
{  
	struct TileData
	{
		sf::IntRect texRect{};
		bool solid{};
	};

	Cfg::Textures tex;
	std::vector<TileData> tData;
	int pitch;
	int rows;
	int tileSize;
public:
	Tileset() = delete;
	explicit Tileset(Cfg::Textures tex_, const std::string& tileset_);
	~Tileset();
	Tileset(const Tileset&) = delete;
	Tileset& operator=(const Tileset&) = delete;
	Tileset(Tileset&&) = delete;
	Tileset& operator=(Tileset&&) = delete;

	inline int getTileSize() { 	return tileSize; 	}
	inline int getNumTiles() { return pitch * rows; }
	bool isSolid(int index_);
	bool isSolid(int col_, int row_);
	sf::IntRect getTexRect(int index_);
	sf::IntRect getTexRect(int col_, int row_);
};

#endif