#pragma once

namespace tezcat
{
	template<class CLASS>
	class Singleton
	{
	public:
		static CLASS *getInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new CLASS();
			}
			return m_Instance;
		}

		static void deleteInstance()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
			}
		}

	private:
		static CLASS *m_Instance;
	};

	template<class CLASS> CLASS *Singleton<CLASS>::m_Instance = nullptr;
}

#define TT_Singlenton(Type) tezcat::Singleton<Type>::getInstance()
#define TT_Set_Singlenton(CLASS)\
private:\
	friend tezcat::Singleton<CLASS>;\
	CLASS();\
	~CLASS();\
	CLASS(const CLASS &);