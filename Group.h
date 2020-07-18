#pragma once

#include <unordered_map>
#include <unordered_set>

namespace tezcat
{
	class Entity;
	class Group
	{
	public:
		//************************************
		// Method:    getInstance
		// FullName:  tezcat::Group::getInstance
		// Access:    public static 
		// Returns:   Group *
		// Qualifier:
		//************************************
		static Group *getInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new Group();
			}
			return m_Instance;
		}

		//************************************
		// Method:    deleteGroup
		// FullName:  tezcat::Group::deleteGroup
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		//************************************
		static void deleteGroup()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
			}
		}

		~Group();

		/**
		* Method:    addGroup
		* FullName:  tezcat::Group::addGroup
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * entity
		* Versions : V
		* Since    : V
		*/
		void addGroup(Entity *entity);

		/**
		* Method:    addGroup
		* FullName:  tezcat::Group::addGroup
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * entity
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		void addGroup(Entity *entity, const std::string &tag);

		/**
		* Method:    removeGroup
		* FullName:  tezcat::Group::removeGroup
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * entity
		* Versions : V
		* Since    : V
		*/
		void removeGroup(Entity *entity);

		/**
		* Method:    removeGroup
		* FullName:  tezcat::Group::removeGroup
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * entity
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		void removeGroup(Entity *entity, const std::string &tag);

		/**
		* Method:    getGroup
		* FullName:  tezcat::Group::getGroup
		* Access:    public 
		* Returns:   std::unordered_set<Entity *> &
		* Qualifier:
		* Parameter: const std::string & tag
		* Versions : V
		* Since    : V
		*/
		std::unordered_set<Entity *> &getGroup(const std::string &tag) { return m_Groups[tag]; }

		/**
		* Method:    clear
		* FullName:  tezcat::Group::clear
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void clear();

		/**
		* Method:    debug
		* FullName:  tezcat::Group::debug
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void debug();

	private:
		Group();

	private:
		std::unordered_map<std::string, std::unordered_set<Entity *>> m_Groups;
		static Group *m_Instance;
	};
}