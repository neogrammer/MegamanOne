#ifndef STAGE_H__
#define STAGE_H__
#include <vector>
#include <Platform.h>
class Stage
{

	int stageID{ 1 };

	int numPlatforms{};
	std::vector<Platform> platforms{};

public:
	Stage(int numPlaforms = 1);
	~Stage();
	void input();
	void update();

	void render();

	std::vector<Platform>& getPlats();
	Platform* createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_);
	static int lua_createPlatform(lua_State* L)
	{
		if (lua_gettop(L) != 12) return -1;
		Stage* object = static_cast<Stage*>(lua_touserdata(L, 1));
		int id_ = (int)lua_tointeger(L, 2);
		int ir_x = (int)lua_tointeger(L, 3);
		int ir_y = (int)lua_tointeger(L, 4);
		int ir_w = (int)lua_tointeger(L, 5);
		int ir_h = (int)lua_tointeger(L, 6);
		int bb_x = (int)lua_tointeger(L, 7);
		int bb_y = (int)lua_tointeger(L, 8);
		int bb_w = (int)lua_tointeger(L, 9);
		int bb_h = (int)lua_tointeger(L, 10);
		int px = (int)lua_tointeger(L, 11);
		int py = (int)lua_tointeger(L, 12);
		sf::IntRect irect_ = { {ir_x,ir_y},{ir_w,ir_h} };
		sf::FloatRect bbox_ = { {(float)bb_x,(float)bb_y},{(float)bb_w,(float)bb_h} };
		sf::Vector2f pos_ = { (float)px , (float)py};
		lua_pushlightuserdata(L, object->createPlatform(id_, irect_, bbox_, pos_));
		return 1;
	};
};

#endif