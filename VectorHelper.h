#pragma once

#include <tuple>

namespace tezcat
{
	namespace vector
	{
		namespace group2x2
		{
			//************************************
			// Method:    get
			// FullName:  tezcat::vector::group2x2::get
			// Access:    public static 
			// Returns:   ::type
			// Qualifier:
			// Parameter: const std::vector<T> & vector
			// Parameter: unsigned int x
			// Parameter: unsigned int y
			// Note     : 此函数不负责取值越界检测
			//************************************
			template<typename T, unsigned int row, unsigned int col>
			static typename std::enable_if<true, T>::type get(const std::vector<T> &vector, unsigned int x, unsigned int y)
			{
				static_assert(row > 0 && col > 0, "row or col must be bigger than zero");
// 				if (x > row || y > col || x < 1 || y < 1)
// 				{
// 					throw std::logic_error("index out of range");
// 				}

				return vector[x - 1 + row * (y - 1)];
			}

			//************************************
			// Method:    get
			// FullName:  tezcat::vector::group2x2::get
			// Access:    public static 
			// Returns:   ::type
			// Qualifier:
			// Parameter: unsigned int row
			// Parameter: unsigned int col
			// Parameter: const std::vector<T> & vector
			// Parameter: unsigned int x
			// Parameter: unsigned int y
			// Note     : 按照一个2X2的矩阵来获取容器中的对象
			//************************************
			template<typename T>
			static typename std::enable_if<true, T>::type get(unsigned int row, unsigned int col, const std::vector<T> &vector, unsigned int x, unsigned int y)
			{
				return vector[x + row * y];
			}

		}
	}
}