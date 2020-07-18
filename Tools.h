#pragma once

#include <sstream>
#include <random>
#include <functional>

namespace tezcat
{
	namespace tools
	{
		inline static int random(int min, int max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(min, max);
			return dis(gen);
		}

		inline static float random(float min, float max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(min, max);
			return dis(gen);
		}

		//判断奇数
		inline static bool isODD(const int &value)
		{
			return (value & 1) != 0;
		}

		//判断偶数
		inline static bool isEven(const int &value)
		{
			return (value & 1) == 0;
		}
	}
}

