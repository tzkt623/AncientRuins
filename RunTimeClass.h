#pragma once

#include "RunTimeInfo.h"

//=============================================================
// 文件 : RunTimeClass.h
// 功能 : 运行时包装类
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-11-13
// 参数 : 自身,父类,类ID,类运行等级(为0为静态类,大于0为动态类,数值越大,优先级越低)
//=============================================================

namespace tezcat
{
//	template<typename Self, class BaseClass, unsigned int ClassRunLevel>
//	template<typename T>
	class RunTimeClass// : public BaseClass
	{
	public:
		virtual ~RunTimeClass() {}

		//************************************
		// Method:    getRunTimeInfo
		// FullName:  tezcat::RunTimeClass<Self, BaseClass, ClassID, ClassRunLevel>::getRunTimeInfo
		// Access:    public static 
		// Returns:   RunTimeInfo<Self> *
		// Qualifier:
		// Info:	  在明确类型信息的情况下,取得运行时类型信息
		//************************************
//		static RunTimeInfo *getRunTimeInfo() { return &m_RunTimeInfo; }

		//************************************
		// Method:    getClassName
		// FullName:  tezcat::RunTimeClass<Self, BaseClass, ClassID, ClassRunLevel>::getClassName
		// Access:    virtual public 
		// Returns:   std::string
		// Qualifier:
		// Info:	  取得运行时类名称
		//************************************
		virtual std::string getClassName() = 0;

		//************************************
		// Method:    getClassID
		// FullName:  tezcat::RunTimeClass<Self, BaseClass, ClassID, ClassRunLevel>::getClassID
		// Access:    virtual public 
		// Returns:   unsigned int
		// Qualifier:
		// Info:	  取得运行时类ID
		//************************************
		virtual unsigned int getClassID() = 0;

		//************************************
		// Method:    getClassRunLevel
		// FullName:  tezcat::RunTimeClass<Self, BaseClass, ClassID, ClassRunLevel>::getClassRunLevel
		// Access:    virtual public 
		// Returns:   unsigned int
		// Qualifier:
		// Info:	  取得运行时类优先级
		//************************************
		virtual unsigned int getClassRunLevel() = 0;

		//************************************
		// Method:    getTypeID
		// FullName:  tezcat::RunTimeClass::getTypeID
		// Access:    virtual public 
		// Returns:   size_t
		// Qualifier:
		//************************************
		virtual size_t getTypeID() = 0;
	};

	// 	template<typename Self, class BaseClass, unsigned int ClassRunLevel>
	// 	RunTimeInfo<Self> tezcat::RunTimeClass<Self, BaseClass, ClassRunLevel>::m_RunTimeInfo(ClassRunLevel, typeid(Self).name());
#define TT_DECLARE_RTTI()\
public:\
	static tezcat::RunTimeInfo *getRunTimeInfo() { return &m_RunTimeInfo; }\
	virtual std::string getClassName()\
	{\
	return m_RunTimeInfo.getClassName(); \
	}\
	virtual unsigned int getClassRunLevel()\
	{\
	return m_RunTimeInfo.getClassRunLevel(); \
	}\
	virtual unsigned int getClassID()\
	{\
	return m_RunTimeInfo.getClassID(); \
	}\
	virtual size_t getTypeID()\
	{\
	return m_RunTimeInfo.getTypeID();\
	}\
private:\
	static tezcat::RunTimeInfo m_RunTimeInfo;

#define TT_IMPLEMENT_RTTI(Self, ClassRunLevel) tezcat::RunTimeInfo Self::m_RunTimeInfo(ClassRunLevel, #Self)

}

