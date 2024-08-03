#include <pch.h>
#include <MachineHandler.h>


MachineHandler::MachineHandler(MachineType mType_)
	: mType{mType_}
	, machine{}
{
	switch (mType)
	{
	case MachineType::Player:
	{
		machine = std::make_unique<FSM_Player>();
		
	}
	break;
	default:
		break;
	}

}

FSM<>& MachineHandler::getMachine()
{
	return *machine;
}
