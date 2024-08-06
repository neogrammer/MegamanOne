#include <pch.h>
#include <Stage.h>
#include <Projectile.h>
#include <Snail.h>
#include <MoveCommand.h>
void Stage::manipulate(lua_State* L)
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
				lua_getglobal(L, "IssueNextTask");
				if (lua_isfunction(L, -1))
				{
					//lua_pushlightuserdata(L, this);
					lua_pushlightuserdata(L, m->plat);
					if (!scr::CheckLua(L, lua_pcall(L, 1, 0, 0)))
					{
						// script bad
					}
				}
		}
	}


	cleanupManipluators(mManipulators);
}

void Stage::update(lua_State* L)
{
	manipulate(L);
	for (auto& plat : platforms )
	{
		plat.update();
		//plat.setControlledByScript(false);
		//plat.tickMovement();
		//plat.setControlledByScript(true);
	}

	for (auto& e : enemies)
	{
		e->update();
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

	stage1Music = &Cfg::music.get((int)Cfg::Music::Stage1);
	stage1Music->play();
	stage1Music->setVolume(20);

	enemies.clear();
	enemies.emplace_back(std::make_unique<Snail>());
	MoveData data{ {enemies.back()->getPos().x - 600.f, enemies.back()->getPos().y}, 12.f};
	enemies.back()->pushCommand(CmdType::Move, reinterpret_cast<void*>(&data));


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
	for (auto& e : enemies)
	{
		e->input();
	}
}

void Stage::render()
{
	for (auto& plat : platforms)
	{
		plat.render();
	}

	for (auto& e : enemies)
	{
		e->render();
	}
}

std::vector<Platform>& Stage::getPlats()
{
	 return platforms;
}

void Stage::moveObject(Platform& dyno,float x, float time)
{
	Platform* tmp = &dyno;
	if (tmp != nullptr)
	{
		mNewManipulators.emplace_back(new ManInterpPos{ &dyno, x, time });

	}
	tmp = nullptr;
}

void Stage::moveObjectUp(Platform& dyno, float y, float time)
{
	Platform* tmp = &dyno;
	if (tmp != nullptr)
	{
		mNewManipulators.emplace_back(new ManInterpPosY{ &dyno, y, time });
		dyno.setPrevPos(dyno.getPos());
		if (y < dyno.getPos().y)
			dyno.setMinY(y);
		// else set as max y
	}
	tmp = nullptr;
}

Platform* Stage::createPlatform(int id_, sf::IntRect irect_, sf::FloatRect bbox_, sf::Vector2f pos_)
{
	platforms.emplace_back(Platform{ Cfg::Textures::FlyPad, irect_, bbox_, {pos_.x,pos_.y} });
	Platform* plat = &platforms.back();
	plat->id = (int)platforms.size();
	return plat;
}

void Stage::retry(Platform& plat)
{
	auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&plat](Manipulator* m)->bool { return m->plat == &plat; });
	if (it != mManipulators.end())
	{
		(*it)->complete = false;
	}
}

Stage::ManInterpPos::ManInterpPos(Platform* obj, float x, float time)
	: elapsed{ 0.f }
{
	plat = obj;
	startPos = {plat->getPos().x, plat->getPos().y} ;
	targetPos = { x, plat->getPos().y };
	//elapsed = -1 *  (1.f / 60.f);
	//auto sudoPrevPos = olc::vf2d{ (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y };
	//plat->setPrevPos(sudoPrevPos);
	//elapsed = 0.f;
	completionTime = time;
}


bool Stage::ManInterpPos::update()
{
	elapsed += gTime;
	plat->setPrevPos(plat->getPos());
	auto p = olc::vf2d{ (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y };
	plat->setVelocity({(p.x - plat->getPrevPos().x) / gTime, 0.f});

	//plat->setPos( {(targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y});
	if (elapsed >= completionTime)
	{
		plat->setVelocity({ 0.f,0.f });
		plat->setPos({ targetPos.x, targetPos.y });
		complete = true;
	}
	


	return complete;
}

Stage::ManInterpPosY::ManInterpPosY(Platform* obj, float y, float time) : elapsed{ 0.f }
{
	plat = obj;
	startPos = { plat->getPos().x, plat->getPos().y };
	targetPos = { plat->getPos().x, y };
	completionTime = time;
}

bool Stage::ManInterpPosY::update()
{
	//elapsed += gTime;
	//plat->setPrevPos(plat->getPos());
	//plat->setPos({ (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y });

	elapsed += gTime;
	
		plat->setPrevPos(plat->getPos());
		auto p = olc::vf2d{ (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y };
		plat->setVelocity({ 0.f,  (p.y - plat->getPrevPos().y) / gTime });

	if (elapsed >= completionTime)
	{
		plat->setVelocity({ 0.f,0.f });
		plat->setPos({ targetPos.x, targetPos.y });
		complete = true;
	}
	return complete;
}
