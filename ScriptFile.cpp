#include "ScriptFile.h"
#include "ScriptParse.h"
#include "ScriptDebug.h"

#include "TTString.h"
#include <iostream>

namespace tezcat
{
	ScriptFile * ScriptFile::m_NullScriptFile = new ScriptFile();

	const std::string ScriptFile::ScriptErrorRule = "script_error_rule";

	const std::string ScriptFile::ScriptErrorVar = "script_error_var";

	ScriptFile::ScriptFile()
	{

	}

	ScriptFile::~ScriptFile()
	{

	}

	void ScriptFile::debug()
	{
		std::cout << "======ScriptNode Debug Begin======" << std::endl;
		std::cout << "file name : " << m_FileName << std::endl;


		for (auto &data : m_Vars)
		{
			std::cout << "var " << data.first << " : " << data.second.asSTDString() << std::endl;
		}

		for (auto &data : m_Classes)
		{
			std::cout << "class " << data.first << ":" << std::endl;
			for (auto &d : data.second)
			{
				std::cout << " " << d.first << " : " << d.second.asSTDString() << std::endl;
			}
		}

		for (auto &data : m_Maps)
		{
			std::cout << "map " << data.first << ":" << std::endl;
			for (auto &d : data.second)
			{
				std::cout << " " << d.first << " : " << d.second.asSTDString() << std::endl;
			}
		}

		for (auto &data : m_Arrays)
		{
			std::cout << "array " << data.first << ":" << std::endl;
			for (auto &d : data.second)
			{
				std::cout << " " << d.asSTDString() << std::endl;
			}
		}

		std::cout << "======ScriptNode Debug End======" << std::endl;
	}

	void ScriptFile::setVar(std::string attribute, std::string var, bool real)
	{
		auto &v = m_Vars[attribute];
		v = var;
		if (real)
		{
			v.toDouble();
		}
	}

	TValue &ScriptFile::getVar(const std::string &attribute)
	{
#ifdef TT_Debug
		m_Type = Tpye::Var;
#endif
		auto it = m_Vars.find(attribute);
		if (it != m_Vars.end())
		{
			return it->second;
		}

#ifdef TT_Debug
		ScriptDebug::valueDebug(attribute);
#endif
		return TValue::NullValue;
	}

	ScriptFile *ScriptFile::setMap(std::string map_name, std::string attribute, std::string rule)
	{
		m_Maps[map_name][attribute] = rule;
		return this;
	}

	std::map<std::string, TValue> *ScriptFile::getMap(const std::string &map_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Map;
#endif
		auto it = m_Maps.find(map_name);
		if (it != m_Maps.end())
		{
			return &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::mapDebug(map_name);
#endif
		return nullptr;
	}

	ScriptFile *ScriptFile::setClass(std::string class_name, std::string attribute, std::string value, bool real)
	{
		TValue temp(value);
		if (real)
		{
			temp.toDouble();
		}
		m_Classes[class_name][attribute] = std::move(temp);
		return this;
	}

	std::map<std::string, TValue> *ScriptFile::getClass(const std::string &class_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Class;
#endif
		auto it = m_Classes.find(class_name);
		if (it != m_Classes.end())
		{
			return &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::classDebug(class_name);
#endif

		return nullptr;
	}

	void ScriptFile::setArray(std::string array_name, std::string value, bool real)
	{
		TValue temp(value);
		if (real)
		{
			temp.toDouble(); 
		}
		m_Arrays[array_name].push_back(std::move(temp));
	}

	std::vector<TValue> *ScriptFile::getArray(std::string array_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Array;
#endif
		auto it = m_Arrays.find(array_name);
		if (it != m_Arrays.end())
		{
			return &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::arrayDebug(array_name);
#endif

		return nullptr;
	}

	/*
	void ScriptFile::pushClass(const std::string &class_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Class;
#endif

		auto it = m_Classes.find(class_name);
		if (it != m_Classes.end())
		{
			m_ClassesCache = &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::classDebug(class_name);
#endif
	}

	void ScriptFile::pushMap(const std::string &map_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Map;
#endif

		auto it = m_Maps.find(map_name);
		if (it != m_Maps.end())
		{
			m_MapsCache = &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::mapDebug(map_name);
#endif
	}

	void ScriptFile::pushArray(const std::string &array_name)
	{
#ifdef TT_Debug
		m_Type = Tpye::Array;
#endif

		auto it = m_Arrays.find(array_name);
		if (it != m_Arrays.end())
		{
			m_ArraysCache = &it->second;
		}

#ifdef TT_Debug
		ScriptDebug::arrayDebug(array_name);
#endif
	}

	TValue & ScriptFile::getValueInClass(const std::string &key)
	{
#ifdef TT_Debug
		assert(m_Type == Tpye::Class);

		auto it = m_ClassesCache->find(key);
		if (it != m_ClassesCache->end())
		{
			return it->second;
		}

		ScriptDebug::valueDebug(key);

		return TValue::NullValue;
#else
		return m_ClassesCache->at(key);
#endif // TT_Debug
	}

	TValue & ScriptFile::getValueInMap(const std::string &key)
	{
#ifdef TT_Debug
		assert(m_Type == Tpye::Map);

		auto it = m_MapsCache->find(key);
		if (it != m_MapsCache->end())
		{
			return it->second;
		}

		ScriptDebug::valueDebug(key);

		return TValue::NullValue;
#else
		return m_MapsCache->at(key);
#endif // TT_Debug
	}

	TValue & ScriptFile::getValueInArray(const size_t &index)
	{
#ifdef TT_Debug
		assert(m_Type == Tpye::Array);
		assert(index < m_ArraysCache->size() - 1);

		return m_ArraysCache->at(index);
#else
		return m_ArraysCache->at(index);
#endif // TT_Debug
	}
	*/




}