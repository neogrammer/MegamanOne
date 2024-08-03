#ifndef FSM_PLAYER_H__
#define FSM_PLAYER_H__
#include <FSM.h>
#include <optional>
#include <iostream>
#include <type_traits>

class FSM_Player : public FSM<FSM_Player, PlayerStateVar>
{

public:
	std::optional<PlayerStateVar> On_Event(state_Standing& s, const evt_Jumped& e)
	{
		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}

	std::optional<PlayerStateVar> On_Event(state_Standing& s, const evt_StartedMoving& e)
	{
		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "running";
		return state_Running{};
	}

	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_StoppedMoving& e)
	{
		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		return state_Standing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_Jumped& e)
	{
		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}

	std::optional<PlayerStateVar> On_Event(state_Jumping& s, const evt_ReachedJumpPeak& e)
	{
		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "falling";
		return state_Falling{};
	}

	std::optional<PlayerStateVar> On_Event(state_Falling& s, const evt_Landed& e)
	{
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "landing";
		justChanged_ = true;
		return state_Landing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Landing& s, const evt_AnimationFinished& e)
	{
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		justChanged_ = true;
		return state_Standing{};
	}

	template <typename State, typename Event>
	std::optional<PlayerStateVar> On_Event(State&, const Event&)
	{
		justChanged_ = false;
		return std::nullopt;
	}

	//AnimType getType(state_TransToFall& s)
	//{
	//	return  AnimType::TransFall;
	//}


	//template <typename State>
	//AnimType getType(State& s)
	//{
	//	std::cout << "animation not added to this state yet! STATE: " << typeid(s).name() << std::endl;
	//	return AnimType::Count;
	//}
};

#endif