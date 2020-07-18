#include "NetPackageBuilder.h"
#include <iostream>
#include <stdexcept>

namespace tezcat
{
	unsigned int NetPackageBuilder::DefaultLength = 50;
	unsigned int NetPackageBuilder::GrowFactor = 2;


	NetPackageBuilder::NetPackageBuilder() :
		m_Package(nullptr), m_NowLength(0), m_TotalLength(0), m_Head(new NetPackageHead()), m_Tail(new NetPackageTail())
	{
	}

	NetPackageBuilder::~NetPackageBuilder()
	{
	}

	void NetPackageBuilder::beginCreatePackage(Byte version, NetPackageType type)
	{
		if (m_Package == nullptr)
		{
			m_Package = new char[DefaultLength];
			m_TotalLength = DefaultLength;
		}
		memset(m_Package, 0x00, m_TotalLength);

		m_NowLength = sizeof(NetPackageHead);
		m_Head->tag = HeadTag;
		m_Head->version = version;
		m_Head->type = type;

		m_Tail->tag = TailTag;
	}

	void NetPackageBuilder::putString(const std::string &value)
	{
		auto len = value.size();
		this->growBuffer(len);
		memcpy(m_Package + m_NowLength, value.c_str(), len);
		m_NowLength += len;
	}

	void NetPackageBuilder::endCreatePackage()
	{
		if (m_NowLength == 0)
		{
			throw std::logic_error("Length must be bigger than 0");
		}

		m_Head->length = m_NowLength - sizeof(NetPackageHead);
		memcpy(m_Package, m_Head, sizeof(NetPackageHead));
		this->growBuffer(sizeof(NetPackageTail));
		memcpy(m_Package + m_NowLength, m_Tail, sizeof(NetPackageTail));
		m_NowLength += sizeof(NetPackageTail);

		std::cout << "·¢ËÍ°ü³¤:" << m_NowLength << std::endl;
	}

	void NetPackageBuilder::growBuffer(size_t length)
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

	char * NetPackageBuilder::switchCode(void *value)
	{
		return nullptr;
	}
}

