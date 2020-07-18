#include "NetPackageReceiver.h"

#include <iostream>

namespace tezcat
{
	unsigned int NetPackageReceiver::GrowFactor = 2;
	unsigned int NetPackageReceiver::DefaultLength = 50;
	NetPackageReceiver::NetPackageReceiver() :
		m_Package(nullptr), m_TotalLength(0), m_NowLength(0), m_Head(new NetPackageHead()), m_Tail(new NetPackageTail())
	{
	}

	NetPackageReceiver::~NetPackageReceiver()
	{
	}

	char *NetPackageReceiver::setPackage(size_t length)
	{
		//第一次启动,初始化
		if (m_Package == nullptr)
		{
			m_Package = new char[DefaultLength];
			memset(m_Package, 0x00, DefaultLength);
			m_TotalLength = DefaultLength;
		}
		else if (length != 0)
		{
			this->growBuffer(length);
			m_NowLength += length;
		}

		return m_Package + m_NowLength;
	}

	void NetPackageReceiver::analysis(const std::function<void(char *data, unsigned int &totalLength, unsigned int nowLength)> &function)
	{
		std::cout << m_NowLength << std::endl;

		memcpy(m_Head, m_Package, sizeof(NetPackageHead));
		memcpy(m_Tail, m_Package + sizeof(NetPackageHead) + m_Head->length, sizeof(NetPackageTail));

		std::cout << "包头校验:" << (unsigned int)m_Head->tag << std::endl;
		std::cout << "版本号:" << (unsigned int)m_Head->version << std::endl;
		std::cout << "类型:" << (unsigned int)m_Head->type << std::endl;
		std::cout << "数据长:" << m_Head->length << std::endl;

		std::cout << "包尾校验:" << (unsigned int)m_Tail->tag << std::endl;

		if (m_Head->tag == HeadTag && m_Tail->tag == TailTag)
		{
			if (function != nullptr)
			{
				function(m_Package, m_TotalLength, m_NowLength);
			}
		}
		else
		{
			std::cout << "数据包不正确" << std::endl;
			this->clean();
		}
	}

	std::string NetPackageReceiver::getString(unsigned int index, unsigned int length)
	{
		char *temp = new char[length + 1];
		memset(temp, 0x00, length + 1);
		memcpy(temp, m_Package + sizeof(NetPackageHead) + index, length);
		return temp;
	}

	void NetPackageReceiver::growBuffer(size_t length)
	{
		if (m_TotalLength - m_NowLength - 1 < length)
		{
			auto *tempData = m_Package;
			auto tempLength = m_TotalLength;
			m_TotalLength += length;
			m_Package = new char[m_TotalLength];
			memset(m_Package, 0x00, m_TotalLength);
			memcpy(m_Package, tempData, tempLength);
			delete[] tempData;
		}
	}

	void NetPackageReceiver::clean()
	{
		m_NowLength = sizeof(NetPackageHead);
		memset(m_Package, 0x00, m_TotalLength);
	}

}

