#pragma once

#include <string>

//========================================================================
//
//	文件 : ScriptParse.h
//	时间 : 2014-10-30
//	作者 : 特兹卡特(Tezcat)
//	功能 : 脚本文件解析器,解析器每次读取一个文件解析
//	关键字 : var 代表独立的一个赋值操作
//	关键字 : map 代表一组映射,表示一组属性被一定的规则所影响
//	关键字 : class 代表一个类
//
//========================================================================

namespace tezcat
{
	class ScriptFile;
	class ScriptParse
	{
	public:
		ScriptParse();
		~ScriptParse();

	public:

		//************************************
		// Method:    loadFile
		// FullName:  tezcat::ScriptParse::loadFile
		// Access:    public 
		// Returns:   ScriptNode *
		// Qualifier:
		// Parameter: const std::string & file_name
		//************************************
		ScriptFile *loadFile(const std::string &file_name);

		//************************************
		// Method:    loadData
		// FullName:  tezcat::ScriptParse::loadData
		// Access:    public 
		// Returns:   ScriptNode *
		// Qualifier:
		// Parameter: std::string & data
		//************************************
		ScriptFile *loadData(std::string &data, const std::string &file_name);

		void retain() { m_RefCount += 1; }
		void release()
		{
			m_RefCount -= 1;
			if (m_RefCount <= 0)
			{
				delete this;
			}
		}

	private:
		//************************************
		// Method:    handleString
		// FullName:  tezcat::ScriptParse::handleString
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: std::string & value
		//************************************
		bool handleString(std::string &value);

	private:
		static std::string FileHead;

		static std::string Var;
		static std::string Map;
		static std::string Class;
		static std::string Array;

	private:
		size_t m_RefCount;
	};
}