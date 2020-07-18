#include "EntityManager.h"



namespace tezcat
{
	//
	EntityManager::EntityManager() :
		m_NowIndex(0)
	{
	}

	EntityManager::~EntityManager()
	{

	}

	void EntityManager::logic()
	{
		auto it = m_Entities.begin();
		while (it != m_Entities.end())
		{
			if (!(*it)->isRemoved())
			{
				(*it)->logic();
			}
			++it;
		}
	}

	void EntityManager::foreachHas(const std::function<void(Entity *entity)> &function)
	{
		auto it = m_Entities.begin();
		while (it != m_Entities.end())
		{
			if ((*it) != nullptr)
			{
				function(*it);
			}
			++it;
		}
	}

	Entity * EntityManager::createEntity()
	{
		Entity *e = nullptr;

		if (m_Recycle.empty())
		{
			e = new Entity();
			e->initEntity();
			e->setIndex(m_NowIndex++);
			m_Entities.push_back(e);
			return e;
		}
		else
		{
			e = m_Recycle.front();
			m_Recycle.pop_back();
			m_Entities[e->getIndex()] = e;
		}

		return e;
	}

	void EntityManager::remove(Entity *e)
	{
		m_Entities[e->getIndex()] = nullptr;
		m_Recycle.push_back(e);
		e->clear();
	}
}

