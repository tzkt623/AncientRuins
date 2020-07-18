#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace tezcat
{
	class RunTimeSystem
	{
	public:
		static RunTimeSystem *getInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new RunTimeSystem();
				m_Instance->ClassID = 0;
			}
			return m_Instance;
		}

		void addClassInfos(std::string name, unsigned int id)
		{
			auto it = ClassIDInfos.find(name);
			if (it == ClassIDInfos.end())
			{
				ClassIDInfos.insert(std::make_pair(name, id));
			}
		}

		void lookClassInfos()
		{
			for (auto &data : ClassIDInfos)
			{
				std::cout << data.first << " : " << data.second << std::endl;
			}
		}

		void giveID(const std::string &name)
		{
			ClassIDMap.push_back(name);
			this->addClassInfos(name, ClassID);
			ClassID += 1;
		}

		void giveTypeID(size_t &type_id)
		{
			type_id = TypeID++;
		}

		void setCreateFunction(const std::function<void*(const std::string &)> &function) { m_Function = function; }

		void *createClass(const std::string &class_name) { return m_Function(class_name); }

	private:
		RunTimeSystem() : TypeID(0), ClassID(0) {}

	private:
		static RunTimeSystem *m_Instance;

		unsigned int ClassID;
		size_t TypeID;
		std::function<void*(const std::string &)> m_Function;
		std::map<std::string, unsigned int> ClassIDInfos;
		std::map<std::string, std::string> ErrorClassInfos;
		std::vector<std::string> ClassIDMap;
	};
}