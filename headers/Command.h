#ifndef COMMAND_H__
#define COMMAND_H__
#include <Enemy.h>
class Command
{
protected:
	bool done{ false };
	Enemy* enemy{};

public:
	Command() = delete;
	explicit Command(Enemy& enemy_) : done{ false }, enemy { &enemy_ } {};
	virtual ~Command() = default;
	Command(const Command&) = delete;
	Command(Command&&) = delete;
	Command& operator=(const Command&) = delete;
	Command& operator=(Command&&) = delete;


	virtual bool tick() = 0;

	inline bool isDone() { return done; }
};
#endif