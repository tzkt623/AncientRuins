#pragma once

#include <string>

namespace tezcat
{
#define HeadTag 6
#define TailTag 23

	typedef unsigned char Byte;
	typedef unsigned short DByte;

#pragma pack(push, 1)

	enum class NetPackageType : unsigned int
	{
		Error,
	};

	struct NetPackageHead
	{
		Byte tag;
		Byte version;			//1
		NetPackageType type;	//4
		DByte length;			//2
	};

	struct NetPackageTail
	{
		Byte tag;				//1
	};

#pragma pack(pop)

	template<typename T>
	T toBigEndian(T &value)
	{
		auto len = sizeof(T);
		T result = 0;
		Byte *tempResult = (Byte *)&result;
		Byte *tempValue = (Byte *)&value;
		for (size_t i = 0; i < len; i++)
		{
			tempResult[i] = tempValue[len - i - 1];
		}

		return result;
	}
}



