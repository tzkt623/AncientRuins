#pragma once

#include "RunTimeSystem.h"

//=============================================================
// 文件 : RunTimeInfo.h
// 功能 : 运行时类型信息
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-11-13
//=============================================================

namespace tezcat
{
	class RunTimeInfo
	{
	public:

		RunTimeInfo::~RunTimeInfo()
		{

		}

		RunTimeInfo::RunTimeInfo(unsigned int classRunLevel, const std::string &name) :
			m_ClassRunLevel(classRunLevel), m_ClassName(name)
		{
			RunTimeSystem::getInstance()->giveID(name);
			RunTimeSystem::getInstance()->giveTypeID(m_TypeID);
		}

		//************************************
		// Method:    getClassID
		// FullName:  tezcat::RunTimeInfo<T>::getClassID
		// Access:    public 
		// Returns:   unsigned int
		// Qualifier: const
		// Info:	  class id
		//************************************
		unsigned int getClassID() const { return m_ClassID; }

		//************************************
		// Method:    getClassRunLevel
		// FullName:  tezcat::RunTimeInfo<T>::getClassRunLevel
		// Access:    public 
		// Returns:   unsigned int
		// Qualifier: const
		// Info:	  class runtime level
		//************************************
		unsigned int getClassRunLevel() const { return m_ClassRunLevel; }

		//************************************
		// Method:    getClassName
		// FullName:  tezcat::RunTimeInfo<T>::getClassName
		// Access:    public 
		// Returns:   std::string
		// Qualifier: const
		// Info:	  class name
		//************************************
		std::string getClassName() const { return m_ClassName; }

		//************************************
		// Method:    setClassName
		// FullName:  tezcat::RunTimeInfo<T>::setClassName
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
		void setClassName(const std::string &name) { m_ClassName = name; }

		//************************************
		// Method:    getTypeID
		// FullName:  tezcat::RunTimeInfo::getTypeID
		// Access:    public 
		// Returns:   size_t
		// Qualifier: const
		//************************************
		size_t getTypeID() const { return m_TypeID; }

	private:
		size_t m_TypeID;
		unsigned int m_ClassID;
		unsigned int m_ClassRunLevel;
		std::string m_ClassName;
	};
}