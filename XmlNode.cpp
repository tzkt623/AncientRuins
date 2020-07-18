#include "XmlNode.h"
#include <sstream>

namespace tezcat
{

	XmlNode XmlNode::nullNode("NullNode", "Null");
	std::string XmlNode::errorValue = "_tt_xml_error_";

	XmlNode::XmlNode() :
		parent(nullptr)
	{
		key.clear();
		value.clear();
		children.clear();
		attributes.clear();
	}

	XmlNode::XmlNode(const std::string &k, const std::string &v) :
		key(k),
		value(v),
		parent(nullptr)
	{
		children.clear();
		attributes.clear();
	}

	XmlNode::~XmlNode()
	{
		//清理子节点
		clear();
	}


	void XmlNode::linkChild(XmlNode *child)
	{
		//	printf("node %s add a child %s\n", this->key.c_str(), child->key.c_str());
#if TT_Debug
		printf("node %s add a child %s\n", this->key.c_str(), child->key.c_str());
#endif
		child->parent = this;
//		this->children.push_back(child);
		this->children.insert(child);
	}

	void XmlNode::clear()
	{
#if TT_Debug
		printf("node %s clear!\n", this->key.c_str());
#endif
		//清除属性
		this->attributes.clear();

		if (this->hasChildren())
		{
			auto it = this->children.begin();
			while (it != this->children.end())
			{
				//删除节点
				//			delete (*it);
				//			MemPool->freeT((*it));
				(*it)->recycle();
				//删除索引
				//			this->children.erase(it++);
				++it;
			}
			//删除索引
			this->children.clear();
		}
	}

	XmlNode * XmlNode::findLocalChild(const std::string &key)
	{
#if TT_Debug
		printf("node %s finding %s\n", this->key.c_str(), key.c_str());
#endif
		auto it = children.begin();
		while (it != children.end())
		{
			if ((*it)->key == key)
			{
				return (*it);
			}
			++it;
		}

		return &nullNode;
	}

	void XmlNode::removeChild(const std::string &key)
	{
#if TT_Debug
		printf("node %s remove child %s\n", this->key.c_str(), key.c_str());
#endif

		auto temp = this->findLocalChild(key);
		if (!temp->isNull())
		{
			//删除链表里temp节点的引用
			this->removeRef(temp);
			delete temp;
		}
	}

	void XmlNode::removeChild(XmlNode *node)
	{
#if TT_Debug
		printf("node %s remove child %s\n", this->key.c_str(), node->key.c_str());
#endif
		if (!node->isNull())
		{
			//删除链表里temp节点的引用
			this->removeRef(node);
			delete node;
		}
	}

	void XmlNode::foreachChild(const std::function<void(XmlNode *)> &function)
	{
		auto it = this->children.begin();
		while (it != this->children.end())
		{
			function((*it));
			if ((*it)->hasChildren())
			{
				(*it)->foreachChild(function);
			}
			++it;
		}
	}

	bool XmlNode::removeRef(XmlNode *node)
	{
		auto it = this->children.begin();
		while (it != this->children.end())
		{
			if ((*it) == node)
			{
				this->children.erase(it);
				return true;
			}
			++it;
		}

		return false;
	}

	bool XmlNode::isEqual(const XmlNode *node)
	{
		if (this->key == node->key && this->value == node->value)
		{
			return true;
		}
		return false;
	}

	bool XmlNode::isNull() const
	{
		if (this->key == nullNode.key && this->value == nullNode.value)
		{
			return true;
		}
		return false;
	}

	XmlNode *XmlNode::simpleCreate(const std::string &k, const std::string &v /*= TTXML_NODE*/)
	{
		//	auto newNode = new TTXML_Node(k, v);
		auto newNode = XmlNode::create();
		newNode->key = k;
		newNode->value = v;
		this->linkChild(newNode);
		return newNode;
	}

	XmlNode * XmlNode::clone()
	{
		//	TTXML_Node *node = new TTXML_Node(this->key, this->value);
		XmlNode *node = XmlNode::create();
		node->key = this->key;
		node->value = this->value;

		if (!this->attributes.empty())
		{
			this->foreachAttribute([&](std::string k, std::string v)
			{
				node->attributes[k] = v;
			});
		}

		this->foreachChild([&](XmlNode *child)
		{
			auto childnode = child->clone();
			node->linkChild(childnode);
		});

		return node;
	}

	void XmlNode::insert(XmlNode *node)
	{
		// 	if (node->parent != nullptr)
		// 	{
		// 		if (!node->cutLinkFromParent()) return;
		// 	}

		auto temp_node = this->findLocalChild(node->key);

		//如果插入的是一组数据
		if (node->isNode())
		{
			if (!temp_node->isNull())
			{
				this->removeChild(temp_node);
				this->linkChild(node);
			}
			else
			{
				this->linkChild(node);
			}
		}
		//如果是单个数据
		else
		{
			//如果不是空节点,删除原来的节点,再连接
			if (!temp_node->isNull())
			{
				this->removeChild(temp_node);
			}
			this->linkChild(node);
		}
	}

	void XmlNode::setValue(const std::string &key, const std::string &value)
	{
		auto temp = this->findLocalChild(key);
		if (!temp->isNull() && !temp->isNode())
		{
			temp->value = value;
		}
		else
		{
			//		auto value_node = new TTXML_Node(key, value);
			auto value_node = XmlNode::create();
			value_node->key = key;
			value_node->value = value;
			this->linkChild(value_node);
		}
	}

	unsigned int XmlNode::classSize()
	{
		auto size = sizeof(XmlNode);
		if (this->hasChildren())
		{
			this->foreachChild([&](XmlNode *node)
			{
				size += node->classSize();
			});
		}
		return size;
	}

	bool XmlNode::cutLinkFromParent()
	{
		if (parent)
		{
			if (parent->removeRef(this))
			{
				parent = nullptr;
			}
			return true;
		}
		return false;
	}

	void XmlNode::addAttribute(const std::string &key, const std::string &value)
	{
		this->attributes[key] = value;
	}

	void XmlNode::foreachAttribute(const std::function<void(std::string, std::string)> &function)
	{
		if (this->attributes.empty())
		{
			return;
		}

		auto it = this->attributes.begin();
		while (it != this->attributes.end())
		{
			function(it->first, it->second);
			++it;
		}
	}

	std::string XmlNode::getAttribute(const std::string &key)
	{
		if (this->attributes.empty())
		{
			return errorValue;
		}

		auto it = this->attributes.find(key);
		if (it != this->attributes.end())
		{
			return it->second;
		}

		return errorValue;
	}

	void XmlNode::removeAttribute(const std::string &key)
	{
		auto it = this->attributes.find(key);
		if (it != this->attributes.end())
		{
			this->attributes.erase(it);
		}
	}

	XmlNode * XmlNode::getNode(const std::string &policy)
	{
		XmlNode *temp = this;

		std::string buildString;
		for (unsigned int i = 0; i < policy.length(); i++)
		{
			char ch = policy[i];
			if (ch == ',')
			{
				temp = temp->findLocalChild(buildString);
				buildString.clear();
			}
			else
			{
				buildString += ch;
			}
		}

		if (!buildString.empty())
		{
			temp = temp->findLocalChild(buildString);
		}

		return temp;
	}

	void XmlNode::copy(XmlNode *node)
	{
// 		this->clear();
// 
// 		this->key = node->key;
// 		this->value = node->value;
// 		std::copy(node->children.begin(), node->children.end(), std::back_inserter(this->children));
// 		node->foreachAttribute([&](std::string k, std::string v)
// 		{
// 			this->attributes[k] = v;
// 		});
	}

	void XmlNode::removeChildByPool(XmlNode *node)
	{
#if TT_Debug
		printf("node %s remove child %s\n", this->key.c_str(), node->key.c_str());
#endif
		if (!node->isNull())
		{
			//删除链表里temp节点的引用
			this->removeRef(node);
			node->recycle();
		}
	}

	void XmlNode::removeChildByPool(const std::string &key)
	{
#if TT_Debug
		printf("node %s remove child %s\n", this->key.c_str(), key.c_str());
#endif
		auto temp = this->findLocalChild(key);
		if (!temp->isNull())
		{
			//删除链表里temp节点的引用
			this->removeRef(temp);
			temp->recycle();
		}
	}
}
