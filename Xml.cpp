#include "Xml.h"
#include "Encryption.h"

namespace tezcat
{
	Xml::Xml() :
		m_RootNode(nullptr),
		m_iLayer(0)
	{

	}

	Xml::~Xml()
	{
		printf("TTXML delete!\n");
		this->clear();
	}

	XmlNode *Xml::createRootNode(const std::string &root_key, const std::string &root_value)
	{
		m_iLayer = 0;
// 		if (this->hasRootNode(root_key))
// 		{
// 			if (m_RootNode != nullptr)
// 			{
// 				m_RootNode->recycle();
// 				m_RootNode = nullptr;
// 			}
// 		}
// 		m_GlobalNodes[root_key] = XmlGlobalInfo::create();
// 		m_RootNode = XmlNode::create();
// 		//	m_RootNode = new TTXML_Node();
// 		m_RootNode->key = root_key;
// 		m_RootNode->value = root_value;
		m_RootNode = createNode(root_key, root_value);
//		m_RootNode = nullptr;
		printf("create node %s\n", root_key.c_str());

		return m_RootNode;
	}

	XmlNode * Xml::createNode(const std::string &key, const std::string &value /*= TTXML_NODE*/)
	{
		auto temp = XmlNode::create();
		temp->key = key;
		temp->value = value;
		return temp;

		//	return new TTXML_Node(key, value);
	}

	void Xml::createXML(const std::string &file, const std::string &root_key, const std::string &root_value)
	{
		this->createRootNode(root_key, root_value);
		//	m_FilePath = file;
		m_FileName = file;
	}

	bool Xml::isExist(const std::string &file)
	{
		tttinyxml2::XMLDocument doc;
		auto errorcode = doc.LoadFile(file.c_str());
		if (errorcode == tttinyxml2::XML_ERROR_FILE_NOT_FOUND)
		{
			return false;
		}

		return true;
	}

	bool Xml::loadFile(const std::string &file, const std::string &root_key, const std::string &root_value)
	{
		this->createRootNode(root_key, root_value);
		tttinyxml2::XMLDocument doc;
		auto errorcode = doc.LoadFile(file.c_str());

		switch (errorcode)
		{
		case tttinyxml2::XML_NO_ERROR:
			//		m_FilePath = file;
			m_FileName = file;
			this->analyze(doc.FirstChildElement(), m_RootNode);
			return true;
			break;
		case tttinyxml2::XML_NO_ATTRIBUTE:
			break;
		case tttinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			break;
		case tttinyxml2::XML_ERROR_FILE_NOT_FOUND:
			return false;
			break;
		case tttinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			break;
		case tttinyxml2::XML_ERROR_FILE_READ_ERROR:
			break;
		case tttinyxml2::XML_ERROR_ELEMENT_MISMATCH:
			break;
		case tttinyxml2::XML_ERROR_PARSING_ELEMENT:
			break;
		case tttinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			break;
		case tttinyxml2::XML_ERROR_IDENTIFYING_TAG:
			break;
		case tttinyxml2::XML_ERROR_PARSING_TEXT:
			break;
		case tttinyxml2::XML_ERROR_PARSING_CDATA:
			break;
		case tttinyxml2::XML_ERROR_PARSING_COMMENT:
			break;
		case tttinyxml2::XML_ERROR_PARSING_DECLARATION:
			break;
		case tttinyxml2::XML_ERROR_PARSING_UNKNOWN:
			break;
		case tttinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			break;
		case tttinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			break;
		case tttinyxml2::XML_ERROR_PARSING:
			break;
		case tttinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			break;
		case tttinyxml2::XML_NO_TEXT_NODE:
			break;
		default:
			break;
		}

		return false;
	}

	bool Xml::loadFileForData(const std::string &content, const std::string &root_key, const std::string &root_value)
	{
		if (content.empty())
		{
			return false;
		}

		//删除字符串里的注释
// 		for (unsigned int i = 0; i < content.size(); ++i)
// 		{
// 			auto flag1 = content.at(i);
// 			if (flag1 == '<')
// 			{
// 				auto flag2 = content.at(i + 1);
// 				if (flag2 == '!')
// 				{
// 					for (unsigned int j = i + 4; j < content.size(); ++j)
// 					{
// 						auto flag3 = content.at(j);
// 						if (flag3 == '-')
// 						{
// 							auto flag4 = content.at(j + 1);
// 							auto flag5 = content.at(j + 2);
// 							if (flag4 == '-' && flag5 == '>')
// 							{
// 								content.erase(i, j + 2 - i + 1);
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}

		this->createRootNode(root_key, root_value);
		tttinyxml2::XMLDocument doc;
		if (tttinyxml2::XMLError::XML_NO_ERROR == doc.Parse(content.c_str(), content.size()))
		{
			this->analyze(doc.FirstChildElement(), m_RootNode);
			return true;
		}
		return false;
	}

	bool Xml::loadFileFromCodeFile(const std::string &key, const std::string &file, const std::string &root_key /*= TTXML_DEFAULT_ROOT_NODE*/, const std::string &root_value /*= TTXML_NODE*/)
	{
		if (file.empty())
		{
			return false;
		}

		tezcat::Encryption decode(key);
		decode.progress(file);

		this->createRootNode(root_key, root_value);
		tttinyxml2::XMLDocument doc;
		if (tttinyxml2::XMLError::XML_NO_ERROR == doc.Parse((char *)decode.getDataBuffer(), decode.getLength()))
		{
			this->analyze(doc.FirstChildElement(), m_RootNode);
			return true;
		}
		return false;
	}

	void Xml::analyze(tttinyxml2::XMLElement *root, XmlNode *node)
	{
		if (root == nullptr)
		{
			return;
		}

// 		if (node == nullptr)
// 		{
// 			m_RootNode = XmlNode::create();
// 		}

		//创建一个节点
		auto rootNode = XmlNode::create();
		rootNode->key = root->Name();
		if (root->GetText()) rootNode->value = root->GetText();
		else rootNode->value = TTXML_NODE;

		//遍历解析节点属性,并加入节点
		const tttinyxml2::XMLAttribute  *rootAttribute = root->FirstAttribute();
		while (rootAttribute)
		{
			const char *attributeName = rootAttribute->Name();
			const char *attributeValue = rootAttribute->Value();
			rootNode->addAttribute(attributeName, attributeValue);
			rootAttribute = rootAttribute->Next();
		}

		node->linkChild(rootNode);

		//递归遍历子节点
		auto child = root->FirstChildElement();
		if (child != nullptr)
		{
			analyze(child, rootNode);
		}

		//递归遍历同级节点
		auto nextSibling = root->NextSiblingElement();
		if (nextSibling != nullptr)
		{
			analyze(nextSibling, node);
		}
	}

	void Xml::loadToXML(const std::unordered_set<XmlNode *> &node, tttinyxml2::XMLDocument &doc, tttinyxml2::XMLNode *like_node)
	{
		auto it = node.begin();
		while (it != node.end())
		{
			auto temp = (*it);
			auto rootNode = doc.NewElement(temp->key.c_str());
			like_node->LinkEndChild(rootNode);
			temp->foreachAttribute([&](std::string key, std::string value)
			{
#if TT_Debug
				printf("%s,%s\n", key.c_str(), value.c_str());
#endif
				rootNode->SetAttribute(key.c_str(), value.c_str());
			});

			if (temp->value == TTXML_NODE)
			{
				this->loadToXML(temp->children, doc, rootNode);
			}
			else
			{
				rootNode->LinkEndChild(doc.NewText(temp->value.c_str()));
			}
			++it;
		}
	}

	void Xml::save(const std::string &root_key)
	{
		tttinyxml2::XMLDocument doc;
		doc.LinkEndChild(doc.NewDeclaration());
		this->loadToXML(m_RootNode->children, doc, &doc);
		doc.SaveFile(m_FileName.c_str());
//		m_RootNode->clear();
	}

	void Xml::save()
	{

		tttinyxml2::XMLDocument doc;
		doc.LinkEndChild(doc.NewDeclaration());
		this->loadToXML(m_RootNode->children, doc, &doc);
		doc.SaveFile(m_FileName.c_str());
	}


	void Xml::saveByCode(const std::string &key)
	{
		tttinyxml2::XMLDocument doc;
		doc.LinkEndChild(doc.NewDeclaration());
		this->loadToXML(m_RootNode->children, doc, &doc);

		tezcat::Encryption code(key);
		code.progressString(getXmlString());
		code.save(m_FileName);
	}

	void Xml::clearOneRootNode(const std::string &root_key)
	{
// 		auto it = m_GlobalNodes.find(root_key);
// 		if (it != m_GlobalNodes.end())
// 		{
// 			printf("clear one root node %s\n", root_key.c_str());
// 			auto temp = it->second;
// 			temp->rootNode->recycle();
// 			temp->recycle();
// 			m_GlobalNodes.erase(it);
// 		}
	}

	void Xml::clear()
	{
// 		auto it = m_GlobalNodes.begin();
// 		while (it != m_GlobalNodes.end())
// 		{
// 			auto temp = it->second;
// 			temp->rootNode->recycle();
// 			temp->recycle();
// 			++it;
// 		}

		m_RootNode->recycle();
		if (m_RootNode != nullptr)
		{
			delete m_RootNode;
		}
	}

	XmlNode *Xml::getNode(const std::string &child_list)
	{
		return m_RootNode->getNode(child_list);
	}

	void Xml::printXML(int(*func)(const char *, ...))
	{
		printf("===========XML==================BEGIN==================\n");
// 		auto it = m_GlobalNodes.begin();
// 		while (it != m_GlobalNodes.end())
// 		{
// 			this->formatPrint(it->second->rootNode);
// 			++it;
// 		}
		this->formatPrint(m_RootNode, func);

		printf("===========XML==================END====================\n");
		m_iLayer = 0;
	}

	void Xml::formatPrint(XmlNode *node, int(*func)(const char *, ...))
	{
		auto it = node->children.begin();
		while (it != node->children.end())
		{
			if ((*it)->isNode())
			{
				for (int i = 0; i < m_iLayer; i++)
				{
					printf("\t");
				}

				if ((*it)->hasAtrribute())
				{
					func("<%s ", (*it)->key.c_str());
					(*it)->foreachAttribute([&](std::string key, std::string value)
					{
						func("%s=\"%s\" ", key.c_str(), value.c_str());
					});
					func(">\n");
				}
				else
				{
					func("<%s>\n", (*it)->key.c_str());
				}
			}
			else
			{
				for (int i = 0; i < m_iLayer; i++)
				{
					func("\t");
				}
				func("<%s>%s</%s>\n", (*it)->key.c_str(), (*it)->value.c_str(), (*it)->key.c_str());
			}

			if ((*it)->hasChildren())
			{
				++m_iLayer;
				formatPrint((*it), func);
			}

			if ((*it)->isNode())
			{
				for (int i = 0; i < m_iLayer; i++)
				{
					func("\t");
				}
				func("</%s>\n", (*it)->key.c_str());
			}
			++it;
		}
		--m_iLayer;
	}

	std::string Xml::treeSize()
	{
		/*
		std::string temp;
		auto size = m_RootNode->classSize();
		//Byte
		temp = std::to_string(size);
		temp += "B";
		//KB
		if (size > 1024)
		{
		size /= 1024;
		temp = std::to_string(size);
		temp += "KB";
		}
		//MB
		if (size > 1024)
		{
		size /= 1024;
		temp = std::to_string(size);
		temp += "MB";
		}
		//GB
		if (size > 1024)
		{
		size /= 1024;
		temp = std::to_string(size);
		temp += "GB";
		}
		return temp;
		*/
		return "KB";
	}

	bool Xml::hasRootNode(const std::string &key)
	{
		auto it = m_GlobalNodes.find(key);
		return it != m_GlobalNodes.end();
	}

	XmlNode * Xml::getRootNode(const std::string &root_key)
	{
// 		if (this->hasRootNode(root_key))
// 		{
// 			return m_RootNode;
// 		}
// 
// 		return &XmlNode::nullNode;

		return m_RootNode;
	}

	bool Xml::setFilePath(const std::string &root_node, const std::string &path)
	{
		if (this->hasRootNode(root_node))
		{
			m_GlobalNodes[root_node]->filePath = path;
			return true;
		}

		return false;
	}

	void Xml::insertNode(XmlNode *node)
	{
		if (this->hasRootNode(node->key))
		{
			m_GlobalNodes[node->key]->rootNode->recycle();
			m_GlobalNodes[node->key]->rootNode = node;
		}
		else
		{
			auto temp = XmlGlobalInfo::create();
			temp->rootNode = node;
			m_GlobalNodes[node->key] = temp;
		}
	}

	void Xml::getXmlString(XmlNode *node)
	{
		auto it = node->children.begin();
		while (it != node->children.end())
		{
			if ((*it)->isNode())
			{

				if ((*it)->hasAtrribute())
				{
					m_XmlString += "<" + (*it)->key;
//					func("<%s ", (*it)->key.c_str());
					(*it)->foreachAttribute([&](std::string key, std::string value)
					{
//						func("%s=\"%s\" ", key.c_str(), value.c_str());
						m_XmlString += key + "=\"" + value + "\" ";
					});
//					func(">\n");
					m_XmlString += ">";
				}
				else
				{
//					func("<%s>\n", (*it)->key.c_str());
					m_XmlString += "<" + (*it)->key + ">";
				}
			}
			else
			{
//				func("<%s>%s</%s>\n", (*it)->key.c_str(), (*it)->value.c_str(), (*it)->key.c_str());
				m_XmlString += "<" + (*it)->key + ">" + (*it)->value + "</" + (*it)->key + ">";
			}

			if ((*it)->hasChildren())
			{
				getXmlString((*it));
			}

			if ((*it)->isNode())
			{
//				func("</%s>\n", (*it)->key.c_str());
				m_XmlString += "</" + (*it)->key + ">";
			}
			++it;
		}
	}

	std::string &Xml::getXmlString()
	{
		m_XmlString.clear();
		m_XmlString += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		this->getXmlString(m_RootNode);
		return m_XmlString;
	}



}