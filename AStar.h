#pragma once

#include <list>
#include <vector>
#include <set>
#include <algorithm>
#include "TileMap.h"

namespace tezcat
{
//	class TileMap;
//	class MapBlock<UserData>;

	template<typename UserData>
	class AStar
	{
	public:
		struct Node
		{
			float H;		//到终点的权重
			float G;		//到起点的权重
			MapBlock<UserData> *way;
			Node *parent;

			Node() : H(0), G(0), way(nullptr), parent(nullptr) {}

			//和值
			float getF()
			{
				return H + G;
			}
		};

	public:
		AStar()
		{}
		AStar(TileMap<UserData> *map) :
			m_Map(map), m_HasWay(false)
		{}
		~AStar()
		{}

	public:
		enum class Type
		{
			Diamond_4,
			Square_4,
			Square_8
		};

	public:

		void newFinding(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point, Type type)
		{
			m_HasWay = false;
			m_CloseList.clear();

			//如果开始点,结束点无效,不寻路
			if (begin_point->isInvalid() || target_point->isInvalid())
			{
				return;
			}

			//不能通行
			if (!begin_point->getUserData()->isRoad() || !target_point->getUserData()->isRoad())
			{
				return;
			}

			m_Type = type;

			//记录开始点
			m_BeginBlock = begin_point;
			//包装开始点
			auto *bg = this->warpBlock(begin_point);
			//包装结束点
			auto *ed = this->warpBlock(target_point);
			//将开始点加入开启列表
			m_AssistOpenList.push_back(bg);

			//寻路
			while (!m_AssistOpenList.empty())
			{
				//找到最好的一条路,并从开启列表里移除
				m_TheBest = this->findTheBest();
				//加入关闭列表
				m_AssistCloseList.push_back(m_TheBest);

				if (m_TheBest->way == ed->way)
				{
					m_TheBest = nullptr;
					break;
				}

				switch (m_Type)
				{
					//菱形4边寻路算法
				case Type::Diamond_4:
					this->newFindWay4(m_TheBest->way, ed->way);
					break;
				case Type::Square_4:
					break;
				case Type::Square_8:
					break;
				default:
					break;
				}

			}

			if (!m_AssistOpenList.empty())
			{
				//倒推回路径
				m_CloseList.push_front(target_point);
				auto it = m_AssistCloseList.rbegin();
				auto end = m_AssistCloseList.rend();
				while (it != end)
				{
					auto *w = (*it)->parent->way;

					if (w == m_BeginBlock)
					{
						m_HasWay = true;
						break;
					}

					if (std::find(m_CloseList.begin(), m_CloseList.end(), w) == m_CloseList.end())
					{
						m_CloseList.push_front(w);
					}

					++it;
				}
			}

			for (auto d : m_AssistCloseList)
			{
				this->recycleNode(d);
			}
			m_AssistCloseList.clear();

			for (auto d : m_AssistOpenList)
			{
				this->recycleNode(d);
			}
			m_AssistOpenList.clear();
			this->recycleNode(ed);
		}

		void newFindWay4(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point)
		{
			//上
			auto *top = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex + 1);
			this->newCheckBlock_4TBLR(top, target_point);

			//左
			auto *left = m_Map->getBlock(begin_point->xIndex - 1, begin_point->yIndex);
			this->newCheckBlock_4TBLR(left, target_point);

			//下
			auto *bottom = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex - 1);
			this->newCheckBlock_4TBLR(bottom, target_point);

			//右
			auto *right = m_Map->getBlock(begin_point->xIndex + 1, begin_point->yIndex);
			this->newCheckBlock_4TBLR(right, target_point);
		}

		void newCheckBlock_4TBLR(MapBlock<UserData> * check_point, MapBlock<UserData> * target_point)
		{
			//方块可以通过
			if (!check_point->isInvalid() && check_point->getUserData()->isRoad())
			{
				//查找关闭列表
				auto cit = std::find_if(m_AssistCloseList.begin(), m_AssistCloseList.end(), [&](Node *w)
				{
					return w->way == check_point;
				});
				//在关闭列表中
				if (cit != m_AssistCloseList.end())
				{
					return;
				}

				//查找开启列表
				auto oit = std::find_if(m_AssistOpenList.begin(), m_AssistOpenList.end(), [&](Node *w)
				{
					return w->way == check_point;
				});

				//不在开启列表中
				if (oit == m_AssistOpenList.end())
				{
					auto *helper = this->createHelper();
					//G值是best点到当前点的G值加best点的G值
					helper->G = 1.0f * (std::abs(m_TheBest->way->xIndex - check_point->xIndex) + std::abs(m_TheBest->way->yIndex - check_point->yIndex)) + m_TheBest->G;
					//H值计算方式不变
					helper->H = static_cast<float>(std::abs(check_point->xIndex - target_point->xIndex) + std::abs(check_point->yIndex - target_point->yIndex));
					//设置父节点
					helper->parent = m_TheBest;
					helper->way = check_point;
					m_AssistOpenList.push_back(helper);
				}
				//在开启列表中
				else
				{
					auto *way = (*oit);
					float newG = 1.0f * (std::abs(m_TheBest->way->xIndex - way->way->xIndex) + std::abs(m_TheBest->way->yIndex - way->way->yIndex)) + m_TheBest->G;

					if (newG < way->G)
					{
						way->G = newG;
						way->parent = m_TheBest;
					}
				}
			}
		}

		Node *warpBlock(MapBlock<UserData> *block)
		{
			auto *helper = this->createHelper();
			helper->way = block;

			return helper;
		}

		bool newIsInOpenList(MapBlock<UserData> *way)
		{
			return std::find_if(m_AssistOpenList.begin(), m_AssistOpenList.end(), [&](Node *w)
			{
				return w->way == way;
			}) != m_AssistOpenList.end();
		}

		bool newIsInCloseList(MapBlock<UserData> *way)
		{
			return std::find_if(m_AssistCloseList.begin(), m_AssistCloseList.end(), [&](Node *w)
			{
				return w->way == way;
			}) != m_AssistCloseList.end();
		}

		Node *findTheBest()
		{
			Node *result = nullptr;
			//更新权重
			float tempWeight = std::numeric_limits<float>::max();
			for (auto *way : m_AssistOpenList)
			{
				//获取F值
				auto temp = way->getF();

				//更新F最小值,和新通路
				if (temp <= tempWeight)
				{
					tempWeight = temp;
					result = way;
				}
			}

			m_AssistOpenList.remove(result);

			return result;
		}

		std::list<Node *> &getAssistCloseList() { return m_AssistCloseList; }

		void recycleNode(Node *node)
		{
			node->G = 0;
			node->H = 0;
			node->way = nullptr;
			node->parent = nullptr;
			m_RecycleHelper.push_back(node);

//			delete node;
		}
	public:

		//************************************
		// Method:    finding
		// FullName:  tezcat::AStar::finding
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: MapBlock * begin_point
		// Parameter: MapBlock * target_point
		//************************************
		void finding(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point, Type type)
		{
			this->newFinding(begin_point, target_point, type);
		}

		//************************************
		// Method:    getCloseList
		// FullName:  tezcat::AStar::getCloseList
		// Access:    public 
		// Returns:   std::list<MapBlock *> &
		// Qualifier:
		//************************************
		std::list<MapBlock<UserData> *> &getCloseList() { return m_CloseList; }

		//************************************
		// Method:    clearWay
		// FullName:  tezcat::AStar::clearWay
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clearWay() { m_CloseList.clear(); }

		//************************************
		// Method:    setMap
		// FullName:  tezcat::AStar::setMap
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: TileMap * val
		//************************************
		void setMap(TileMap<UserData> * val) { m_Map = val; }

		//************************************
		// Method:    hasWay
		// FullName:  tezcat::AStar::hasWay
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		bool hasWay() { return m_HasWay; }

		//************************************
		// Method:    nextPosition
		// FullName:  tezcat::AStar::nextPosition
		// Access:    public 
		// Returns:   MapBlock *
		// Qualifier:
		//************************************
		MapBlock<UserData> *nextPosition() { return m_CloseList.front(); }

		//************************************
		// Method:    pop
		// FullName:  tezcat::AStar::pop
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void pop()
		{ 
			if (m_CloseList.empty())
			{
				return;
			}
			m_CloseList.pop_front();
			if (m_CloseList.empty())
			{
				m_HasWay = false;
			}
		}

	private:
		//************************************
		// Method:    findWay
		// FullName:  tezcat::AStar::findWay
		// Access:    private 
		// Returns:   MapBlock *
		// Qualifier:
		// Parameter: MapBlock * begin_point
		// Parameter: MapBlock * target_point
		//************************************
		MapBlock<UserData> *findWay8(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point)
		{
			if (this->isInvalid(begin_point))
			{
				return nullptr;
			}

			if (this->isInvalid(target_point))
			{
				return nullptr;
			}

			if (begin_point == target_point)
			{
				return nullptr;
			}

			auto *top = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex + 1);
			this->checkBlock_4TBLR(top, target_point);

			auto *bottom = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex - 1);
			this->checkBlock_4TBLR(bottom, target_point);

			auto *left = m_Map->getBlock(begin_point->xIndex - 1, begin_point->yIndex);
			this->checkBlock_4TBLR(left, target_point);

			auto *right = m_Map->getBlock(begin_point->xIndex + 1, begin_point->yIndex);
			this->checkBlock_4TBLR(right, target_point);


			auto *topLeft = m_Map->getBlock(begin_point->xIndex - 1, begin_point->yIndex + 1);
			this->checkBlock_4Cross(topLeft, target_point);

			auto *topRight = m_Map->getBlock(begin_point->xIndex + 1, begin_point->yIndex + 1);
			this->checkBlock_4Cross(topRight, target_point);

			auto *bottomLeft = m_Map->getBlock(begin_point->xIndex - 1, begin_point->yIndex - 1);
			this->checkBlock_4Cross(bottomLeft, target_point);

			auto *bottomRight = m_Map->getBlock(begin_point->xIndex + 1, begin_point->yIndex - 1);
			this->checkBlock_4Cross(bottomRight, target_point);

			return this->calculateInfo(begin_point, target_point);
		}

		MapBlock<UserData> *findWay4(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point)
		{
			if (begin_point == target_point)
			{
				return nullptr;
			}

			auto *top = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex + 1);
			this->checkBlock_4TBLR(top, target_point);

			auto *left = m_Map->getBlock(begin_point->xIndex - 1, begin_point->yIndex);
			this->checkBlock_4TBLR(left, target_point);

			auto *bottom = m_Map->getBlock(begin_point->xIndex, begin_point->yIndex - 1);
			this->checkBlock_4TBLR(bottom, target_point);

			auto *right = m_Map->getBlock(begin_point->xIndex + 1, begin_point->yIndex);
			this->checkBlock_4TBLR(right, target_point);

			return this->calculateInfo(begin_point, target_point);
		}

		//************************************
		// Method:    checkBlock_4TBLR
		// FullName:  tezcat::AStar::checkBlock_4TBLR
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: MapBlock * check_point
		// Parameter: MapBlock * target_point
		//************************************
		void checkBlock_4TBLR(MapBlock<UserData> * check_point, MapBlock<UserData> * target_point)
		{
			//方块可以通过
			if (!this->isInvalid(check_point))
			{
				//方块没有加入到关闭列表,也不在开启列表
				if (!this->isInCloseList(check_point) && !this->isInOpenList(check_point))
				{
					Node *helper = this->createHelper();
					helper->G = 1.0f * (std::abs(m_BeginBlock->xIndex - check_point->xIndex) + std::abs(m_BeginBlock->yIndex - check_point->yIndex));
					helper->H = std::abs(check_point->xIndex - target_point->xIndex) + std::abs(check_point->yIndex - target_point->yIndex);
					helper->way = check_point;
					helper->parent = m_TheBest;
					this->push2OpenList(helper);
				}
			}
		}

		//************************************
		// Method:    checkBlock_4Cross
		// FullName:  tezcat::AStar::checkBlock_4Cross
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: MapBlock * check_point
		// Parameter: MapBlock * target_point
		//************************************
		void checkBlock_4Cross(MapBlock<UserData> * check_point, MapBlock<UserData> * target_point)
		{
			if (!this->isInvalid(check_point))
			{
				//方块没有加入到关闭列表
				if (!this->isInCloseList(check_point))
				{
					Node *helper = this->createHelper();
					helper->G = 1.4f * (std::abs(m_BeginBlock->xIndex - check_point->xIndex) + std::abs(m_BeginBlock->yIndex - check_point->yIndex));
					helper->H = std::abs(check_point->xIndex - target_point->xIndex) + std::abs(check_point->yIndex - target_point->yIndex);
					helper->way = check_point;
					helper->parent = m_TheBest;
					this->push2OpenList(helper);
				}
			}
		}

		//************************************
		// Method:    calculateInfo
		// FullName:  tezcat::AStar::calculateInfo
		// Access:    private 
		// Returns:   MapBlock *
		// Qualifier:
		// Parameter: MapBlock * begin_point
		// Parameter: MapBlock * target_point
		//************************************
		MapBlock<UserData> *calculateInfo(MapBlock<UserData> *begin_point, MapBlock<UserData> *target_point)
		{
			Node *result = nullptr;
			float tempWeight = std::numeric_limits<float>::max();

			for (auto *way : m_AssistOpenList)
			{
				//获取F值
				auto temp = way->getF();
				//			way->way->ifScan = true;
				//更新F最小值,和新通路
				if (temp <= tempWeight)
				{
					tempWeight = temp;
					result = way;
					m_TheBest = way;
				}
			}

			// 		for (auto way : m_AssistOpenList)
			// 		{
			// 			m_RecycleHelper.push_back(way);
			// 		}
			// 
			// 		m_AssistOpenList.clear();

			if (result == nullptr)
			{
				return nullptr;
			}
			else
			{
				//			m_OpenList.remove(result->way);
				m_AssistOpenList.remove(result);
				m_AssistCloseList.push_back(result);
				//			m_CloseList.push_back(result->way);

				// 			auto w = result->way;
				// 			result->way = nullptr;
				// 			m_RecycleHelper.push_back(result);

				return result->way;
			}
		}

		//************************************
		// Method:    ifBlock
		// FullName:  tezcat::AStar::ifBlock
		// Access:    private 
		// Returns:   bool
		// Qualifier:
		// Parameter: MapBlock * block
		//************************************
		bool isInvalid(MapBlock<UserData> *block)
		{
			return block->invalid;
		}

		//************************************
		// Method:    push2OpenList
		// FullName:  tezcat::AStar::push2OpenList
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: Helper * way
		//************************************
		void push2OpenList(Node *helper)
		{
			//如果已经在开启列表中了
			if (this->newIsInOpenList(helper->way))
			{

			}
			else
			{
				m_AssistOpenList.push_back(helper);
			}
		}

		//************************************
		// Method:    createHelper
		// FullName:  tezcat::AStar::createHelper
		// Access:    private 
		// Returns:   Helper *
		// Qualifier:
		//************************************
		Node *createHelper()
		{
			if (m_RecycleHelper.empty())
			{
				return new AStar::Node();
			}
			else
			{
				auto *h = m_RecycleHelper.front();
				h->G = 0;
				h->H = 0;
				h->parent = nullptr;
				h->way = nullptr;
				m_RecycleHelper.pop_front();
				return h;
			}
		}

		//************************************
		// Method:    isInOpenList
		// FullName:  tezcat::AStar::isInOpenList
		// Access:    private 
		// Returns:   bool
		// Qualifier:
		// Parameter: Node * block
		//************************************
		bool isInOpenList(MapBlock<UserData> *way)
		{
			return std::find(m_OpenList.begin(), m_OpenList.end(), way) != m_OpenList.end();
//			return std::find(m_AssistOpenList.begin(), m_AssistOpenList.end(), block->way) != m_AssistOpenList.end();
		}

		bool isInCloseList(MapBlock<UserData> *way)
		{
			return std::find(m_CloseList.begin(), m_CloseList.end(), way) != m_CloseList.end();
		}

	private:
		TileMap<UserData> *m_Map;
		std::list<Node *> m_AssistOpenList;
		std::list<Node *> m_AssistCloseList;

		std::list<MapBlock<UserData> *> m_OpenList;
		std::list<MapBlock<UserData> *> m_CloseList;

		Type m_Type;

		MapBlock<UserData> *m_BeginBlock;
		Node *m_TheBest;

		bool m_HasWay;
		static std::list<Node *> m_RecycleHelper;
	};

	template<typename UserData> std::list<typename AStar<UserData>::Node *> AStar<UserData>::m_RecycleHelper;

}
