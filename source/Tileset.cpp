#include <pch.h>
#include <Tileset.h>
#include <fstream>
Tileset::Tileset(Cfg::Textures tex_, const std::string& tileset_)
{
	tex = tex_;

	std::ifstream file;
	file.open("assets/data/tilesets/" + tileset_ + ".tst");
	file >> this->pitch >> rows >> tileSize;

	tData.reserve(rows * pitch);
	for (int i = 0; i < rows * pitch; i++)
	{
		int y = i / pitch;
		int x = i / rows;
		this->tData.emplace_back(TileData{});
		tData.back().texRect = { {x * tileSize, y * tileSize},{ tileSize, tileSize} };
		int solidInt;
		file >> solidInt;
		if (solidInt == 1)
			tData.back().solid = true;
		else
			tData.back().solid = false;
	}
	file.close();
}

Tileset::~Tileset()
{

}

bool Tileset::isSolid(int index_)
{
	return tData.at(index_).solid;
}

bool Tileset::isSolid(int col_, int row_)
{
	int index = row_ * pitch + col_;
	return tData.at(index).solid;

}

sf::IntRect Tileset::getTexRect(int index_)
{
	return tData.at(index_).texRect;

}

sf::IntRect Tileset::getTexRect(int col_, int row_)
{
	int index = row_ * pitch + col_;
	return tData.at(index).texRect;

}
