#pragma once

#include "NetData.h"
#include <string>

namespace tezcat
{
	struct NetPackageHead;
	struct NetPackageTail;
	class NetPackageBuilder
	{
	public:
		NetPackageBuilder();
		~NetPackageBuilder();

		//************************************
		// Method:    beginCreatePackage
		// FullName:  tezcat::NetPackageBuilder::beginCreatePackage
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: Byte version
		// Parameter: NetPackageType type
		//************************************
		void beginCreatePackage(Byte version, NetPackageType type);

		//************************************
		// Method:    endCreatePackage
		// FullName:  tezcat::NetPackageBuilder::endCreatePackage
		// Access:    public 
		// Returns:   char *
		// Qualifier:
		//************************************
		void endCreatePackage();

		//************************************
		// Method:    getPackageLength
		// FullName:  tezcat::NetPackageBuilder::getPackageLength
		// Access:    public 
		// Returns:   unsigned int
		// Qualifier:
		//************************************
		unsigned int getPackageLength() { return m_NowLength; }

		//************************************
		// Method:    getPackage
		// FullName:  tezcat::NetPackageBuilder::getPackage
		// Access:    public 
		// Returns:   char *
		// Qualifier: const
		//************************************
		char * getPackage() const { return m_Package; }

	public:

		//************************************
		// Method:    putNumber
		// FullName:  tezcat::NetPackageBuilder::putNumber
		// Access:    public 
		// Returns:   ::type
		// Qualifier:
		// Parameter: T value
		//************************************
		template<typename T>
		typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value, void>::type putNumber(T value)
		{
// 			char *temp = (char *)&value;
// 			size_t len = sizeof(T);
//			value = toBigEndian(value);
			this->growBuffer(sizeof(T));
			memcpy(m_Package + sizeof(NetPackageHead), &value, sizeof(T));
			m_NowLength += sizeof(T);
		}

		//************************************
		// Method:    putString
		// FullName:  tezcat::NetPackageBuilder::putString
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & value
		//************************************
		void putString(const std::string &value);

	private:
		//************************************
		// Method:    growBuffer
		// FullName:  tezcat::NetPackageBuilder::growBuffer
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: size_t length
		//************************************
		void growBuffer(size_t length);

		//************************************
		// Method:    switchCode
		// FullName:  tezcat::NetPackageBuilder::switchCode
		// Access:    private 
		// Returns:   char *
		// Qualifier:
		// Parameter: void * value
		//************************************
		char *switchCode(void *value);


	private:
		char *m_Package;
		unsigned int m_NowLength;
		unsigned int m_TotalLength;
		NetPackageHead *m_Head;
		NetPackageTail *m_Tail;
	private:
		static unsigned int DefaultLength;
		static unsigned int GrowFactor;
	};
}