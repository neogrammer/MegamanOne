#ifndef STAGE_H__
#define STAGE_H__
#include <vector>
#include <Platform.h>
#include <memory>
class Enemy;
class Projectile;
class Stage
{
	sf::Music* stage1Music{ nullptr };
	int stageID{ 1 };

	int numPlatforms{};
	std::vector<Platform> platforms{};
	std::vector<std::unique_ptr<Enemy>> enemies{};
public:
	struct Manipulator
	{
		Platform* plat;
		virtual bool update() = 0;
		bool complete{ false };
	};

	struct ManInterpPos : Manipulator
	{
		sf::Vector2f startPos;
		sf::Vector2f targetPos;
		float completionTime;
		float elapsed;
		ManInterpPos(Platform* obj, float x, float time);
		bool update() override final;
	};

	struct ManInterpPosY : Manipulator
	{
		sf::Vector2f startPos;
		sf::Vector2f targetPos;
		float completionTime;
		float elapsed;
		ManInterpPosY(Platform* obj, float y, float time);
		bool update() override final;
	};


	void manipulate(lua_State* L);
	void update(lua_State* L);
	void cleanupManipluators(std::vector<Manipulator*>& vec);
	void destroyAllManipluators(std::vector<Manipulator*>& vec);
	bool isManipulatorCompleted(std::vector<Manipulator*>& vec);
	std::vector<Manipulator*> mManipulators;
	std::vector<Manipulator*> mNewManipulators;



	Stage(int numPlaforms = 2);
	~Stage();
	void input();

	void render();

	std::vector<Platform>& getPlats();
	void moveObject(Platform& dyno, float x, float time);
	void moveObjectUp(Platform& dyno, float y, float time);
	static int lua_moveObject(lua_State* L)
	{

		if (lua_gettop(L) != 5) return -1;

		Stage* object = static_cast<Stage*>(lua_touserdata(L, 1));
		Platform* plat = static_cast<Platform*>(lua_touserdata(L, 2));
		float x = (float)lua_tonumber(L, 3);
		float y = (float)lua_tonumber(L, 4);
		float t = (float)lua_tonumber(L, 5);
		object->moveObject(*plat, x, t);
		return 0;
	};

	static int lua_moveObjectUp(lua_State* L)
	{

		if (lua_gettop(L) != 5) return -1;

		Stage* object = static_cast<Stage*>(lua_touserdata(L, 1));
		Platform* plat = static_cast<Platform*>(lua_touserdata(L, 2));
		float x = (float)lua_tonumber(L, 3);
		float y = (float)lua_tonumber(L, 4);
		float t = (float)lua_tonumber(L, 5);
		object->moveObjectUp(*plat, y, t);
		return 0;
	};

	Platform* createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_);
	void retry(Platform& plat);
	static int lua_retry(lua_State* L)
	{
		if (lua_gettop(L) != 2) return -1;
		Stage* object = static_cast<Stage*>(lua_touserdata(L, 1));
		Platform* plat = static_cast<Platform*>(lua_touserdata(L, 2));
		object->retry(*plat);
		return 0;
	};
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