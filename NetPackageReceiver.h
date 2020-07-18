#pragma once

#include <string>
#include <functional>
#include "NetData.h"
namespace tezcat
{
	struct NetPackageHead;
	struct NetPackageTail;
	class NetPackageReceiver
	{
	public:
		NetPackageReceiver();
		~NetPackageReceiver();

		//************************************
		// Method:    setPackage
		// FullName:  tezcat::NetPackageReceiver::setPackage
		// Access:    public 
		// Returns:   char *
		// Qualifier:
		// Parameter: size_t length
		//************************************
		char *setPackage(size_t length);

		//************************************
		// Method:    analysis
		// FullName:  tezcat::NetPackageReceiver::analysis
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::function<void
		// Parameter: char * data
		// Parameter: unsigned int & totalLength
		// Parameter: unsigned int nowLength
		// Parameter: > & function
		//************************************
		void analysis(const std::function<void(char *data, unsigned int &totalLength, unsigned int nowLength)> &function = nullptr);


		//************************************
		// Method:    readLength
		// FullName:  tezcat::NetPackageReceiver::readLength
		// Access:    public static 
		// Returns:   unsigned int
		// Qualifier:
		//************************************
		static unsigned int readLength() { return DefaultLength; }

		//************************************
		// Method:    clean
		// FullName:  tezcat::NetPackageReceiver::clean
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clean();

	public:
		//************************************
		// Method:    getString
		// FullName:  tezcat::NetPackageReceiver::getString
		// Access:    public 
		// Returns:   std::string
		// Qualifier:
		// Parameter: unsigned int index
		// Parameter: unsigned int length
		//************************************
		std::string getString(unsigned int index, unsigned int length);

		//************************************
		// Method:    getNumber
		// FullName:  tezcat::NetPackageReceiver::getNumber
		// Access:    public 
		// Returns:   ::type
		// Qualifier:
		// Parameter: unsigned int index
		//************************************
		template<typename T>
		typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value, T>::value_type getNumber(unsigned int index)
		{
			T result;
			memcpy(&result, m_Package + sizeof(NetPackageHead) + index, sizeof(T));
			return result;
		}

		NetPackageHead *getHead() { return m_Head; }

	private:
		void growBuffer(size_t length);

	private:
		char *m_Package;
		unsigned int m_TotalLength;
		unsigned int m_NowLength;
		bool m_IsFull;
		NetPackageHead *m_Head;
		NetPackageTail *m_Tail;

	private:
		static unsigned int DefaultLength;
		static unsigned int GrowFactor;
	};
}