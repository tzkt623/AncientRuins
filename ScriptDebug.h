#pragma once

#include <string>

namespace tezcat
{
	class ScriptDebug
	{
	public:

		static void setSystem(const std::string &info) { m_SystemInfo == info; }

		static void systemDebug(const std::string &info);

		static void fileDebug(const std::string &info);

		static void valueDebug(const std::string &info);

		static void classDebug(const std::string &info);

		static void mapDebug(const std::string &info);

		static void arrayDebug(const std::string &info);

		static void parseDebug(const std::string &info);

	private:
		static std::string m_SystemInfo;
		static std::string m_FileInfo;
		static std::string m_ValueInfo;
		static std::string m_MapInfo;
		static std::string m_ClassInfo;
		static std::string m_ArrayInfo;
		static std::string m_ParseInfo;
	};


}
