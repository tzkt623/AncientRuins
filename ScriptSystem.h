#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <list>
#include <functional>

#include "TValue.h"
#include "ScriptFile.h"
#include <memory>


//========================================================================
//
//	文件 : ScriptSystem.h
//	时间 : 2014-10-30
//	作者 : 特兹卡特(Tezcat)
//	功能 : 脚本系统
//
//	示例	:
//	file People;
//	var Name="You";
//	class Attribute
//	{
//		Strength=10,
//		Hp=10,
//	};
//
//	array Item
//	{
//		Gun,
//		Candy,
//		Water
//	};
//
//	map Effect
//	{
//		Strength=(2+@)*!Hp!+<2-8>,
//	};
//========================================================================

namespace tezcat
{
	class ScriptParse;
	class ScriptSystem
	{
	public:
		ScriptSystem();
		~ScriptSystem();

		//************************************
		// Method:    loadListFile
		// FullName:  tezcat::AttributeSystem::loadListFile
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & file
		// Info:	  加载列表文件
		//************************************
		bool loadListFile(const std::string &file);
		bool loadListFileContent(const std::string &list_file, std::string list_content, const std::function<std::string(const std::string &)> &file_content);

		//************************************
		// Method:    loadFile
		// FullName:  tezcat::ScriptSystem::loadFile
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & file
		//************************************
		void loadFile(const std::string &file);

		//************************************
		// Method:    getScript
		// FullName:  tezcat::ScriptSystem::getScript
		// Access:    public 
		// Returns:   ScriptNode *
		// Qualifier:
		// Parameter: const std::string & script_name
		//************************************
		ScriptFile *getScript(const std::string &script_name);

		//************************************
		// Method:    getScripts
		// FullName:  tezcat::ScriptSystem::getScripts
		// Access:    public 
		// Returns:   std::map<std::string, ScriptNode *> &
		// Qualifier:
		//************************************
		std::map<std::string, ScriptFile *> &getScripts() { return m_Scripts; }


	public:
		//************************************
		// Method:    loadMapData
		// FullName:  tezcat::ScriptFile::loadMapData
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: ScriptFile * data
		// Parameter: const std::string & name
		// Parameter: PropertyMap & map
		//************************************
		static void loadMapData(ScriptFile *data, const std::string &name, PropertyMap &map)
		{
			auto *data_class = data->getClass(name);
			map.clear();
			map.reserve(data_class->size());
			for (auto d : *data_class)
			{
				map[d.first] = d.second;
			}
		}

		//************************************
		// Method:    loadArrayData
		// FullName:  tezcat::ScriptSystem::loadArrayData
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: ScriptFile * data
		// Parameter: const std::string & name
		// Parameter: PropertyArray & array
		//************************************
		static void loadArrayData(ScriptFile *data, const std::string &name, PropertyArray &array)
		{
			auto *data_array = data->getArray(name);
			array.clear();
			array.reserve(data_array->size());
			for (auto d : *data_array)
			{
				array.push_back(d);
			}
		}

	private:
		//************************************
		// Method:    createAttribute
		// FullName:  tezcat::ScriptSystem::createAttribute
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & file
		//************************************
		void createFile(const std::string &file);
		void createFileWithContent(std::string &content, const std::string &file_name);

		//************************************
		// Method:    clear
		// FullName:  tezcat::ScriptSystem::clear
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear();

		//************************************
		// Method:    debug
		// FullName:  tezcat::ScriptSystem::debug
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void debug();

	private:
		static ScriptParse *m_Parse;
		std::map<std::string, ScriptFile *> m_Scripts;
		std::string m_SystemInfo;
		size_t m_NowID;
	};
}