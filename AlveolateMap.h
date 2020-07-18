#pragma once

#include <iostream>
#include <vector>

namespace tezcat
{
	class AlveolateCell
	{
	public:
		AlveolateCell() :pointX(0), pointY(0), indexX(0), indexY(0) {}
		AlveolateCell(const float &px, const float &py, const int &ix, const int &iy)
			:pointX(px), pointY(py), indexX(ix), indexY(iy) {}

		float pointX, pointY;
		int indexX, indexY;
		float width, height;
	};

	class AlveolateMap
	{
	public:
		AlveolateMap();
		~AlveolateMap();

		void createMap(int cols, int rows, const float &side_length)
		{
			this->setCellSize(side_length);
			for (int y = 0; y < rows; y++)
			{
				for (int x = 0; x < cols; x++)
				{
					auto *cell = new AlveolateCell(0 + m_RectWidth * x, 0 + m_RectHeight * y, x, y);
					m_Cells.push_back(cell);
				}
			}
		}

		//输入鼠标按下的点坐标（x，y）
		//返回被捕获六边形的中心坐标
		AlveolateCell getCell(const float &x, const float &y)
		{
			//位于矩形网格边线上的三个CELL中心点
			AlveolateCell points[3];
			//当前距离
			float dist;
			float mindist = m_MinDistance * 100; //一个非常大的值
			int index;//index:被捕获的索引
			//计算出鼠标点位于哪一个矩形网格中
			int cx = (int)(x / m_RectWidth);
			int cy = (int)(y / m_RectHeight);

			points[0].pointX = m_RectWidth * cx;
			points[1].pointX = m_RectWidth * (cx + 0.5f);
			points[2].pointX = m_RectWidth * (cx + 1);

			//根据cy是否是偶数，决定三个点的纵坐标
			if (cy % 2 == 0)
			{
				//偶数时，三个点组成倒立三角
				points[0].pointY = points[2].pointY = m_RectHeight * cy;
				points[1].pointY = m_RectHeight * (cy + 1);
			}
			else
			{
				//奇数时，三个点组成正立三角
				points[0].pointY = points[2].pointY = m_RectHeight * (cy + 1);
				points[1].pointY = m_RectHeight * cy;
			}

			//现在找出鼠标距离哪一个点最近
			for (int i = 0; i < 3; i++)
			{
				//求出距离的平方
				dist = distance2(x, y, points[i].pointX, points[i].pointY);

				//如果已经肯定被捕获
				if (dist < m_MinDistance)
				{
					index = i;
					break;
				}

				//更新最小距离值和索引
				if (dist < mindist)
				{
					mindist = dist;
					index = i;
				}
			}

			this->setDrawCell(points[index].pointX, points[index].pointY);

			//现在index 就是被捕获的结果
			return points[index];
		}

		AlveolateCell *getDrawCell() { return m_DrawCell; }

	private:
		//设置六边形的边长
		void setCellSize(const float &side_length)
		{
			if (side_length > 0)
			{
				m_CellSideLength = side_length;
				m_RectWidth = side_length * 1.7320508f;		//sqrt(3) * side_length 
				m_RectHeight = side_length * 1.5f;			//1.5 * side_length
				//二分之根号3 边长的平方，如果距离比它还小，就必然捕获
				m_MinDistance = side_length * side_length * 0.75f;
			}
		}

		//求取两个点的距离平方
		inline float distance2(const float &x1, const float &y1, const float &x2, const float &y2)
		{
			return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		}

		//给出蜂窝CELL的中心点和边长a，填充Cell的六边形的六个端点
		void setDrawCell(const float &cellx, const float &celly)
		{
			m_DrawCell[0].pointX = cellx;
			m_DrawCell[0].pointY = celly - m_CellSideLength;

			m_DrawCell[1].pointX = cellx + m_RectWidth * 0.5f;
			m_DrawCell[1].pointY = celly - m_CellSideLength / 2;

			m_DrawCell[2].pointX = m_DrawCell[1].pointX;
			m_DrawCell[2].pointY = celly + m_CellSideLength / 2;

			m_DrawCell[3].pointX = cellx;
			m_DrawCell[3].pointY = celly + m_CellSideLength;

			m_DrawCell[4].pointX = cellx - m_RectWidth * 0.5f;
			m_DrawCell[4].pointY = celly + m_CellSideLength / 2;

			m_DrawCell[5].pointX = m_DrawCell[4].pointX;
			m_DrawCell[5].pointY = celly - m_CellSideLength / 2;
		}

	private:
		//两个方向的矩形网格基本单位
		float m_RectWidth;
		float m_RectHeight;
		float m_MinDistance;     // (a*sqrt(3)/2)^2
		float m_CellSideLength;
		AlveolateCell m_DrawCell[6];


	private:
		std::vector<AlveolateCell *> m_Cells;
	};

}