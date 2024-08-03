#ifndef FSM_H__
#define FSM_H__
#include <variant>
#include <optional>
#include <fsm_events.h>
#include <fsm_states.h>
#include <string>

template <typename Derived, typename StateVariant>
class FSM
{
	StateVariant state_;
//	AnimType currType_{ AnimType::Count };
	protected:
		std::string currentState_{ "falling" };
		bool justChanged_{ false };
public:
	inline bool wasJustChanged() { return justChanged_; }
	inline void setJustChanged(bool cond_) { justChanged_ = cond_; }
	inline std::string getCurrentState() { return currentState_; }

	template<typename Event>
	void dispatch(Event&& event)
	{
		Derived& child = static_cast<Derived&>(*this);
		auto new_state = std::visit(
			[&](auto& s) -> std::optional<StateVariant>
			{
				return child.On_Event(s, std::forward<Event>(event));
			}, state_);
		if (new_state)
		{
			state_ = *std::move(new_state);
		}
		/*currType_ = std::visit(
			[&](auto& s) -> AnimType
			{
				return child.getType(s);
			}, state_);*/
	}

	/*AnimType getCurrType()
	{
		return currType_;
	}
	
	AnimType getAnimType()
	{
		Derived& child = static_cast<Derived&>(*this);
		AnimType new_type = std::visit(
			[&](auto& s) -> AnimType
			{
				return child.getType(s);
			}, state_);
		currType_ = new_type;
		return new_type;
		
	}*/
};

#endif