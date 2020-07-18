/***************************************************************************************************************
*  Xml.h
*  作者 : 特兹卡特(Tezcat)
*  功能 : XML解析
*  时间 : 14-1-10.
*  说明 : 1.数据组织结构,可以导出成XML文件
*        2.每个节点的内存由其父节点管理,不用手动管理内存
*        3.所有节点必须全部通过TTXML,TTXML_Node类create出来,不能使用new或者对象
***************************************************************************************************************/
#pragma once

#include "tinyxml2.h"

#include <string>
#include <unordered_map>
#include <functional>
#include "XmlGlobal.h"
#include "XmlNode.h"

namespace tezcat
{

	struct XmlGlobalInfo
	{
		XmlNode *rootNode;
		std::string filePath;

		XmlGlobalInfo() : rootNode(nullptr), filePath(TTXML_Dont_Save) {}

		static XmlGlobalInfo *create()
		{
			return new XmlGlobalInfo();
		}

		void recycle()
		{
			delete this;
		}
	};

	class Xml
	{
	public:
		Xml();
		~Xml();

		/**
		 *	@brief 判断文件是否存在
		 *	@param file 文件路径
		 */
		bool isExist(const std::string &file);

		/**
		 *	@brief 读取XML文件
		 *	@param file 文件路径
		 *	@param root_key 根节点键 默认值为RootNode
		 *	@param root_value 根节点值 默认值为node
		 */
		bool loadFile(const std::string &file, const std::string &root_key = TTXML_DEFAULT_ROOT_NODE, const std::string &root_value = TTXML_NODE);

		/**
		 *	@brief 格式化标准XML字符串
		 *	@param content xml全文本
		 *	@param root_key 根节点键 默认值为RootNode
		 *	@param root_value 根节点值 默认值为node
		 */
		bool loadFileForData(const std::string &content, const std::string &root_key = TTXML_DEFAULT_ROOT_NODE, const std::string &root_value = TTXML_NODE);

		/**
		* Method:    loadFileFromTTPFile
		* FullName:  tezcat::Xml::loadFileFromTTPFile
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string & key
		* Parameter: const std::string & file
		* Parameter: const std::string & root_key
		* Parameter: const std::string & root_value
		* Versions : V
		* Since    : V
		*/
		bool loadFileFromCodeFile(const std::string &key, const std::string &file, const std::string &root_key = TTXML_DEFAULT_ROOT_NODE, const std::string &root_value = TTXML_NODE);

		/**
		 *	@brief 创建一个XML数据结构
		 *	@param file 文件全路径
		 *	@param root_key 根节点键 默认值为RootNode
		 *	@param root_value 根节点值 默认值为node
		 */
		void createXML(const std::string &file, const std::string &root_key = TTXML_DEFAULT_ROOT_NODE, const std::string &root_value = TTXML_NODE);

		/**
		 *	@brief 创建一个自由节点
		 *	@param key 节点键
		 *	@param value 节点值 默认为创建组节点
		 */
		XmlNode *createNode(const std::string &key, const std::string &value = TTXML_NODE);

		/**
		 *	@brief
		 */
		void clearOneRootNode(const std::string &root_key);

		/**
		 *	@brief 清理整个XML
		 */
		void clear();

		/**
		 *	@brief 保存一个节点
		 * @param root_key 需要保存的跟节点名
		 *	@输入保存路径保存数据
		 */
		void save(const std::string &root_key);

		/**
		 *	@brief 保存所有
		 *	@用创建好的路径快速保存
		 */
		void save();

		/**
		* Method:    saveByCode
		* FullName:  tezcat::Xml::saveByCode
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & key
		* Versions : V
		* Since    : V
		*/
		void saveByCode(const std::string &key);

		void getXmlString(XmlNode *node);

		/**
		 *	@brief 整个结构大小
		 */
		std::string treeSize();

		/**
		 *	@brief 打印
		 */
		void printXML(int(*func)(const char *, ...) = printf);

		/**
		 *	@brief 获取一个节点
		 * @param root_node 搜索根节点
		 * @param child_list 搜索子节点串
		 */
		XmlNode *getNode(const std::string &child_list);

		/**
		 *	@brief 获取跟节点
		 *	@param root_key 根节点名称
		 */
		XmlNode *getRootNode(const std::string &root_key = TTXML_DEFAULT_ROOT_NODE);

		/**
		 *	@brief 设置保存位置
		 *	@param root_node 根节点名称
		 *	@param 保存路径
		 *	@return 返回是否保存成功
		 */
		bool setFilePath(const std::string &root_node, const std::string &path);

		/**
		 *	@brief 初始化
		 */
		XmlNode *createRootNode(const std::string &root_key, const std::string &root_value = TTXML_NODE);

		/**
		 *	@brief
		 */
		void insertNode(XmlNode *node);

		std::string &getXmlString();

	private:
		/**
		 *	@brief 解析
		 */
		void analyze(tttinyxml2::XMLElement *root, XmlNode *node);

		/**
		 *	@brief 转化到XML
		 */
//		void loadToXML(const std::list<XmlNode *> &node, tttinyxml2::XMLDocument &doc, tttinyxml2::XMLNode *like_node = nullptr);
		void loadToXML(const std::unordered_set<XmlNode *> &node, tttinyxml2::XMLDocument &doc, tttinyxml2::XMLNode *like_node = nullptr);


		/**
		 *	@brief 格式化打印
		 */
		void formatPrint(XmlNode *node, int(*func)(const char *, ...));

		/**
		 *	@brief
		 */
		bool hasRootNode(const std::string &key);

	private:
		int m_iLayer;
		std::unordered_map<std::string, XmlGlobalInfo *> m_GlobalNodes;
		XmlNode *m_RootNode;
		std::string m_FileName;
		std::string m_XmlString;

	};

}