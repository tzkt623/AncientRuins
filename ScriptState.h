#pragma once

#include "StateMachine.h"

namespace tezcat
{
	class ScriptClass : public State
	{
	public:

		virtual ~ScriptClass();
		virtual void onEnter() override;
		virtual void onExit() override;
		virtual void execute() override;


	};
}