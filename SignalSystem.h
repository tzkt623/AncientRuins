#pragma once

#include <type_traits>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "Signal.h"
namespace tezcat
{
	class SignalSystem
	{
	public:
		SignalSystem() {}
		~SignalSystem() {}

		template<typename... Args>
		void connect(const std::string &name, const std::function<void(Args...)> &function)
		{
			auto *s = new Signal<Args>(name, Args...);
			m_Signals[name] = s;
		}

	private:

		std::unordered_map<std::string, DynamicMemory *> m_Signals;
	};
}