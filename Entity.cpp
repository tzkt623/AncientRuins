#include "Entity.h"
#include "Group.h"
#include "TTString.h"

namespace tezcat
{
	Entity::Entity() :
		m_ComponentManager(new ComponentManager(this)),
		m_Remove(false),
		m_AutoGroup(false)
	{

	}

	Entity::~Entity()
	{
		delete m_ComponentManager;
	}


	void Entity::initEntity()
	{

	}

	void Entity::logic()
	{
		m_ComponentManager->logic();
	}

	void Entity::clear()
	{
		m_Remove = false;

		m_ComponentManager->clear();

		if (m_AutoGroup)
		{
			m_AutoGroup = false;
			Group::getInstance()->removeGroup(this);
		}
	}

	bool Entity::hasTags(const std::string &tag_list)
	{
		auto list = String::split2List(tag_list, ',');
		auto it = list.begin();
		while (it != list.end())
		{
			if (m_Tags.find((*it)) == m_Tags.end())
			{
				return false;
			}

			++it;
		}

// 		std::string build = tag_list;
// 		std::string temp;
// 		while (!build.empty())
// 		{
// 			auto pos1 = build.find_first_of(",");
// 			if (pos1 == std::string::npos && build.empty())
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				if (pos1 == std::string::npos)
// 				{
// 					temp = build;
// 					build.clear();
// 				}
// 				else
// 				{
// 					temp = build.substr(0, pos1);
// 					build.erase(0, pos1 + 1);
// 				}
// 
// 				
// 				if (m_Tags.find(temp) == m_Tags.end())
// 				{
// 					return false;
// 				}
// 			}
// 		}

		return true;
	}

	void Entity::addTag(const std::string &tag)
	{
		if (m_Tags.find(tag) == m_Tags.end())
		{
			m_Tags.insert(tag);
			if (m_AutoGroup)
			{
				Group::getInstance()->addGroup(this, tag);
			}
		}
	}

	void Entity::addTags(const std::string &tag_list)
	{
		auto list = String::split2List(tag_list, ',');
		while (list.empty())
		{
			this->addTag(list.front());
			list.pop_front();
		}

// 		std::string build = tag_list;
// 		std::string temp;
// 		while (!build.empty())
// 		{
// 			auto pos1 = build.find_first_of(",");
// 			if (pos1 == std::string::npos && build.empty())
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				if (pos1 == std::string::npos)
// 				{
// 					temp = build;
// 					build.clear();
// 				}
// 				else
// 				{
// 					temp = build.substr(0, pos1);
// 					build.erase(0, pos1 + 1);
// 				}
// 
// 				addTag(temp);
// 			}
// 		}

	}

	void Entity::addTags(const std::initializer_list<std::string> &tag_list)
	{
		auto it = tag_list.begin();
		while (it != tag_list.end())
		{
			this->addTag(*it);
			++it;
		}
	}

	void Entity::removeTag(const std::string &tag)
	{
		m_Tags.erase(tag);
		if (m_AutoGroup)
		{
			Group::getInstance()->removeGroup(this, tag);
		}
	}

	void Entity::removeTags(const std::string &tag_list)
	{
		auto list = String::split2List(tag_list, ',');
		while (list.empty())
		{
			this->removeTag(list.front());
			list.pop_front();
		}

// 		std::string build = tag_list;
// 		std::string temp;
// 		while (!build.empty())
// 		{
// 			auto pos1 = build.find_first_of(",");
// 			if (pos1 == std::string::npos && build.empty())
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				if (pos1 == std::string::npos)
// 				{
// 					temp = build;
// 					build.clear();
// 				}
// 				else
// 				{
// 					temp = build.substr(0, pos1);
// 					build.erase(0, pos1 + 1);
// 				}
// 
// 				removeTag(temp);
// 			}
// 		}
	}

	void Entity::removeTags(const std::initializer_list<std::string> &tag_list)
	{
		auto it = tag_list.begin();
		while (it != tag_list.end())
		{
			this->removeTag(*it);
			++it;
		}
	}

	void Entity::autoGroup()
	{
		if (m_AutoGroup == false)
		{
			m_AutoGroup = true;
			Group::getInstance()->addGroup(this);
		}
	}

}