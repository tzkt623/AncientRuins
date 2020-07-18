#pragma once

//#include "RunTimeClass.h"

//=============================================================
// 文件 : Objec.h
// 功能 : 总父类
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-11-13
// 信息 : 总父类占用类编号0
//=============================================================

namespace tezcat
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

//		virtual std::string getClassName() = 0;

		virtual unsigned int getClassID() = 0;

		virtual unsigned int getClassRunLevel() = 0;



	};
}