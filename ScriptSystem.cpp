#include "ScriptSystem.h"
#include "ScriptParse.h"
#include "ScriptDebug.h"

#include "SystemIO.h"
#include "TTString.h"

#include <iostream>
#include <memory>


namespace tezcat
{
	ScriptParse * ScriptSystem::m_Parse = new ScriptParse();

	ScriptSystem::ScriptSystem() : m_NowID(0)
	{
		m_Parse->retain();
	}

	ScriptSystem::~ScriptSystem()
	{
		m_Parse->release();
		clear();
	}

	ScriptFile * ScriptSystem::getScript(const std::string &script_name)
	{
		ScriptDebug::setSystem(m_SystemInfo);

		auto it = m_Scripts.find(script_name);

		if (it != m_Scripts.end())
		{
			return it->second;
		}

#ifdef TT_Debug
		ScriptDebug::fileDebug(script_name);
#endif

		return ScriptFile::m_NullScriptFile;
	}

	void ScriptSystem::loadFile(const std::string &file)
	{
		m_SystemInfo = file;
		this->createFile(file);
	}

	bool ScriptSystem::loadListFile(const std::string &file)
	{
		m_SystemInfo = file;
		std::string temp = io::loadBinary2String(file);
		if (temp == "error")
		{
			ScriptDebug::systemDebug(m_SystemInfo);
			return false;
		}
		else
		{
			String::removeByFlag(temp, "\n\r\t");
			auto list = String::split2List(temp, ';');
			auto path = file.substr(0, file.find_last_of('/') + 1);

			//创建数据
			for (auto &str : list)
			{
				this->createFile(path + str);
			}

			this->debug();

			return true;
		}
	}

	bool ScriptSystem::loadListFileContent(const std::string &list_file, std::string list_content, const std::function<std::string(const std::string &)> &file_content)
	{
		m_SystemInfo = list_file;
		String::removeByFlag(list_content, "\n\r\t");
		auto list = String::split2List(list_content, ';');
		auto path = list_file.substr(0, list_file.find_last_of('/') + 1);

		//创建数据
		for (auto &str : list)
		{
			auto con = file_content(path + str);
			this->createFileWithContent(con, str);
		}

		this->debug();

		return true;
	}

	void ScriptSystem::debug()
	{
		std::cout << "======ScriptSystem Debug Begin======" << std::endl;

		for (auto &data : m_Scripts)
		{
			std::cout << data.first + " Script:" << std::endl;
			data.second->debug();
		}

		std::cout << "======ScriptSystem Debug End======" << std::endl;
	}

	void ScriptSystem::createFile(const std::string &file)
	{
		auto node = m_Parse->loadFile(file);
		auto it = m_Scripts.find(node->getFileName());
		if (it != m_Scripts.end())
		{
			delete it->second;
			m_Scripts.erase(it);
		}
		else
		{
			m_Scripts[node->getFileName()] = node;
		}
	}


	void ScriptSystem::createFileWithContent(std::string &content, const std::string &file_name)
	{
		auto node = m_Parse->loadData(content, file_name);
		auto it = m_Scripts.find(node->getFileName());
		if (it != m_Scripts.end())
		{
			delete it->second;
			m_Scripts.erase(it);
		}
		else
		{
			m_Scripts[node->getFileName()] = node;
		}
	}


	void ScriptSystem::clear()
	{
		for (auto p : m_Scripts)
		{
			delete p.second;
		}
	}
}