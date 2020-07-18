#pragma once

#include <functional>
#include <vector>
#include <list>
#include <unordered_set>
#include <complex>

namespace tezcat
{
	class AbstractMapBlock
	{

	public:
		AbstractMapBlock(int _x = 0, int _y = 0, float px = 0, float py = 0, bool inv = true) :
			xIndex(_x), yIndex(_y), xPoint(px), yPoint(py), height(0), width(0){}

		float getMidX() { return xPoint + width / 2; }
		float getMidY() { return yPoint + height / 2; }

		float getMaxX() { return xPoint + width; }
		float getMaxY() { return yPoint + height; }

		float getMinX() { return xPoint; }
		float getMinY() { return yPoint; }

	public:
		int xIndex;
		int yIndex;
		float xPoint;
		float yPoint;
		float width;
		float height;
		void *userData;
	};

	template<typename UserData>
	class MapBlock : public AbstractMapBlock
	{
	public:
		MapBlock(UserData *usr = nullptr, int _x = 0, int _y = 0, float px = 0, float py = 0, bool inv = true) :
			AbstractMapBlock(_x, _y, px, py, inv), userData(usr)
		{}
		UserData *getUserData() { return userData; }

		~MapBlock()
		{
			if (userData != nullptr)
			{
				delete userData;
			}
		}

		bool isInvalid() { return this == Invalid; }

		static MapBlock *Invalid;

		void setUserData(UserData *ud)
		{
			userData = ud;
		}

	private:
		UserData *userData;
	};

	template<typename UserData>
	MapBlock<UserData> *MapBlock<UserData>::Invalid = new MapBlock<UserData>();


	template<typename UserData>
	class TileMap
	{
		enum class Type
		{
			Ortho,
			Diamond,
			HexagonYFlat,
			HexagonXFlat,
		};
	public:
		TileMap(){}
		TileMap(int col_x, int row_y, float width = 0, float height = 0):
			m_TotalX(col_x), m_TotalY(row_y), m_BlockWidth(width), m_BlockHeight(height)
		{
			m_MapWidth = m_TotalX * m_BlockWidth;
			m_MapHeight = m_TotalY * m_BlockHeight;
		}
		~TileMap()
		{

		}

		//************************************
		// Method:    createMap
		// FullName:  tezcat::TileMap::createMap
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: int col_x 横排个数
		// Parameter: int row_y 竖排个数
		// Parameter: float width 方块宽
		// Parameter: float height 方块高
		// Parameter: float offset_x 横向偏移
		// Parameter: float offset_y 纵向偏移
		//************************************
		void createOrthoMap(float offset_x = 0, float offset_y = 0)
		{
			m_MapType = Type::Ortho;
			m_Blocks.reserve(m_TotalX * m_TotalY);

			m_OffSetX = offset_x;
			m_OffSetY = offset_y;

			for (int y = 1; y <= m_TotalY; y++)
			{
				for (int x = 1; x <= m_TotalX; x++)
				{
					auto block = new MapBlock<UserData>();
					block->xIndex = x;
					block->yIndex = y;
					block->width = m_BlockWidth;
					block->height = m_BlockHeight;
					block->xPoint = offset_x + ((x - 1) * m_BlockWidth);
					block->yPoint = offset_y + ((y - 1) * m_BlockHeight);
					m_Blocks.push_back(block);
				}
			}
		}

		//************************************
		// Method:    createDiamondMap
		// FullName:  tezcat::TileMap::createDiamondMap
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: float offset_x
		// Parameter: float offset_y
		//************************************
		void createDiamondMap(float offset_x = 0, float offset_y = 0)
		{
			m_MapType = Type::Diamond;
			m_Blocks.reserve(m_TotalX * m_TotalY);

			m_OffSetX = offset_x;
			m_OffSetY = offset_y;

			for (int y = 1; y <= m_TotalY; y++)
			{
				for (int x = 1; x <= m_TotalX; x++)
				{
					auto block = new MapBlock<UserData>();
					block->xIndex = x;
					block->yIndex = y;
					block->width = m_BlockWidth;
					block->height = m_BlockHeight;
					block->xPoint = //(m_MapWidth / 2 - width / 2) //起点
						m_OffSetX //X偏移
						+ ((x - 1) * m_BlockWidth / 2) //X移动一格
						- ((y - 1) * m_BlockWidth / 2); //Y移动一格

					block->yPoint = //(m_MapHeight - height) //起点
						m_OffSetY //Y偏移
						- ((x - 1) * m_BlockHeight / 2) //X移动一格
						- ((y - 1) * m_BlockHeight / 2); //Y移动一格
					m_Blocks.push_back(block);
				}
			}
		}

		//************************************
		// Method:    createHexagonYFlatMap
		// FullName:  tezcat::TileMap::createHexagonYFlatMap
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: float side_length
		// Parameter: float offset_x
		// Parameter: float offset_y
		//************************************
		void createHexagonYFlatMap(float side_length, float offset_x = 0, float offset_y = 0)
		{
			m_MapType = Type::HexagonYFlat;
			m_Blocks.reserve(m_TotalX * m_TotalY);

			m_OffSetX = offset_x;
			m_OffSetY = offset_y;

			float PI = 3.141592653f;

			m_SideLength = side_length;
			auto side_sin = side_length * std::sin(PI / 180 * 30.0f);
			auto side_cos = side_length * std::cos(PI / 180 * 30.0f);
			m_BlockWidth = side_sin * 2 + side_length;
			m_BlockHeight = side_cos * 2;

			for (int y = 1; y <= m_TotalY; y++)
			{
				for (int x = 1; x <= m_TotalX; x++)
				{
					auto block = new MapBlock<UserData>();
					block->xIndex = x;
					block->yIndex = y;
					block->width = m_BlockWidth;
					block->height = m_BlockHeight;
					block->invalid = false;

					//X
					block->xPoint = m_OffSetX //X偏移
						+ (side_sin + side_length) * (x - 1);

					//Y
					if ((x - 1) % 2 == 0)
					{
						block->yPoint = m_OffSetY //Y偏移
							+ side_cos * 2 * (y - 1);
					}
					else
					{
						block->yPoint = m_OffSetY //Y偏移
							+ side_cos * 2 * (y - 1)
							+ side_cos;
					}


					m_Blocks.push_back(block);
				}
			}
		}

		//************************************
		// Method:    createHexagonXFlatMap
		// FullName:  tezcat::TileMap::createHexagonXFlatMap
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: float side_length
		// Parameter: float offset_x
		// Parameter: float offset_y
		//************************************
		void createHexagonXFlatMap(float side_length, float offset_x = 0, float offset_y = 0)
		{
			m_MapType = Type::HexagonYFlat;
			m_Blocks.reserve(m_TotalX * m_TotalY);

			m_OffSetX = offset_x;
			m_OffSetY = offset_y;

			float PI = 3.141592653f;

			m_SideLength = side_length;
			auto side_sin = side_length * std::sin(PI / 180 * 30.0f);
			auto side_cos = side_length * std::cos(PI / 180 * 30.0f);
			m_BlockWidth = side_cos * 2;
			m_BlockHeight = side_sin * 2 + side_length;

			for (int y = 1; y <= m_TotalY; y++)
			{
				for (int x = 1; x <= m_TotalX; x++)
				{
					auto block = new MapBlock<UserData>();
					block->xIndex = x;
					block->yIndex = y;
					block->width = m_BlockWidth;
					block->height = m_BlockHeight;
					block->invalid = false;

					//X
					if ((y - 1) % 2 == 0)
					{
						block->xPoint = m_OffSetX //X偏移
							+ side_cos * 2 * (x - 1);
					}
					else
					{
						block->xPoint = m_OffSetX //X偏移
							+ side_cos * 2 * (x - 1)
							+ side_cos;
					}

					block->yPoint = m_OffSetY //Y偏移
						+ (side_sin + side_length) * (y - 1);

					m_Blocks.push_back(block);
				}
			}
		}

		//************************************
		// Method:    getBlock
		// FullName:  tezcat::TileMap::getBlock
		// Access:    public 
		// Returns:   MapBlock *
		// Qualifier:
		// Parameter: int x
		// Parameter: int y
		//************************************
		MapBlock<UserData> *getBlock(const int &x, const int &y)
		{
			if (x > m_TotalX || y > m_TotalY || x < 1 || y < 1)
			{
				return MapBlock<UserData>::Invalid;
			}

			return m_Blocks[x + ((y - 1) * m_TotalX) - 1];
		}

		//************************************
		// Method:    getBlock
		// FullName:  tezcat::TileMap::getBlock
		// Access:    public 
		// Returns:   MapBlock *
		// Qualifier:
		// Parameter: float x
		// Parameter: float y
		//************************************
		MapBlock<UserData> *getBlock(const float &x, const float &y)
		{
			int tempX = 0;
			int tempY = 0;

			switch (m_MapType)
			{
			case Type::Ortho:
				tempX = static_cast<int>(x / m_BlockWidth + 1);
				tempY = static_cast<int>(y / m_BlockHeight + 1);
				break;
			case Type::Diamond:
				tempX = static_cast<int>(((x - m_MapWidth / 2) / m_BlockWidth) - ((y - m_MapHeight) / m_BlockHeight)) + 1;
				tempY = static_cast<int>(-((x - m_MapWidth / 2) / m_BlockWidth) - ((y - m_MapHeight) / m_BlockHeight)) + 1;
				break;
			case Type::HexagonYFlat:
			{
									   tempY = y / m_BlockHeight;
									   float yy = y - tempY * m_BlockHeight;

									   tempX = x / m_BlockWidth;
									   float xx = x - tempX * m_BlockWidth;

									   if ((tempX + tempY) & 1)
									   {
										   if (xx * m_BlockWidth - yy * m_MapHeight > (m_BlockWidth * m_BlockWidth - m_BlockHeight * m_BlockHeight) / 2)
										   {
											   tempX += 1;
										   }
									   }
									   else
									   {
										   if (xx * m_BlockWidth + yy * m_BlockHeight > (m_BlockWidth * m_BlockWidth + m_BlockHeight * m_BlockHeight) / 2)
										   {
											   tempX += 1;
										   }
									   }

									   tempX = (tempX + (1 - (tempY & 1))) / 2;

									   tempX += 1;
									   tempY += 1;
			}
				break;
			case Type::HexagonXFlat:
			{

			}
				break;
			default:
				break;
			}

			return this->getBlock(tempX, tempY);
		}

		int getXRow() const { return m_TotalX; }
		int getYRow() const { return m_TotalY; }

		int getXRowFirst() const { return 1; }
		int getYRowFirst() const { return 1; }

		std::vector<MapBlock<UserData> *> &getBlocks() { return m_Blocks; }

		void foreachBlock(const std::function< void(MapBlock<UserData> *) > &function)
		{
			for (int y = 1; y <= m_TotalY; y++)
			{
				for (int x = 1; x <= m_TotalX; x++)
				{
					function(this->getBlock(x, y));
				}
			}
		}

		std::list<std::string> &getInfo() { return m_Info; }


	public:
		float getOffSetX() const { return m_OffSetX; }
		float getOffSetY() const { return m_OffSetY; }

		float getMapWidth() const { return m_MapWidth; }
		float getMapHeight() const { return m_MapHeight; }

		float getBlockWidth() const { return m_BlockWidth; }
		float getBlockHeight() const { return m_BlockHeight; }

		int getTotalX() const { return m_TotalX; }
		int getTotalY() const { return m_TotalY; }

		void clear()
		{
			auto it = m_Blocks.begin();
			while (it != m_Blocks.end())
			{
				delete(*it);
				++it;
			}
			m_Blocks.clear();
		}

	private:


	protected:
		Type m_MapType;
		std::vector<MapBlock<UserData> *> m_Blocks;
		std::unordered_set<MapBlock<UserData> *> m_Borders;
		std::list<std::string> m_Info;

		int m_TotalX;
		int m_TotalY;

		float m_BlockWidth;
		float m_BlockHeight;

		float m_OffSetX;
		float m_OffSetY;

		float m_MapWidth;
		float m_MapHeight;

		float m_SideLength;
	};
}