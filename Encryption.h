#pragma once

//===================================================================================
// 文件 : Encryption.h
// 功能 : 文件2进制加密解密
// 作者 : 特兹卡特(Tezcat)
// 时间 : 2014-8-6
//
//===================================================================================


#include <string>
#include <unordered_map>

namespace tezcat
{
	class Encryption
	{
	public:

		/**
		* Method:    Encryption
		* FullName:  tezcat::Encryption::Encryption
		* Access:    private
		* Returns:
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		Encryption();

		/**
		* Method:    Encryption
		* FullName:  tezcat::Encryption::Encryption
		* Access:    private 
		* Returns:   
		* Qualifier:
		* Parameter: const std::string & key
		* Parameter: EncryptionType type
		* Versions : V
		* Since    : V
		*/
		Encryption(const std::string &key);

		/**
		* Method:    ~Encryption
		* FullName:  tezcat::Encryption::~Encryption
		* Access:    public 
		* Returns:   
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		~Encryption();

		/**
		* Method:    progress
		* FullName:  tezcat::Encryption::progress
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string file
		* Versions : V
		* Since    : V
		*/
		bool progress(const std::string file);

		/**
		* Method:    progressData
		* FullName:  tezcat::Encryption::progressData
		* Access:    public 
		* Returns:   bool
		* Qualifier:
		* Parameter: const std::string & content
		* Versions : V
		* Since    : V
		*/
		bool progressString(const std::string &content);

		/**
		* Method:    save
		* FullName:  tezcat::Encryption::save
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Parameter: const std::string & file_path
		* Versions : V
		* Since    : V
		*/
		void save(const std::string &file_path);

		/**
		* Method:    clear
		* FullName:  tezcat::Encryption::clear
		* Access:    public 
		* Returns:   void
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		void clear();


	public:
		/**
		* Method:    getDataBuffer
		* FullName:  tezcat::Encryption::getDataBuffer
		* Access:    public 
		* Returns:   unsigned char *
		* Qualifier:
		* Versions : V
		* Since    : V
		*/
		unsigned char *getDataBuffer() { return m_DataBuffer; }

		/**
		* Method:    getLength
		* FullName:  tezcat::Encryption::getLength
		* Access:    public 
		* Returns:   unsigned int
		* Qualifier: const
		* Versions : V
		* Since    : V
		*/
		unsigned long long int getLength() const { return m_Length; }


        std::string getStringDataBuffer()
        {
            std::string content;
            if (m_DataBuffer)
            {
                content += (char *)m_DataBuffer;
            }
            return content;
        }

	private:
        unsigned char *m_DataBuffer;
//		unsigned int m_Length;
        unsigned long long int m_Length;
		std::string m_Key;
	};

}
