/****************************************************************************************************
*  TTXML_Node.h
*  作者 : 特兹卡特(Tezcat)
*  功能 : XML数据节点
*  时间 : 14-1-13
*  说明 : 1.数据组织结构,可以导出成XML文件
*           2.每个节点的内存由其父节点管理,不用手动管理内存
*           3.所有节点必须全部通过TTXML,TTXML_Node类create出来,不能使用new或者对象
****************************************************************************************************/
#pragma once

#include "XmlGlobal.h"
#include <functional>
#include <sstream>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "TTString.h"

namespace tezcat
{

	enum class XmlNodeSwitchType
	{
		ST_KV,
		ST_AT
	};

	class XmlNode
	{
	public:

		/**
		* Method:    create
		* FullName:  XmlNode::create
		* Access:    public static
		* Returns:   XmlNode *
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		static XmlNode *create()
		{
			return new XmlNode();
		}

		/**
		* Method:    recycle
		* FullName:  XmlNode::recycle
		* Access:    public
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void recycle()
		{
			delete this;
		}

		/**
		 *	@brief 创建本节点的子节点
		 *	@param k 键
		 *	@param v值 不填为创建组节点
		 *	@return 返回创建好的节点
		 *	@创建一个本节点的子节点,非自由节点
		 */
		XmlNode *simpleCreate(const std::string &k, const std::string &v = TTXML_NODE);
		
		template<typename T>
		XmlNode *simpleCreate(const std::string &k, const T &value)
		{
			auto newNode = XmlNode::create();
			newNode->key = k;
			newNode->value = String::toString(value);
			this->linkChild(newNode);
			return newNode;
		}

		/**
		 *	@brief 挂接一个子节点
		 *	@param child 子节点 值节点或组节点
		 */
		void linkChild(XmlNode *child);

		/**
		 *	@brief 是否有子节点
		 *	@判断是否有子节点
		 */
		bool hasChildren() { return !children.empty(); }

		/**
		 *	@brief 是否有属性
		 *	@
		 */
		bool hasAtrribute() { return !this->attributes.empty(); }

		/**
		 *	@brief 是否是组节点
		 *	@判断是否是组节点
		 */
		bool isNode() { return value == TTXML_NODE; }

		/**
		 *	@brief 清理
		 *	@清理所有子节点,会释放他们的内存
		 */
		void clear();

		/**
		 *	@brief 查找本节点下可能存在的所有子节点中的一个
		 *	@param key 子节点键串
		 */
		XmlNode *getNode(const std::string &policy);

		/**
		 *	@brief 移除子节点
		 *	@param key 要移除的节点的键
		 *	@用于在只知道key的情况下移除节点,如果没有此节点,将不会做任何事情
		 */
		void removeChild(const std::string &key);

		/**
		 *	@brief 移除子节点
		 *	@param node 要移除的节点
		 *	@用于在知道节点指针的情况下移除节点,如果没有此节点,将不会做任何事情
		 */
		void removeChild(XmlNode *node);

		void removeChildByPool(const std::string &key);
		void removeChildByPool(XmlNode *node);

		/**
		 *	@brief 判断相等
		 *	@param node 另一个节点
		 *	@简单的判断,只会判断键值对是否相等,不会判断子节点
		 */
		bool isEqual(const XmlNode *node);

		/**
		 *	@brief 空节点
		 *	@判断是否为空节点
		 */
		bool isNull() const;

		/**
		 *	@brief 遍历子节点
		 *	@param function 函数地址
		 *	@一个遍历子节点的方法
		 */
		void foreachChild(const std::function<void(XmlNode *)> &function);

		/**
		 *	@brief 插入一个组节点或者值节点
		 *	@param node 要插入的节点
		 *	@插入值节点:如果存在,将覆盖原来的值,如果不存在,添加
		 *	@插入组节点:如果存在,将删除以前的,再添加,如果不存在,添加
		 */
		void insert(XmlNode *node);

		/**
		 *	@brief 改变一个值节点的值
		 *	@param key 键
		 *	@param value 值
		 *	@改变本节点上一个子值节点的值,如果没有,则在本节点上添加一个,如果为组节点,则不做任何事情
		 */
		void setValue(const std::string &key, const std::string &value);

		/**
		 *	@brief 设置本节点的值
		 *	@param v 各种类型的值
		 *	@设置本节点的值,可传任意参数
		 */
		template<typename T>
		void setLocalValue(T v)
		{
			value.clear();
			std::stringstream in;
			in << v;
			in >> value;
		}

		/**
		 *	@brief 获得本节点的值(转换快速但是判断不全面)
		 *	@获得本节点的值,得到任意数据类型(建议只在int float double bool之间转换)
		 */
		template<typename T>
		T getLocalValue()
		{
			if (typeid(T) == typeid(bool))
			{
				if (value == "false" || value == "FALSE")
				{
					return false;
				}
				else if (value == "true" || value == "TRUE")
				{
					return true;
				}

				auto temp = value.at(0);
				if (temp > '0' || temp <= '9')
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			T temp;
			std::stringstream out(value);
//			out << value;
			out >> temp;
			return temp;
		}

		/**	此方法未完成
		 *	@brief 复制一个节点的数据
		 *	@
		 */
		void copy(XmlNode *node);

		/**	此方法未完成
		 *	@brief 克隆本节点
		 *	@克隆本节点,包括子节点.
		 */
		XmlNode *clone();

		/**
		 *	@brief 结构大小统计
		 */
		unsigned int classSize();

		/**
		 *	@brief 切断与父节点的链接
		 *	@return 是否切断成功
		 *	@切断与父节点的链接,如果没有父节点,则返回false
		 */
		bool cutLinkFromParent();

		/**
		 *	@brief 添加属性
		 *	@param key属性键
		 *	@param value 属性值
		 */
		void addAttribute(const std::string &key, const std::string &value);

		/**
		 *	@brief 移除属性
		 *	@param key 属性键
		 */
		void removeAttribute(const std::string &key);

		/**
		 *	@brief 遍历属性
		 */
		void foreachAttribute(const std::function<void(std::string, std::string)> &function);

		/**
		 *	@brief 获得属性
		 */
		std::string getAttribute(const std::string &key);

		template<typename T>
		T getAttribute(const std::string &key)
		{
			if (this->attributes.empty())
			{
				return NULL;
			}

			auto it = this->attributes.find(key);
			if (it != this->attributes.end())
			{
				auto &tempValue = it->second;
				if (typeid(T) == typeid(bool))
				{
					if (tempValue == "false" || tempValue == "FALSE")
					{
						return false;
					}
					else if (tempValue == "true" || tempValue == "TRUE")
					{
						return true;
					}

					auto &temp = tempValue.at(0);
					if (temp > '0' || temp <= '9')
					{
						return true;
					}
					else
					{
						return false;
					}
				}

				T temp;
				std::stringstream out;
				out << tempValue;
				out >> temp;
				return temp;
			}
			else
			{
				return NULL;
			}
		}

		template<typename T>
		void setAttribute(const std::string &key, T v)
		{
			std::stringstream in;
			in << v;
			auto it = attributes.find(key);
			if (it != attributes.end())
			{
				in >> it->second;
			}
			else
			{
				in >> attributes[key];
			}
		}

		/**
		 *	@brief 获得本节点的子节点
		 */
//		std::list<XmlNode *> *getChildren() { return &children; }
		std::unordered_set<XmlNode *> *getChildren() { return &children; }

	public:
		std::string key;
		std::string value;
//		std::list<XmlNode *> children;
		std::unordered_set<XmlNode *> children;
		std::unordered_map<std::string, std::string> attributes;

	public:
		static XmlNode nullNode;
		static std::string errorValue;
		//	static TTFreeList<TTXML_Node> *MemPool;

	public:
		XmlNode();
		~XmlNode();

	private:
		friend class Xml;
		XmlNode(const std::string &k, const std::string &v = TTXML_NODE);

		/**
		 *	@brief 删除子节点的引用
		 *	@param node 子节点 值节点或组节点
		 */
		bool removeRef(XmlNode *node);

		/**
		 *	@brief 查找本节点的一个子节点
		 *	@param key 子节点键
		 */
		XmlNode *findLocalChild(const std::string &key);

	private:
		XmlNode *parent;
	};

}