#include "ScriptParse.h"
#include "ScriptFile.h"
#include "TTString.h"
#include "SystemIO.h"

#include <vector>
#include <list>
#include <sstream>


namespace tezcat
{
//	std::string ScriptParse::FileHead = "file";
	std::string ScriptParse::Var = "var";
	std::string ScriptParse::Map = "map";
	std::string ScriptParse::Class = "class";
	std::string ScriptParse::Array = "array";


	//
	//
	//
	ScriptParse::ScriptParse():
		m_RefCount(0)
	{

	}

	ScriptParse::~ScriptParse()
	{

	}

	ScriptFile *ScriptParse::loadFile(const std::string &file_name)
	{
//		auto data = IO::loadBinary(file_name);
//		std::string temp = IO::loadBinary(file_name);
		auto str = io::loadBinary2String(file_name);
		return loadData(str, file_name);
	}

	ScriptFile *ScriptParse::loadData(std::string &data, const std::string &file_name)
	{
		bool findFile = false;

		ScriptFile *node = new ScriptFile();

		auto lastF = file_name.find_last_of('/');
		if (lastF != std::string::npos)
		{
			node->setFileName(file_name.substr(lastF + 1, file_name.find_first_of('.') - lastF - 1));
		}
		else
		{
			node->setFileName(file_name.substr(0, file_name.find_first_of('.')));
		}


		String::removeByFlag(data, "\n\r\t");

		//分离每层
		auto list = String::split2List(data, ';');
		for (auto &str : list)
		{
			//判断类型
			auto firstSpacePos = str.find_first_of(' ');
			std::string type = str.substr(0, firstSpacePos);
			//分析var类型
			if (type == Var)
			{
				
				auto equalPos = str.find_first_of('=');
				std::string name = str.substr(firstSpacePos + 1, equalPos - firstSpacePos - 1);
				std::string value = str.substr(equalPos + 1);
				//没发现",即为实数
				bool isReal = this->handleString(value);
				node->setVar(name, value, isReal);
			}
			//分析class类型
			else if (type == Class)
			{
				//找括号
				auto firstK = str.find_first_of('{');
				auto lastK = str.find_last_of('}');
				std::string classList = str.substr(firstK + 1, lastK - firstK - 1);
				std::string className = str.substr(firstSpacePos + 1, firstK - firstSpacePos - 1);
				//分离每层
				String::removeByFlag(classList, " ");
				
				auto mapList = tezcat::String::split2List(classList, ',');
				if (mapList.empty())
				{
					node->setNullClass(className);
				}
				else
				{
					for (auto data : mapList)
					{
						auto equalPos = data.find_first_of('=');
						std::string name = data.substr(0, equalPos);
						std::string value = data.substr(equalPos + 1);
						auto isReal = handleString(value);
						node->setClass(className, name, value, isReal);
					}
				}
			}
			//分析map类型
			else if (type == Map)
			{
				//找括号
				auto firstK = str.find_first_of('{');
				auto lastK = str.find_last_of('}');
				std::string map = str.substr(firstK + 1, lastK - firstK - 1);
				std::string mapName = str.substr(firstSpacePos + 1, firstK - firstSpacePos - 1);
				//分离每层
				String::removeByFlag(map, " ");
				auto mapList = tezcat::String::split2List(map, ',');
				if (mapList.empty())
				{
					node->setNullMap(mapName);
				}
				else
				{
					for (auto data : mapList)
					{
						auto equalPos = data.find_first_of('=');
						std::string name = data.substr(0, equalPos);
						std::string rule = data.substr(equalPos + 1);
						node->setMap(mapName, name, rule);
					}
				}
			}
			//分析array类型
			else if (type == Array)
			{
				//找括号
				auto firstK = str.find_first_of('{');
				auto lastK = str.find_last_of('}');
				std::string arrayList = str.substr(firstK + 1, lastK - firstK - 1);
				std::string arrayName = str.substr(firstSpacePos + 1, firstK - firstSpacePos - 1);
				//分离每层
				String::removeByFlag(arrayList, " ");
				auto arrayData = tezcat::String::split2List(arrayList, ',');
				if (arrayData.empty())
				{
					node->setNullArray(arrayName);
				}
				else
				{
					for (auto data : arrayData)
					{
						bool isReal = this->handleString(data);
						node->setArray(arrayName, data, isReal);
					}
				}
			}

		}

		return node;
	}

	bool ScriptParse::handleString(std::string &value)
	{
		bool isReal = false;
		if (value.find('"') == std::string::npos)
		{
			isReal = true;
		}
		else
		{
			String::removeByFlag(value, "\"");
		}

		return isReal;
	}


}