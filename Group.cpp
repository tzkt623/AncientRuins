#include "Group.h"
#include "Entity.h"
#include <iostream>

namespace tezcat
{
	Group *Group::m_Instance = nullptr;

	Group::Group()
	{
	}

	Group::~Group()
	{
	}

	void Group::addGroup(Entity *entity)
	{
		if (entity->getTags().empty())
		{
			return;
		}

		auto &temp = entity->getTags();
		for (auto tag : temp)
		{
			m_Groups[tag].insert(entity);
			std::cout << "Group <" << tag << "> Add " << entity << std::endl;
		}
	}

	void Group::addGroup(Entity *entity, const std::string &tag)
	{
		m_Groups[tag].insert(entity);
		std::cout << "Group <" << tag << "> Add " << entity << std::endl;
	}

	void Group::removeGroup(Entity *entity)
	{
		auto &temp = entity->getTags();
		for (auto tag : temp)
		{
			m_Groups[tag].erase(entity);
			std::cout << "Group <" << tag << "> Remove " << entity << std::endl;
		}
	}

	void Group::removeGroup(Entity *entity, const std::string &tag)
	{
		auto it = m_Groups.find(tag);
		if (it != m_Groups.end())
		{
			it->second.erase(entity);
			std::cout << "Group <" << tag << "> Remove " << entity << std::endl;
		}
	}

	void Group::clear()
	{
		m_Groups.clear();
	}

	void Group::debug()
	{
		for (auto &group : m_Groups)
		{
			std::cout << "Group <" << group.first << "> has entity: " << group.second.size() << std::endl;
		}
	}

}