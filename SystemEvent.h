#pragma once


#include <list>

namespace tezcat
{
	template<typename EventType>
	class SystemEventDispather;
	template<typename EventType>
	class SystemEvent
	{
	public:
		static SystemEvent *create(EventType t, void *data);

		template<typename data>
		typename std::enable_if<std::is_integral<data>::value || std::is_floating_point<data>::value || std::is_class<data>::value || std::is_void<data>::value, data *>::type getData() { return (data *)userData; }
		EventType getType() const { return type; }

	private:
		SystemEvent(EventType t, void *data):type(t), userData(data) {}
		~SystemEvent() {}

	public:
		static void clearEvents();
		void recycle();

	private:
		EventType type;
		void *userData;

	private:
		static std::list<SystemEvent<EventType> *> EventAllocation;
	};

	template<typename EventType>
	std::list<SystemEvent<EventType> *> tezcat::SystemEvent<EventType>::EventAllocation;

	template<typename EventType>
	void tezcat::SystemEvent<EventType>::recycle()
	{
		this->userData = nullptr;
		EventAllocation.push_back(this);
	}

	template<typename EventType>
	void tezcat::SystemEvent<EventType>::clearEvents()
	{
		auto it = EventAllocation.begin();
		while (it != EventAllocation.end())
		{
			double (*it);
			++it;
		}
		EventAllocation.clear();
	}

	template<typename EventType>
	SystemEvent<EventType> * SystemEvent<EventType>::create( EventType t, void *data )
	{
		if (EventAllocation.empty())
		{
			return new SystemEvent<EventType>(t, data);
		}
		else
		{
			auto e = EventAllocation.front();
			EventAllocation.pop_front();
			e->type = t;
			e->userData = data;
			return e;
		}
	}
}
