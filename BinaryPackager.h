#pragma once

//===================================================================================
// 文件 : BinaryPackager.h
// 功能 : 文件2进制打包程序
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-8-6
// 使用 : 解包:输入包名,不带扩展名;  封包:载入所有文件,然后打包,会自动生成数据结构文件和打包数据
//===================================================================================

#include <list>
#include <string>

namespace tezcat
{

	class BinaryPackager
	{
    public:
		struct Item
		{
			Item() :data(nullptr) {}

			~Item() { if (data){ delete[] data; } }

			unsigned index;
			std::string path;
			std::string name;
			std::string extension;
//			unsigned int length;
            unsigned long long int length;
			unsigned char *data;
		};

	public:
        BinaryPackager(const std::string &key);
		BinaryPackager();
		~BinaryPackager();

		/**
		* Method:    package
		* FullName:  tezcat::BinaryPackager::package
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string file
		* Versions : V
		* Since    : V
		*/
		bool package(const std::string file);

		/**
		* Method:    unPackage
		* FullName:  tezcat::BinaryPackager::unPackage
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string file
		* Versions : V
		* Since    : V
		*/
		bool unPackage(const std::string file, const std::string &path = "");

		/**
		* Method:    loadOneItem
		* FullName:  tezcat::BinaryPackager::loadOneItem
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string file
		* Versions : V
		* Since    : V
		*/
        BinaryPackager::Item *loadOneItem(const std::string file);

		/**
		* Method:    clear
		* FullName:  tezcat::BinaryPackager::clear
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void clear();

        bool hasData();

//        std::string BinaryPackager::Key() const { return m_Key; }

        void setKey(const std::string &Key) { m_Key = Key; }

    private:
        std::list<Item *> m_DataBuffers;
        std::string m_Key;
	};


}
