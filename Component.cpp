#include "Component.h"
#include "Entity.h"
namespace tezcat
{
	ComponentManager::ComponentManager(Entity *owner):
		m_Owner(owner)
	{

	}

	ComponentManager::~ComponentManager()
	{
		clear();
	}

	ComponentManager * ComponentManager::add(Component *com)
	{
		com->setOwner(m_Owner);
		std::cout << com->getClassName() << " RunLevel:" << com->getClassRunLevel() << std::endl;
#ifdef TT_COM_FAST
		switch (com->getClassRunLevel())
		{
			//加载静态组件
		case 0:
			m_StaticComponents[com->getTypeID()] = com;
			break;
			//加载动态组件
		default:
		{
				   auto index = com->getClassRunLevel() - 1;
				   if (index >= m_Index.size())
				   {
					   m_Index.resize(index + 1, nullptr);
					   m_Index[index] = new std::unordered_map<size_t, Component *>();
				   }

				   if (m_Index[index] == nullptr)
				   {
					   m_Index[index] = new std::unordered_map<size_t, Component *>();
				   }

				   (*m_Index[index])[com->getTypeID()] = com;
				   m_DynamicComponents[com->getTypeID()] = com;
				   break;
		}
		}
#else
		switch (com->getClassRunLevel())
		{
			//加载静态组件
		case 0:
			m_StaticComponents[com->getClassName()] = com;
			break;
			//加载动态组件
		default:
		{
				   auto index = com->getClassRunLevel() - 1;
				   if (index >= m_Index.size())
				   {
					   m_Index.resize(index + 1, nullptr);
					   m_Index[index] = new std::unordered_map<std::string, Component *>();
				   }

				   if (m_Index[index] == nullptr)
				   {
					   m_Index[index] = new std::unordered_map<std::string, Component *>();
				   }

				   (*m_Index[index])[com->getClassName()] = com;
				   m_DynamicComponents[com->getClassName()] = com;
				   break;
		}
		}
#endif



		com->initComponent();

		return this;
	}

	ComponentManager * ComponentManager::push(Component *com)
	{
// 		com->setOwner(m_Owner);
// 		switch (com->getClassRunLevel())
// 		{
// 			//加载静态组件
// 		case 0:
// 			m_StaticComponents[com->getClassName()] = com;
// 			break;
// 			//加载动态组件
// 		default:
// 		{
// 			auto index = com->getClassRunLevel() - 1;
// 			if (index >= m_Index.size())
// 			{
// 			   m_Index.resize(index + 1, nullptr);
// 			   m_Index[index] = new std::unordered_map<std::string, Component *>();
// 			}
// 			if (m_Index[index] == nullptr)
// 			{
// 			   m_Index[index] = new std::unordered_map<std::string, Component *>();
// 			}
// 			(*m_Index[index])[com->getClassName()] = com;
// 			m_DynamicComponents[com->getClassName()] = com;
// 			break;
// 		}
// 		}
// 		com->initComponent();
		this->add(com);

		com->needOtherComponent();

		return this;
	}

	void ComponentManager::logic()
	{
		for (unsigned int i = 0; i < m_Index.size(); i++)
		{
			auto level = m_Index[i];
			if (level)
			{
				for (auto &com : *level)
				{
					com.second->logic();
				}
			}
		}
	}
#ifdef TT_COM_FAST
	Component * ComponentManager::getDynamic(const size_t &type_id)
	{
		auto it = m_DynamicComponents.find(type_id);
		if (it != m_DynamicComponents.end())
		{
			return it->second;
		}

		return nullptr;
	}
#else
	Component * ComponentManager::getDynamic(const std::string &name)
	{
		auto it = m_DynamicComponents.find(name);
		if (it != m_DynamicComponents.end())
		{
			return it->second;
		}

		return nullptr;
	}
#endif




#ifdef TT_COM_FAST
	Component * ComponentManager::getStatic(const size_t &type_id)
	{
		auto it = m_StaticComponents.find(type_id);
		if (it != m_StaticComponents.end())
		{
			return it->second;
		}

		return nullptr;
	}
#else
	Component * ComponentManager::getStatic(const std::string &name)
	{
		auto it = m_StaticComponents.find(name);
		if (it != m_StaticComponents.end())
		{
			return it->second;
		}

		return nullptr;
	}
#endif
	
#ifdef TT_COM_FAST
	void ComponentManager::remove(const size_t &type_id)
	{
		Component *temp = nullptr;

		auto dit = m_DynamicComponents.find(type_id);
		if (dit != m_DynamicComponents.end())
		{
			auto com = dit->second;
			auto map = m_Index[com->getClassRunLevel()];
			map->erase(map->find(type_id));
			m_DynamicComponents.erase(dit);

			com->recycle();
			return;
		}

		auto sit = m_StaticComponents.find(type_id);
		if (sit != m_StaticComponents.end())
		{
			dit->second->recycle();
			m_StaticComponents.erase(sit);
			return;
		}

	}

#else
	void ComponentManager::remove(const std::string &name)
	{
		Component *temp = nullptr;

		auto dit = m_DynamicComponents.find(name);
		if (dit != m_DynamicComponents.end())
		{
			auto com = dit->second;
			auto map = m_Index[com->getClassRunLevel()];
			map->erase(map->find(name));
			m_DynamicComponents.erase(dit);

			com->recycle();
			return;
		}

		auto sit = m_StaticComponents.find(name);
		if (sit != m_StaticComponents.end())
		{
			dit->second->recycle();
			m_StaticComponents.erase(sit);
			return;
		}

	}

#endif

	void ComponentManager::packageAllComponents()
	{
		for (auto &com : m_DynamicComponents)
		{
			com.second->needOtherComponent();
		}

		for (auto &com : m_StaticComponents)
		{
			com.second->needOtherComponent();
		}
	}

	void ComponentManager::clear()
	{
		for (auto &com : m_DynamicComponents)
		{
			com.second->recycle();
		}
		m_DynamicComponents.clear();

		for (auto &com : m_StaticComponents)
		{
			com.second->recycle();
		}
		m_StaticComponents.clear();

		for (auto data : m_Index)
		{
			delete data;
		}
		m_Index.clear();
	}

	void ComponentManager::debug()
	{
		std::cout << "ComponentManager Debug Being----------------->" << std::endl;
		std::cout << "StaticComponents :" << std::endl;
		for (auto &s : m_StaticComponents)
		{
			std::cout << s.first << std::endl;
		}

		std::cout << "DynamicComponents :" << std::endl;
		for (auto &d : m_DynamicComponents)
		{
			std::cout << d.first << std::endl;
		}
		std::cout << "ComponentManager Debug End-----------------<" << std::endl;
	}


	ComponentManager * Component::getComponentManager()
	{
		return m_Owner->getComponentManager();
	}

}