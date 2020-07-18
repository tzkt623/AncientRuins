#pragma once

//**************************************************************
//	词缀系统 根据词缀生成物品
//	基本的需求 : 1.词缀生成几率 2.词缀属性 3.词缀属性影响属性 4.影响算法.
//	词缀分类 : 1.前缀 2.中缀 3.后缀
//
//
//
//**************************************************************

#include "ScriptSystem.h"

namespace tezcat
{
	//
	template<typename ItemData>
	class WordSystem
	{
	public:
		WordSystem(){}
		~WordSystem(){}

		void init(const std::string &list)
		{
			m_ScriptSystem.loadListFile(list);
		}

		ItemData *createItem()
		{

		}

	private:
		ScriptSystem m_ScriptSystem;
	};
}