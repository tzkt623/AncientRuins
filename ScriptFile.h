#pragma once

#include <map>
#include <string>
#include "TValue.h"
#include <assert.h>
#include <functional>

//========================================================================
//
//	文件 : ScriptFile.h
//	时间 : 2014-10-30
//	作者 : 特兹卡特(Tezcat)
//	功能 : 单个脚本文件的数据分类存储
//
//========================================================================

namespace tezcat
{
	class ScriptFile
	{
#ifdef TT_Debug
		enum class Tpye
		{
			Var,
			Class,
			Map,
			Array
		};

		Tpye m_Type;
#endif


	public:
		ScriptFile();
		ScriptFile(size_t id);
		~ScriptFile();

		//************************************
		// Method:    map
		// FullName:  tezcat::ScriptNode::map
		// Access:    public 
		// Returns:   ScriptNode *
		// Qualifier:
		// Parameter: std::string map_name
		// Parameter: std::string attribute
		// Parameter: std::string rule
		//************************************
		ScriptFile *setMap(std::string map_name, std::string attribute, std::string rule);
		void setNullMap(std::string map_name)
		{
			m_Maps[map_name].clear();
		}

		//************************************
		// Method:    getMap
		// FullName:  tezcat::ScriptNode::getMap
		// Access:    public 
		// Returns:   std::map<std::string, std::string> *
		// Qualifier:
		// Parameter: const std::string & map_name
		//************************************
		std::map<std::string, TValue> *getMap(const std::string &map_name);
// 		void pushMap(const std::string &map_name);
// 		TValue &getValueInMap(const std::string &key);
// 		void foreachMap(const std::function<void(const std::string &, const TValue &)> &function)
// 		{
// 			for (auto d : *m_MapsCache)
// 			{
// 				function(d.first, d.second);
// 			}
// 		}

		//************************************
		// Method:    setClass
		// FullName:  tezcat::ScriptNode::setClass
		// Access:    public 
		// Returns:   ScriptNode *
		// Qualifier:
		// Parameter: std::string class_name
		// Parameter: std::string attribute
		// Parameter: std::string value
		//************************************
		ScriptFile *setClass(std::string class_name, std::string attribute, std::string value, bool real = false);
		void setNullClass(std::string class_name)
		{
			m_Classes[class_name].clear();
		}

		//************************************
		// Method:    getClass
		// FullName:  tezcat::ScriptNode::getClass
		// Access:    public 
		// Returns:   std::map<std::string, std::string> *
		// Qualifier:
		// Parameter: const std::string & class_name
		//************************************
		std::map<std::string, TValue> *getClass(const std::string &class_name);
// 		void pushClass(const std::string &class_name);
// 		TValue &getValueInClass(const std::string &key);
// 		size_t getCountInClass() { return m_ClassesCache->size(); }
// 		void foreachClass(const std::function<void(const std::string &, const TValue &)> &function)
// 		{
// 			for (auto d : *m_ClassesCache)
// 			{
// 				function(d.first, d.second);
// 			}
// 		}

		//************************************
		// Method:    setVar
		// FullName:  tezcat::ScriptFile::setVar
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: std::string attribute
		// Parameter: std::string var
		// Parameter: bool real
		//************************************
		void setVar(std::string attribute, std::string var, bool real = false);

		//************************************
		// Method:    getVar
		// FullName:  tezcat::ScriptFile::getVar
		// Access:    public 
		// Returns:   TValue &
		// Qualifier:
		// Parameter: std::string attribute
		//************************************
		TValue &getVar(const std::string &attribute);

		//************************************
		// Method:    setArray
		// FullName:  tezcat::ScriptNode::setArray
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: std::string array_name
		// Parameter: std::string value
		//************************************
		void setArray(std::string array_name, std::string value, bool real = false);
		void setNullArray(std::string array_name)
		{
			m_Arrays[array_name].clear();
		}

		//************************************
		// Method:    getArray
		// FullName:  tezcat::ScriptNode::getArray
		// Access:    public 
		// Returns:   std::vector<std::string> *
		// Qualifier:
		// Parameter: std::string array_name
		//************************************
		std::vector<TValue> *getArray(std::string array_name);
// 		void pushArray(const std::string &array_name);
// 		TValue &getValueInArray(const size_t &index);
// 		void foreachArray(const std::function<void(const TValue &)> &function)
// 		{
// 			for (auto d : *m_ArraysCache)
// 			{
// 				function(d);
// 			}
// 		}

		//************************************
		// Method:    getFileName
		// FullName:  tezcat::ScriptNode::getFileName
		// Access:    public 
		// Returns:   std::string
		// Qualifier: const
		//************************************
		std::string getFileName() const { return m_FileName; }

		//************************************
		// Method:    setFileName
		// FullName:  tezcat::ScriptNode::setFileName
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: std::string val
		//************************************
		void setFileName(std::string val) { m_FileName = val; }

		//************************************
		// Method:    debug
		// FullName:  tezcat::ScriptNode::debug
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void debug();

		//************************************
		// Method:    isNull
		// FullName:  tezcat::ScriptFile::isNull
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		bool isNull() { return this == m_NullScriptFile; }

	public:
		//************************************
		// Method:    loadMapData
		// FullName:  tezcat::ScriptFile::loadMapData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & name
		// Parameter: PropertyMap & map
		//************************************
		void loadMapData(const std::string &name, PropertyMap &map)
		{
			auto *data_class = this->getClass(name);
			map.clear();
			map.reserve(data_class->size());
			for (auto d : *data_class)
			{
				map[d.first] = d.second;
			}
		}

		//************************************
		// Method:    loadArrayData
		// FullName:  tezcat::ScriptFile::loadArrayData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & name
		// Parameter: PropertyArray & array
		//************************************
		void loadArrayData(const std::string &name, PropertyArray &array)
		{
			auto *data_array = this->getArray(name);
			array.clear();
			array.reserve(data_array->size());
			for (auto d : *data_array)
			{
				array.push_back(d);
			}
		}

	private:
		static const std::string ScriptErrorVar;
		static const std::string ScriptErrorRule;


	private:
		friend class ScriptSystem;
		static ScriptFile *m_NullScriptFile;
		//文件名
		std::string m_FileName;

		//Var属性记录
		std::map<std::string, TValue> m_Vars;

		//Map属性记录 <map名, 属性, 规则>
		std::map<std::string, std::map<std::string, TValue>> m_Maps;

		//Class属性记录 <class名, 属性, 值>
		std::map<std::string, std::map<std::string, TValue>> m_Classes;

		//Array属性记录 <array名, 值>
		std::map<std::string, std::vector<TValue>> m_Arrays;

		//
		std::map<std::string, TValue> *m_VarsCache;
		std::map<std::string, TValue> *m_MapsCache;
		std::map<std::string, TValue> *m_ClassesCache;
		std::vector<TValue> *m_ArraysCache;
	private:
	};
}