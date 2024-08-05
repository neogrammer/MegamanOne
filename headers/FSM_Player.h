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
		std::cout << "jumping" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}

	std::optional<PlayerStateVar> On_Event(state_Standing& s, const evt_StartedMoving& e)
	{
		std::cout << "startingRun" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "startingRun";
		return state_StartingRun{};
	}

	std::optional<PlayerStateVar> On_Event(state_StartingRun& s, const evt_AnimationFinished& e)
	{
		std::cout << "running" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "running";
		return state_Running{};
	}

	std::optional<PlayerStateVar> On_Event(state_StartingRun& s, const evt_Jumped& e)
	{
		std::cout << "jumping" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}

	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_Jumped& e)
	{
		std::cout << "jumping" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}

	std::optional<PlayerStateVar> On_Event(state_StartingRun& s, const evt_StoppedMoving& e)
	{
		std::cout << "idle" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		return state_Standing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_StoppedMoving& e)
	{
		std::cout << "idle" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		return state_Standing{};
	}


	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_Fell& e)
	{
		std::cout << "falling" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "falling";
		return state_Falling{};
	}
	std::optional<PlayerStateVar> On_Event(state_Jumping& s, const evt_ReachedJumpPeak& e)
	{
		std::cout << "peakingJump" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "peakingJump";
		return state_PeakingJump{};
	}

	std::optional<PlayerStateVar> On_Event(state_PeakingJump& s, const evt_Fell& e)
	{
		std::cout << "falling" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "falling";
		return state_Falling{};
	}

	std::optional<PlayerStateVar> On_Event(state_Falling& s, const evt_Landed& e)
	{
		std::cout << "Landing" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "landing";
		justChanged_ = true;
		return state_Landing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Landing& s, const evt_AnimationFinished& e)
	{
		std::cout << "idle" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		justChanged_ = true;
		return state_Standing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Standing& s, const evt_StartedShooting& e)
	{
		std::cout << "brandishing" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "brandishing";
		return state_Brandishing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Falling& s, const evt_StartedShooting& e)
	{
		std::cout << "fallingAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "fallingAndShooting";
		return state_ShootingAndFalling{};
	}
	/*std::optional<PlayerStateVar> On_Event(state_Landing& s, const evt_StartedShooting& e)
	{
		std::cout << "Shooting and Landing" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "landingAndshooting";
		return state_ShootingAndLanding{};
	}*/

	std::optional<PlayerStateVar> On_Event(state_Jumping& s, const evt_StartedShooting& e)
	{
		std::cout << "jumpingAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumpingAndShooting";
		return state_JumpingAndShooting{};
	}


	std::optional<PlayerStateVar> On_Event(state_Brandishing& s, const evt_StoppedShooting& e)
	{
		std::cout << "idle" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		return state_Standing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Brandishing& s, const evt_AnimationFinished& e)
	{
		std::cout << "Shooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "shooting";
		return state_Shooting{};
	}
	std::optional<PlayerStateVar> On_Event(state_Brandishing& s, const evt_Jumped& e)
	{
		std::cout << "jumpingAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumpingAndShooting";
		return state_JumpingAndShooting{};
	}
	std::optional<PlayerStateVar> On_Event(state_Shooting& s, const evt_StoppedShooting& e)
	{
		std::cout << "idle" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "idle";
		return state_Standing{};
	}

	std::optional<PlayerStateVar> On_Event(state_Shooting& s, const evt_StartedMoving& e)
	{
		std::cout << "runningAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "runningAndShooting";
		return state_ShootingAndRunning{};
	}

	std::optional<PlayerStateVar> On_Event(state_Shooting& s, const evt_Jumped& e)
	{
		std::cout << "jumpingAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumpingAndShooting";
		return state_JumpingAndShooting{};
	}

	std::optional<PlayerStateVar> On_Event(state_JumpingAndShooting& s, const evt_StoppedShooting& e)
	{
		std::cout << "jumping" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumping";
		return state_Jumping{};
	}


	std::optional<PlayerStateVar> On_Event(state_JumpingAndShooting& s, const evt_ReachedJumpPeak& e)
	{
		std::cout << "jumpPeakShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumpPeakShooting";
		return state_PeakingJumpShoot{};
	}

	std::optional<PlayerStateVar> On_Event(state_PeakingJumpShoot& s, const evt_StoppedShooting& e)
	{
		std::cout << "peakingJump" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "peakingJump";
		return state_PeakingJump{};
	}

	std::optional<PlayerStateVar> On_Event(state_PeakingJumpShoot& s, const evt_Fell& e)
	{
		std::cout << "fallingAndShooting" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "fallingAndShooting";
		return state_ShootingAndFalling{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndFalling& s, const evt_StoppedShooting& e)
	{
		std::cout << "falling" << std::endl;

		justChanged_ = true;
		FSM<FSM_Player, PlayerStateVar>::currentState_ = "falling";
		return state_Falling{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndFalling& s, const evt_Landed& e)
	{
		justChanged_ = true;
		std::cout << "Shooting and Landing" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "landingAndShooting";
		return state_ShootingAndLanding{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndLanding& s, const evt_StoppedShooting& e)
	{
		justChanged_ = true;
		std::cout << "Landing" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "landing";
		return state_Landing{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndLanding& s, const evt_AnimationFinished& e)
	{
		justChanged_ = true;
		std::cout << "shooting" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "shooting";
		return state_Shooting{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndLanding& s, const evt_StartedMoving& e)
	{
		justChanged_ = true;
		std::cout << "runningAndShooting" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "runningAndShooting";
		return state_ShootingAndRunning{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndRunning& s, const evt_StoppedMoving& e)
	{
		justChanged_ = true;
		std::cout << "shooting" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "shooting";
		return state_Shooting{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndRunning& s, const evt_Jumped& e)
	{
		justChanged_ = true;
		std::cout << "jumpingAndShooting" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "jumpingAndShooting";
		return state_JumpingAndShooting{};
	}

	std::optional<PlayerStateVar> On_Event(state_ShootingAndRunning& s, const evt_StoppedShooting& e)
	{
		justChanged_ = true;
		std::cout << "running" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "running";
		return state_Running{};
	}

	std::optional<PlayerStateVar> On_Event(state_Running& s, const evt_StartedShooting& e)
	{
		justChanged_ = true;
		std::cout << "runningAndShooting" << std::endl;

		FSM<FSM_Player, PlayerStateVar>::currentState_ = "runningAndShooting";
		return state_ShootingAndRunning{};
	}

	template <typename State, typename Event>
	std::optional<PlayerStateVar> On_Event(State&, const Event&)
	{
		//std::cout << "No Transition" << std::endl;

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