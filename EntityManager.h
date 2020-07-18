#pragma once

#include <list>
#include <vector>
#include <functional>
#include "Entity.h"

namespace tezcat
{
	class Entity;
	class EntityManager
	{
	public:

		/**
		* Method:    EntityManager
		* FullName:  EntityManager::EntityManager
		* Access:    public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		EntityManager();

		/**
		* Method:    ~EntityManager
		* FullName:  EntityManager::~EntityManager
		* Access:    public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		~EntityManager();

		/**
		* Method:    createEntity
		* FullName:  EntityManager::createEntity
		* Access:    public
		* Returns:   Entity *
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		Entity *createEntity();

		/**
		* Method:    remove
		* FullName:  EntityManager::remove
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * e
		* Versions : V
		* Since    : V
		*/
		void remove(Entity *e);

		/**
		* Method:    updata
		* FullName:  EntityManager::updata
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: float dt
		* Versions : V
		* Since    : V
		*/
		virtual void logic();

		/**
		* Method:    foreach
		* FullName:  EntityManager::foreach
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: const std::function<void
		* Parameter: Entity * entity
		* Parameter: > & function
		* Versions : V
		* Since    : V
		*/
		void foreachHas(const std::function<void(Entity *entity)> &function);

	protected:
		std::vector<Entity *> m_Entities;
		std::list<Entity *> m_Recycle;

		unsigned int m_NowIndex;
	};

}