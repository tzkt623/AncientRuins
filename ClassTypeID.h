#pragma once

namespace tezcat
{
	template<typename Base>
	class ClassTypeID
	{
	public:

		template <typename T>
		static size_t getTypeID()
		{
			static const size_t id = m_NextTypeID++;
			return id;
		}

	private:

		static size_t m_NextTypeID;
	};

	template<typename Base>
	size_t ClassTypeID<Base>::m_NextTypeID = 0;
}

