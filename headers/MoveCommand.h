#ifndef MOVECOMMAND_H__
#define MOVECOMMAND_H__
#include <Command.h>
#include <Enemy.h>
class Projectile;
struct MoveData
{
	olc::vf2d target_{};
	float completeTime_{};
};

class MoveCommand : public Command
{
	
	float completeTime{};
	float timeElapsed{ 0.f };
	olc::vf2d target{};
	olc::utils::geom2d::ray<float> path{};
public:
	MoveCommand() = delete;
	explicit MoveCommand(Enemy& enemy_, olc::vf2d target_, float completeTime_);
	virtual ~MoveCommand() = default;
	MoveCommand(const MoveCommand&) = delete;
	MoveCommand(MoveCommand&&) = delete;
	MoveCommand& operator=(const MoveCommand&) = delete;
	MoveCommand& operator=(MoveCommand&&) = delete;

	bool tick() override;

};

#endif // !MOVECOMMAND_H__
