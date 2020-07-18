#include "ScriptDebug.h"
#include <cassert>
#include <iostream>

namespace tezcat
{
	std::string ScriptDebug::m_ParseInfo;
	std::string ScriptDebug::m_FileInfo;
	std::string ScriptDebug::m_SystemInfo;
	std::string ScriptDebug::m_ValueInfo;
	std::string ScriptDebug::m_ArrayInfo;
	std::string ScriptDebug::m_ClassInfo;
	std::string ScriptDebug::m_MapInfo;

	void ScriptDebug::systemDebug(const std::string &info)
	{
		std::cout << "System " << info << " Bug" << std::endl;
		m_SystemInfo = info;
		assert(false && "script system debug assert!");
	}

	void ScriptDebug::fileDebug(const std::string &info)
	{
		std::cout << "System " << m_SystemInfo << "->File " << info << " Bug" << std::endl;
		m_FileInfo = info;
		assert(false && "script file debug assert!");
	}

	void ScriptDebug::parseDebug(const std::string &info)
	{
		std::cout << info << std::endl;
		m_ParseInfo = info;
		assert(false && "script parse debug assert!");
	}

	void ScriptDebug::valueDebug(const std::string &info)
	{
		std::cout << "System " << m_SystemInfo << "->File " << m_FileInfo << "->Value " << info << " Bug" << std::endl;
		m_ValueInfo = info;
		assert(false && "script value debug assert!");
	}

	void ScriptDebug::classDebug(const std::string &info)
	{
		std::cout << "System " << m_SystemInfo << "->File " << m_FileInfo << "->Class " << info << " Bug" << std::endl;
		m_ClassInfo = info;
		assert(false && "script class debug assert!");
	}

	void ScriptDebug::mapDebug(const std::string &info)
	{
		std::cout << "System " << m_SystemInfo << "->File " << m_FileInfo << "->Map " << info << " Bug" << std::endl;
		m_MapInfo = info;
		assert(false && "script map debug assert!");
	}

	void ScriptDebug::arrayDebug(const std::string &info)
	{
		std::cout << "System " << m_SystemInfo << "->File " << m_FileInfo << "->Array " << info << " Bug" << std::endl;
		m_ArrayInfo = info;
		assert(false && "script array debug assert!");
	}
}

