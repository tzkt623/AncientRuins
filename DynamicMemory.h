#pragma once

//=============================================================
// 文件 : DynamicMemory.h
// 功能 : 内存管理类
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-12-10
//=============================================================

namespace tezcat
{
	class DynamicMemory
	{
	public:
		virtual ~DynamicMemory() {}
		virtual void recycle() { delete this; }

		
	private:


	};
}