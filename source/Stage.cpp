#include <pch.h>
#include <Stage.h>

void Stage::manipulate(sol::state_view& L)
{
	for (auto& m : mNewManipulators)
	{
		Manipulator* man{ std::move(m) };
		mManipulators.emplace_back(std::move(man));
		man = nullptr;
		m = nullptr;
	}
	mNewManipulators.clear();
	mNewManipulators.shrink_to_fit();
	for (auto& m : mManipulators)
	{
		if (m->update())
		{
			


				L["IssueNextTask"](m->plat);
				//L["IssueNextHorizTask"]( &m->dyno, dynamic_cast<DynBullet*>(m->dyno)->maxDist, m->dyno->pos.y);

				//lua_getglobal(L, "IssueNextHorizTask");
				//if (L, lua_isfunction(L, -1))
				//{
				//	lua_pushlightuserdata(L, this);
				//	lua_pushlightuserdata(L, m->dyno);
				//	lua_pushnumber(L, dynamic_cast<DynBullet*>(m->dyno)->maxDist);
				//	lua_pushnumber(L, m->dyno->pos.y);
				//	if (!mylua::CheckLua(L, lua_pcall(L, 4, 1, 0)))
				//	{
				//		// script bad
				//	}
				//}
		


				//	L["IssueNextTask"](m->dyno, dynamic_cast<DynBullet*>(m->dyno)->maxDist, m->dyno->pos.y);








			/*	sol::protected_function func = L["IssueNextTask"];
				if (func.valid())
				{

				}
				else
				{



				}*/

				//lua_getglobal(L, "IssueNextTask");
				//if (L, lua_isfunction(L, -1))
				//{
				//	lua_pushlightuserdata(L, this);
				//	lua_pushlightuserdata(L, m->dyno);
				//	if (!mylua::CheckLua(L, lua_pcall(L, 2, 1, 0)))
				//	{
				//		// script bad
				//	}
				//}
			
		}
	}


	cleanupManipluators(mManipulators);

	//bool found = false;
	//auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	//return found;

	//bool found = false;
	//	 if (found)
	//	{
	//		delete (*it);
	//		*it = nullptr;
	//		mManipulators.erase(it);
	//		mManipulators.shrink_to_fit();

	//		it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool  { if (m->complete == true) found = true; return found; });
	//	}
	//std::erase_if(mManipulators, [](Manipulator* m)
		//{ return m->complete; });
}

void Stage::update(sol::state_view& L)
{
	manipulate(L);
	for (auto& plat : platforms )
	{
		plat.update();
	}
}

void Stage::cleanupManipluators(std::vector<Manipulator*>& vec)
{
	bool scrubbed = false;

	while (!scrubbed)
	{
		scrubbed = true;
		if (isManipulatorCompleted(vec))
		{
			scrubbed = false;
		}

		if (scrubbed == false)
		{
			bool found = false;
			auto it = std::find_if(vec.begin(), vec.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });

			if (found)
			{
				delete (*it);
				*it = nullptr;
				vec.erase(it);
				vec.shrink_to_fit();
			}
			else
			{
				scrubbed = true;
			}
		}
	}
}

void Stage::destroyAllManipluators(std::vector<Manipulator*>& vec)
{

	bool scrubbed = false;

	while (!scrubbed)
	{
		if (vec.size() > 0 && vec.begin() != vec.end())
		{
			scrubbed = false;
		}
		else
		{
			scrubbed = true;
		}

		if (scrubbed == false)
		{
			auto it = vec.begin();
			delete (*it);
			*it = nullptr;
			vec.erase(it);
			vec.shrink_to_fit();
		}
	}
}

bool Stage::isManipulatorCompleted(std::vector<Manipulator*>& vec)
{
	bool found = false;
	auto it = std::find_if(vec.begin(), vec.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	return found;
}

Stage::Stage(int numPlatforms_)
{
	numPlatforms = numPlatforms_;
	platforms.clear();
	platforms.shrink_to_fit();
	platforms.reserve(numPlatforms);

	mManipulators.clear();
	mNewManipulators.clear();
	
}

Stage::~Stage()
{
	destroyAllManipluators(mManipulators);
	destroyAllManipluators(mNewManipulators);

	bool found = false;
	auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	while (found)
	{
		delete (*it);
		*it = nullptr;
		mManipulators.erase(it);
		mManipulators.shrink_to_fit();
		auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	}
}

void Stage::input()
{
	for (auto& plat : platforms)
	{
		plat.input();
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

void Stage::moveObject(ASprite& dyno,float y, float time)
{
	ASprite* tmp = &dyno;
	if (tmp != nullptr)
	{
		mNewManipulators.emplace_back(new ManInterpPos{ tmp, y, time });
	}
	tmp = nullptr;
}

Platform* Stage::createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_)
{
	Platform* plat = &platforms.emplace_back(Platform{ Cfg::Textures::FlyPad, irect_, bbox_, {pos_.x,pos_.y} });
	plat->id = id_;
	return plat;
}

Stage::ManInterpPos::ManInterpPos(ASprite* obj, float y, float time)
	: elapsed{ 0.f }
{
	plat = obj;
	startPos = {obj->getPos().x, plat->getPos().y} ;
	targetPos = { obj->getPos().x, y};
	completionTime = time;

}


bool Stage::ManInterpPos::update()
{
	elapsed += gTime;
	plat->getPos() = {(targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y};

	if (elapsed >= completionTime)
	{
		plat->getPos() = { targetPos.x, targetPos.y };
		complete = true;
	}

	return complete;
}
