#pragma once

#include "DynamicMemory.h"

namespace tezcat
{


	template<typename NameType, typename... Args>
	class Signal : public DynamicMemory
	{
	public:
		Signal(const NameType &name, const Args... args) : m_Name(name), m_Datas(std::make_tuple(args...)) {}
		~Signal(){}

		virtual void recycle() { delete this; }

		void emit()
		{

		}

	private:
		NameType m_Name;
		std::tuple<Args...> m_Datas;
	};
}