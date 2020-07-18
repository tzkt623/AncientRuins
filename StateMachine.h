#pragma once

#include <vector>

namespace tezcat
{
	class State
	{
	public:
		virtual ~State() {}
		virtual void onEnter() = 0;
		virtual void onExit() = 0;
		virtual void execute() = 0;
	};

	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		void changeState(State *state);
		void execute();
		void pushState(State *state);

		void clear();

	private:
		State *m_NowState;
		std::vector<State *> m_States;
	};
}