#pragma once

#include <vector>
#include <string>
#include <bitset>

namespace tezcat
{
	template<unsigned int StateCount>
	class ControlManager
	{
	public:
		ControlManager():m_State(0) {}
		~ControlManager() {}

		void setState(const unsigned int &index)
		{
			m_State.set(index, true);
		}

		template<typename Enum>
		void setState(typename std::enable_if<std::is_enum<Enum>::value, Enum>::value_type em)
		{
			m_State.set(static_cast<unsigned int>(em), true);
		}

		void clearState(const unsigned int &index)
		{
			m_State.set(index, false);
		}

		bool isInThisState(const unsigned int &index)
		{
			return m_State.at(index);
		}

		template<typename Enum>
		bool isInThisState(typename std::enable_if<std::is_enum<Enum>::value, Enum>::value_type em)
		{
			return m_State.at(static_cast<unsigned int>(em));
		}

// 		template<typename Enum>
// 		void registerModel(std::enable_if<std::is_enum<Enum>::value, Enum>::value_type em)
// 		{
// 			std::bitset<StateCount> state()
// 		}

	private:
		std::bitset<StateCount> m_State;
		std::vector<std::string> m_StateInfo;
	};
}