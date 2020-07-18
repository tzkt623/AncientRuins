
#include "Encryption.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include <memory.h>

namespace tezcat
{
//    unsigned char *Encryption::m_DataBuffer = nullptr;
	Encryption::Encryption() :
        m_DataBuffer(nullptr),
		m_Key("tzkthcl")
	{

	}

	Encryption::Encryption(const std::string &key) :
        m_DataBuffer(nullptr),
		m_Key(key)
	{

	}

	Encryption::~Encryption()
	{
		clear();
	}

	void Encryption::save(const std::string &file_path)
	{
		if (m_DataBuffer == nullptr)
		{
			return;
		}

		std::ofstream out(file_path, std::ios::binary);
		out.write((char *)m_DataBuffer, m_Length);
		out.flush();
		out.close();
	}

	void Encryption::clear()
	{
		if (m_DataBuffer)
		{
			delete[] m_DataBuffer;
			m_DataBuffer = nullptr;
		}

		m_Length = 0;
	}

	bool Encryption::progress(const std::string file)
	{
		std::ifstream in(file, std::ios::binary);

		if (in.fail())
		{
			return false;
		}

//		auto pos = in.tellg();
		in.seekg(0, std::ios_base::end);
        m_Length = static_cast<unsigned long long int>(in.tellg());
        in.seekg(0, std::ios_base::beg);

		if (m_DataBuffer)
		{
			delete[] m_DataBuffer;
		}

		m_DataBuffer = new unsigned char[m_Length + 1];
		memset(m_DataBuffer, 0x00, m_Length);
		m_DataBuffer[m_Length] = '\0';

		in.read((char *)m_DataBuffer, m_Length);
		in.close();

		size_t keyLength = m_Key.length();
		for (unsigned int i = 0; i < m_Length; i++)
		{
			m_DataBuffer[i] ^= m_Key.at(i % keyLength);
		}

		return true;
	}


	bool Encryption::progressString(const std::string &content)
	{
		std::stringstream ss;
		ss << content;

//		auto pos = ss.tellg();
		ss.seekg(0, std::ios_base::end);
//		m_Length = static_cast<unsigned int>(ss.tellg());
        m_Length = static_cast<unsigned long long int>(ss.tellg());
        ss.seekg(0, std::ios_base::beg);

		if (m_DataBuffer)
		{
			delete[] m_DataBuffer;
		}

		m_DataBuffer = new unsigned char[m_Length + 1];
		memset(m_DataBuffer, 0x00, m_Length);
		m_DataBuffer[m_Length] = '\0';

		ss.read((char *)m_DataBuffer, m_Length);
		ss.clear();

		size_t keyLength = m_Key.length();
		for (unsigned int i = 0; i < m_Length; i++)
		{
			m_DataBuffer[i] ^= m_Key.at(i % keyLength);
		}

		return true;
	}

}



