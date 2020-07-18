#pragma once

//******************************************************************
// 系统 : 实体组件系统
// 功能 : 组件功能
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-7-10
// 描述 : 组件的抽象接口,分为动态组件和静态组件
//******************************************************************

#include "RunTimeClass.h"
//#include "ClassTypeID.h"
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <assert.h>
#include <vector>
#include <type_traits>

namespace tezcat
{
#define TT_COM_FAST
	// 	enum class ComponentType
	// 	{
	// 		Error,
	// 		Static,
	// 		Dynamic,
	// 	};

	class Entity;
	class ComponentManager;
	class NullComponent{};
	class Component : public RunTimeClass
	{
	public:
		/**
		* Method:    ComponentX
		* FullName:  ComponentX::ComponentX
		* Access:    public
		* Returns:
		* Qualifier: : m_ComponentType(type)
		* Parameter: const Type type
		* Versions : V
		* Since    : V
		*/
		Component() {}

		/**
		* Method:    ~ComponentX
		* FullName:  ComponentX::~ComponentX
		* Access:    virtual public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		virtual ~Component() {}

		//************************************
		// Method:    initComponent
		// FullName:  tezcat::Component::initComponent
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Info: 此函数优先于needOtherComponent()调用, 用于初始化, 重写即可, 不要手动去调用他, 否则会出错!!!
		//************************************
		virtual void initComponent() = 0;

		/**
		* Method:    needOtherComponent
		* FullName:  ComponentX::needOtherComponent
		* Access:    virtual public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		* Info     : 此函数后于initComponent()调用, 用于组装本组件, 重写即可, 不要手动去调用他, 否则会出错!!!
		*/
		virtual void needOtherComponent() = 0;

		/**
		* Method:    getComponentName
		* FullName:  ComponentX::getComponentName
		* Access:    virtual public
		* Returns:   const std::string
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		//		virtual const std::string getComponentName() const = 0;

		/**
		* Method:    getStaticComponentName
		* FullName:  ComponentX::getStaticComponentName
		* Access:    public static
		* Returns:   const std::string
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		//		static const std::string getStaticComponentName() { return "Error"; }

		/**
		* Method:    getOwner
		* FullName:  ComponentX::getOwner
		* Access:    public
		* Returns:   Entity *
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		Entity * getOwner() const { return m_Owner; }

		/**
		* Method:    setOwner
		* FullName:  ComponentX::setOwner
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: Entity * val
		* Versions : V
		* Since    : V
		*/
		void setOwner(Entity * val) { m_Owner = val; }

		//************************************
		// Method:    getComponentManager
		// FullName:  tezcat::Component::getComponentManager
		// Access:    public 
		// Returns:   ComponentManager *
		// Qualifier:
		//************************************
		ComponentManager *getComponentManager();

		/**
		* Method:    getComponentType
		* FullName:  ComponentX::getComponentType
		* Access:    virtual public
		* Returns:   const ComponentXType
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		//		virtual const ComponentType getComponentType() const = 0;

		/**
		* Method:    getStaticComponentType
		* FullName:  ComponentX::getStaticComponentType
		* Access:    public static
		* Returns:   ComponentXType
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		//		static ComponentType getStaticComponentType() { return ComponentType::Error; }


		/**
		* Method:    getPriority
		* FullName:  tezcat::Component::getPriority
		* Access:    virtual public
		* Returns:   unsigned int
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		//		virtual unsigned int getPriority() const = 0;

		/**
		* Method:    getStaticPriority
		* FullName:  tezcat::Component::getStaticPriority
		* Access:    public static
		* Returns:   unsigned int
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		//		static unsigned int getStaticPriority() { return 0; }

		/**
		* Method:    release
		* FullName:  ComponentX::release
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		virtual void recycle() { delete this; }

		//************************************
		// Method:    logic
		// FullName:  tezcat::Component::logic
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void logic() {}

	protected:
		Entity *m_Owner;
	};

#if 0
	class DynamicComponent : public Component
	{
	public:
		/**
		* Method:    DynamicComponent
		* FullName:  DynamicComponent::DynamicComponent
		* Access:    public
		* Returns:
		* Qualifier: : ComponentX(ComponentX::Type::Dynamic)
		* Versions : V
		* Since    : V
		*/
		DynamicComponent() {}

		/**
		* Method:    ~DynamicComponent
		* FullName:  DynamicComponent::~DynamicComponent
		* Access:    virtual public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		virtual ~DynamicComponent() {}

		/**
		* Method:    logic
		* FullName:  DynamicComponent::logic
		* Access:    virtual public
		* Returns:   void
		* Qualifier:
		* Parameter: float dt
		* Versions : V
		* Since    : V
		*/
		virtual void logic() = 0;
	private:

	};

	class StaticComponent : public Component
	{
	public:
		/**
		* Method:    StaticComponent
		* FullName:  StaticComponent::StaticComponent
		* Access:    public
		* Returns:
		* Qualifier: : ComponentX(ComponentX::Type::Static)
		* Versions : V
		* Since    : V
		*/
		StaticComponent() {}

		/**
		* Method:    ~StaticComponent
		* FullName:  StaticComponent::~StaticComponent
		* Access:    virtual public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		virtual ~StaticComponent() {}
	};
#endif

	//
	//
	//
	class ComponentManager
	{
	public:
		ComponentManager(Entity *owner);

		/**
		* Method:    ~ComponentManager
		* FullName:  ComponentManager::~ComponentManager
		* Access:    public
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		~ComponentManager();

		/**
		* Method:    add
		* FullName:  ComponentManager::add
		* Access:    public
		* Returns:   ComponentManager *
		* Qualifier:
		* Parameter: ComponentX * com
		* Versions : V
		* Since    : V
		*/
		ComponentManager *add(Component *com);

		/**
		* Method:    push
		* FullName:  ComponentManager::push
		* Access:    public
		* Returns:   ComponentManager *
		* Qualifier:
		* Parameter: ComponentX * com
		* Versions : V
		* Since    : V
		* Info     : 放入一个组件,会执行needComponent函数,动态添加组件时使用
		*/
		ComponentManager *push(Component *com);

		/**
		* Method:    get
		* FullName:  ComponentManager::get
		* Access:    public
		* Returns:   Com *
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		template<typename Com>
		typename std::enable_if<std::is_base_of<Component, Com>::value && std::is_class<Com>::value, Com>::type *get()
		{
			Component *com = nullptr;
#ifdef TT_COM_FAST
			switch (Com::getRunTimeInfo()->getClassRunLevel())
			{
				//静态组件
			case 0:
				com = this->getStatic(Com::getRunTimeInfo()->getTypeID());
				break;
				//动态组件
			default:
				com = this->getDynamic(Com::getRunTimeInfo()->getTypeID());
				break;
			}
#else
			switch (Com::getRunTimeInfo()->getClassRunLevel())
			{
				//静态组件
			case 0:
				com = this->getStatic(Com::getRunTimeInfo()->getClassName());
				break;
				//动态组件
			default:
				com = this->getDynamic(Com::getRunTimeInfo()->getClassName());
				break;
			}
#endif
			return static_cast<Com *>(com);
		}

		/**
		* Method:    remove
		* FullName:  ComponentManager::remove
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & name
		* Versions : V
		* Since    : V
		*/
#ifdef TT_COM_FAST
		void remove(const size_t &type_id);
#else
		void remove(const std::string &name);
#endif
		template<typename Com>
		typename std::enable_if<std::is_base_of<Component, Com>::value && std::is_class<Com>::value, void>::type remove()
		{
			auto type_id = Com::getRunTimeInfo()->getTypeID();

			switch (Com::getRunTimeInfo()->getClassRunLevel())
			{
				//静态组件
			case 0:
				auto sit = m_StaticComponents.find(type_id);
				if (sit != m_StaticComponents.end())
				{
					sit->second->recycle();
					m_StaticComponents.erase(sit);
				}
				break;
				//动态组件
			default:
				auto dit = m_DynamicComponents.find(type_id);
				if (dit != m_DynamicComponents.end())
				{
					auto com = dit->second;
					auto map = m_Index[com->getClassRunLevel()];
					map->erase(map->find(type_id));
					m_DynamicComponents.erase(dit);

					com->recycle();
				}
				break;
			}
		}

		/**
		* Method:    logic
		* FullName:  ComponentManager::logic
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Parameter: float dt
		* Versions : V
		* Since    : V
		*/
		void logic();

		/**
		* Method:    packageAllComponents
		* FullName:  ComponentManager::packageAllComponents
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void packageAllComponents();

		//************************************
		// Method:    detach
		// FullName:  tezcat::ComponentManager::detach
		// Access:    public 
		// Returns:   Com *
		// Qualifier:
		//************************************
		template<typename Com>
		typename std::enable_if<std::is_base_of<Component, Com>::value && std::is_class<Com>::value, Com>::type *detach()
		{
			Com *com = nullptr;
#ifdef TT_COM_FAST
			auto type_id = Com::getRunTimeInfo()->getTypeID();
			switch (Com::getRunTimeInfo()->getClassRunLevel())
			{
				//静态组件
			case 0:
			{
					  auto sit = m_StaticComponents.find(type_id);
					  if (sit != m_StaticComponents.end())
					  {
						  com = sit->second;
						  m_StaticComponents.erase(sit);
					  }
					  break;
			}
				//动态组件
			default:
			{
					   auto dit = m_DynamicComponents.find(type_id);
					   if (dit != m_DynamicComponents.end())
					   {
						   com = dit->second;
						   auto map = m_Index[com->getClassRunLevel() - 1];
						   map->erase(map->find(type_id));
						   m_DynamicComponents.erase(dit);
					   }
					   break;
			}
			}
#else
			std::string name = Com::getRunTimeInfo()->getClassName();
			switch (Com::getRunTimeInfo()->getClassRunLevel())
			{
				//静态组件
			case 0:
			{
					  auto sit = m_StaticComponents.find(name);
					  if (sit != m_StaticComponents.end())
					  {
						  com = sit->second;
						  m_StaticComponents.erase(sit);
					  }
					  break;
			}
				//动态组件
			default:
			{
					   auto dit = m_DynamicComponents.find(name);
					   if (dit != m_DynamicComponents.end())
					   {
						   com = dit->second;
						   auto map = m_Index[com->getClassRunLevel() - 1];
						   map->erase(map->find(name));
						   m_DynamicComponents.erase(dit);
					   }
					   break;
			}
			}
#endif
			return com;
		}

		/**
		* Method:    clear
		* FullName:  ComponentManager::clear
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void clear();

		//************************************
		// Method:    debug
		// FullName:  tezcat::ComponentManager::debug
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void debug();

#ifdef TT_COM_FAST
		std::unordered_map<size_t, Component *> &getStaticComponents() { return m_StaticComponents; }
		std::unordered_map<size_t, Component *> &getDynamicComponents() { return m_DynamicComponents; }
#else
		std::unordered_map<std::string, Component *> &getStaticComponents() { return m_StaticComponents; }
		std::unordered_map<std::string, Component *> &getDynamicComponents() { return m_DynamicComponents; }
#endif

	private:
		/**
		* Method:    getDynamic
		* FullName:  ComponentManager::getDynamic
		* Access:    private
		* Returns:   ComponentX *
		* Qualifier:
		* Parameter: const std::string & name
		* Versions : V
		* Since    : V
		*/
#ifdef TT_COM_FAST
		Component *getDynamic(const size_t &type_id);
#else
		Component *getDynamic(const std::string &name);

#endif

		/**
		* Method:    getStatic
		* FullName:  ComponentManager::getStatic
		* Access:    private
		* Returns:   ComponentX *
		* Qualifier:
		* Parameter: const std::string & name
		* Versions : V
		* Since    : V
		*/
#ifdef TT_COM_FAST
		Component *getStatic(const size_t &type_id);
#else
		Component *getStatic(const std::string &name);
#endif


	private:
#ifdef TT_COM_FAST
		std::unordered_map<size_t, Component *> m_DynamicComponents;
		std::unordered_map<size_t, Component *> m_StaticComponents;
		std::vector<std::unordered_map<size_t, Component *> *> m_Index;
#else
		std::unordered_map<std::string, Component *> m_DynamicComponents;
		std::unordered_map<std::string, Component *> m_StaticComponents;
		std::vector<std::unordered_map<std::string, Component *> *> m_Index;
#endif // TT_FAST


		Entity *m_Owner;


	private:
	};

}
/*
#define TT_Declare_ComponentName()\
public:\
virtual const std::string getComponentName() const { return m_ComponentName; }\
static const std::string getStaticComponentName() { return m_ComponentName; }\
virtual const tezcat::ComponentType getComponentType() const { return m_ComponentType; }\
static tezcat::ComponentType getStaticComponentType() { return m_ComponentType; }\
virtual unsigned int getPriority() const { return m_RunPriority; } \
static unsigned int getStaticPriority() { return m_RunPriority; }\
private:\
static std::string m_ComponentName; \
static tezcat::ComponentType m_ComponentType; \
static unsigned int m_RunPriority;

#define TT_Implementation_ComponentName(Com, Type, Priority)\
std::string Com::m_ComponentName = #Com; \
tezcat::ComponentType Com::m_ComponentType = Type; \
unsigned int Com::m_RunPriority = Priority;

#define TT_Implementation_ComponentStatic(Com) TT_Implementation_ComponentName(Com, tezcat::ComponentType::Static, 0)
#define TT_Implementation_ComponentDynamic(Com, Priority) TT_Implementation_ComponentName(Com, tezcat::ComponentType::Dynamic, Priority)
}
*/