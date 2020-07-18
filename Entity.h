#pragma once

//******************************************************************
// 系统 : 实体组件系统
// 功能 : 实体功能
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-7-10
// 描述 : 实体组件,用于管理所有本实体下的组件
//******************************************************************

#include "Component.h"

#include <functional>
#include <unordered_set>

namespace tezcat
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		/**
		* Method:    initEntity
		* FullName:  Entity::initEntity
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void initEntity();

		/**
		* Method:    logic
		* FullName:  Entity::logic
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: float dt
		* Versions : V
		* Since    : V
		*/
		void logic();

		/**
		* Method:    getComponentManager
		* FullName:  Entity::getComponentManager
		* Access:    public
		* Returns:   tezcat::ComponentManager *
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		ComponentManager * getComponentManager()
		{
			return m_ComponentManager;
		}

		/**
		* Method:    setComponentManager
		* FullName:  Entity::setComponentManager
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: tezcat::ComponentManager * val
		* Versions : V
		* Since    : V
		*/
		void setComponentManager(ComponentManager * val) { m_ComponentManager = val; }

		/**
		* Method:    getIndex
		* FullName:  Entity::getIndex
		* Access:    public
		* Returns:   unsigned int
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		unsigned int getIndex() const { return m_Index; }

		/**
		* Method:    setIndex
		* FullName:  Entity::setIndex
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: unsigned int val
		* Versions : V
		* Since    : V
		*/
		void setIndex(unsigned int val) { m_Index = val; }

		/**
		* Method:    getRemove
		* FullName:  Entity::getRemove
		* Access:    public
		* Returns:   bool
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		bool isRemoved() const { return m_Remove; }

		/**
		* Method:    setRemove
		* FullName:  Entity::setRemove
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: bool val
		* Versions : V
		* Since    : V
		*/
		void setRemove(bool val) { m_Remove = val; }

		/**
		* Method:    addTag
		* FullName:  tezcat::Entity::addTag
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		void addTag(const std::string &tag);

		/**
		* Method:    addTags
		* FullName:  tezcat::Entity::addTags
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & tag_list
		* Versions : V
		* Since    : V
		*/
		void addTags(const std::string &tag_list);
		void addTags(const std::initializer_list<std::string> &tag_list);

		/**
		* Method:    removeTag
		* FullName:  tezcat::Entity::removeTag
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		void removeTag(const std::string &tag);

		/**
		* Method:    removeTags
		* FullName:  tezcat::Entity::removeTags
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & tag_list
		* Versions : V
		* Since    : V
		*/
		void removeTags(const std::string &tag_list);
		void removeTags(const std::initializer_list<std::string> &tag_list);

		/**
		* Method:    hasTag
		* FullName:  tezcat::Entity::hasTag
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		bool hasTag(const std::string &tag) { return m_Tags.find(tag) != m_Tags.end(); }

		/**
		* Method:    hasTags
		* FullName:  tezcat::Entity::hasTags
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string & tag_list
		* Versions : V
		* Since    : V
		*/
		bool hasTags(const std::string &tag_list);


		/**
		* Method:    getTags
		* FullName:  tezcat::Entity::getTags
		* Access:    public 
		* Returns:   const std::unordered_set<std::string> &
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		const std::unordered_set<std::string> &getTags() { return m_Tags; }


		/**
		* Method:    autoGroup
		* FullName:  tezcat::Entity::autoGroup
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void autoGroup();

	private:
		//************************************
		// Method:    clear
		// FullName:  tezcat::Entity::clear
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear();


	private:
		friend class EntityManager;

		unsigned int m_Index;
		bool m_Remove;
		bool m_AutoGroup;
		std::unordered_set<std::string> m_Tags;
		ComponentManager *m_ComponentManager;
	};


	
}