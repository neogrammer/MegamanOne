#ifndef MACHINEHANDLER_H__
#define MACHINEHANDLER_H__
#include <memory>
#include <Cfg.h>
#include <FSM_Player.h>

template <typename Derived = FSM_Player, typename StateVariant = PlayerStateVar>
class FSM;

class MachineHandler
{
	MachineType mType;
	std::unique_ptr<FSM<>> machine;

public:

	MachineHandler(MachineType mType_);

	FSM<>& getMachine();
};

#endif