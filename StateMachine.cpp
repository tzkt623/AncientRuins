#include "StateMachine.h"

namespace tezcat
{
	StateMachine::StateMachine():
		m_NowState(nullptr)
	{

	}

	StateMachine::~StateMachine()
	{

	}

	void StateMachine::execute()
	{
		m_NowState->execute();
	}

	void StateMachine::changeState(State *state)
	{
		if (m_NowState != nullptr)
		{
			m_NowState->onExit();
		}
		m_NowState = state;
		m_NowState->onEnter();
	}

	void StateMachine::pushState(State *state)
	{
		m_States.push_back(m_NowState);
		m_NowState = state;
		m_NowState->onEnter();
	}

	void StateMachine::clear()
	{
		
	}

}

