#pragma once

#include <vector>

namespace tezcat
{
	template<typename T>
	class Manager
	{
	public:
		Manager()
		{

		}
		~Manager()
		{

		}

		T create()
		{
			return new T();
		}


	private:
		std::vector<T> m_Vector;
	};
}

