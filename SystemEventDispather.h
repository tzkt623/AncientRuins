#pragma once

#include "SystemEvent.h"
#include <functional>
#include <unordered_map>
#include <map>
#include <vector>

namespace tezcat
{
	template<typename EventType>
	class SystemEventDispather
	{
	public:
		static SystemEventDispather *getInstance()
		{
			if (!m_Instance)
			{
				m_Instance = new SystemEventDispather();
#ifdef TT_FAST
				m_Instance->init();
#endif
			}
			return m_Instance;
		}

		static void kill()
		{
			delete m_Instance;
		}

	public:
		SystemEventDispather();
		~SystemEventDispather();

		void createListener(EventType event, void *owner, const std::function< void(SystemEvent<EventType> *) > &function);
		void releaseListener(EventType event, void *owner);
		void dispath(SystemEvent<EventType> *event);
		void dispath(EventType et, void *data);
		SystemEvent<EventType> *createEvent(EventType t, void *data);

	private:
		void init()
		{
			m_Listeners.resize(static_cast<size_t>(EventType::TT_Event_Counts));
		}

	private:
#ifdef TT_FAST
		std::vector<std::unordered_map< void *, std::function< void(SystemEvent<EventType> *)>>> m_Listeners;
#else
		std::unordered_map< EventType, std::unordered_map< void *, std::function< void(SystemEvent<EventType> *) > > > m_Listeners;
#endif
		//		std::map< EventType, std::map< void *, std::function< void (Event<EventType> *) > > > m_Listeners;
		//		std::list<Event<EventType> *> m_Recycle;

	private:
		static SystemEventDispather *m_Instance;
	};

	template<typename EventType> SystemEventDispather<EventType> * SystemEventDispather<EventType>::m_Instance = nullptr;

	template<typename EventType>
	SystemEventDispather<EventType>::SystemEventDispather()
	{

	}

	template<typename EventType>
	SystemEventDispather<EventType>::~SystemEventDispather()
	{

	}

	template<typename EventType>
	void SystemEventDispather<EventType>::dispath(SystemEvent<EventType> *event)
	{
#ifdef TT_FAST
		auto &set = m_Listeners[static_cast<size_t>(event->getType())];
#else
		auto &set = m_Listeners[event->getType()];
#endif
		auto it = set.begin();
		while (it != set.end())
		{
			it->second(event);
			++it;
		}
		event->recycle();
	}

	template<typename EventType>
	void tezcat::SystemEventDispather<EventType>::dispath(EventType et, void *data)
	{
		auto event = SystemEvent<EventType>::create(et, data);
#ifdef TT_FAST
		auto &set = m_Listeners[static_cast<size_t>(et)];
#else
		auto &set = m_Listeners[et];
#endif
//		auto &set = m_Listeners[et];
		auto it = set.begin();
		while (it != set.end())
		{
			it->second(event);
			++it;
		}
		event->recycle();
	}

	template<typename EventType>
	void SystemEventDispather<EventType>::createListener(EventType event, void *owner, const std::function< void(SystemEvent<EventType> *) > &function)
	{
#ifdef TT_FAST
		m_Listeners[static_cast<size_t>(event)].insert(std::make_pair(owner, function));
#else
		m_Listeners[event].insert(std::make_pair(owner, function));
#endif
	}

	template<typename EventType>
	void SystemEventDispather<EventType>::releaseListener(EventType event, void *owner)
	{
#ifdef TT_FAST
		auto &set = m_Listeners[static_cast<size_t>(event)];
#else
		auto &set = m_Listeners[event];
#endif
		auto it = set.find(owner);
		if (it != set.end())
		{
			set.erase(it);
		}
	}
}

//必须在最开始调用事件初始化
#define TT_Event_Init(EventType) tezcat::SystemEventDispather<EventType>::getInstance()
#define TT_Event_Create_Bind(EventType, SystemEvent, Function) tezcat::SystemEventDispather<EventType>::getInstance()->createListener(SystemEvent, this, std::bind(&Function, this, std::placeholders::_1))
#define TT_Event_Create(EventType, SystemEvent, Lambda) tezcat::SystemEventDispather<EventType>::getInstance()->createListener(SystemEvent, this, Lambda)
#define TT_Event_Release(EventType, SystemEvent) tezcat::SystemEventDispather<EventType>::getInstance()->releaseListener(SystemEvent, this)
#define TT_Event_Dispatch(EventType, SystemEvent, Data) tezcat::SystemEventDispather<EventType>::getInstance()->dispath(SystemEvent, Data)
#define TT_Event_Kill(EventType) tezcat::SystemEventDispather<EventType>::kill()