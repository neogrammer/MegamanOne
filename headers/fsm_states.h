#ifndef FSM_STATES_H__
#define FSM_STATES_H__

#include <variant>

struct state_Standing { };
struct state_StartingRun{};
struct state_Running { };
struct state_Jumping { };
struct state_Falling { };
struct state_Shooting { };
struct state_ShootingAndRunning { };
struct state_ShootingAndJumping { };
struct state_ShootingAndFalling { };
struct state_Landing {};

using PlayerStateVar = std::variant<state_Falling, state_StartingRun, state_Running, state_Jumping, state_Standing
								, state_Shooting, state_ShootingAndRunning
								, state_ShootingAndJumping, state_ShootingAndFalling, state_Landing>;

#endif