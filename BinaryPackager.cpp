#include "BinaryPackager.h"
#include "Xml.h"
#include <fstream>
#include "Encryption.h"
#include "TTString.h"

namespace tezcat
{
    BinaryPackager::BinaryPackager(const std::string &key):
        m_Key(key)
    {

    }

    BinaryPackager::BinaryPackager():
        m_Key("tzkthcl")
	{
	}

	BinaryPackager::~BinaryPackager()
	{
	}

	bool BinaryPackager::package(const std::string file)
	{
		std::string packageFile = file + ".ttp";
		std::string packageInfo = file + ".tti";
		

		//写入二进制数据,并生成XML数据结构
		std::ofstream outp(packageFile, std::ios::binary);
		Xml xml;
		xml.createXML(file + ".tti");
		auto root = xml.getRootNode();
//		unsigned int index = 0;
		auto it = m_DataBuffers.begin();
		while (it != m_DataBuffers.end())
		{
			outp.write((char *)(*it)->data, (*it)->length);
            auto xmlFile = root->simpleCreate("file" + String::toString((*it)->index));
            xmlFile->simpleCreate("index", (*it)->index);
			xmlFile->simpleCreate("path", (*it)->path);
			xmlFile->simpleCreate("name", (*it)->name);
			xmlFile->simpleCreate("extension", (*it)->extension);
			xmlFile->simpleCreate("length", (*it)->length);
//			++index;
			++it;
		}

		outp.flush();
		outp.close();

		//加密XML数据结构,并存文件
		std::string xmlContent = xml.getXmlString();
        Encryption code(m_Key);
		code.progressString(xmlContent);
		code.save(packageInfo);
		
		return true;
	}


	bool BinaryPackager::unPackage(const std::string file, const std::string &path)
	{
        std::string tempFile;
        auto wpos = file.find_last_of('.');
        if(wpos == std::string::npos)
        {
            tempFile = file;
        }
        else
        {
            tempFile = file.substr(0, wpos);
        }



		//读取加密后的XML
        Encryption decode(m_Key);
        decode.progress(tempFile + ".tti");
		std::string content = (char *)decode.getDataBuffer();

		//解析解密后的XML数据
		Xml xml;
		if (!xml.loadFileForData(content)) return false;
		auto root = xml.getRootNode();
		auto rtit = root->children.begin();
		while (rtit != root->children.end())
		{
			auto node = (*rtit);
			Item *item = new Item();
            item->index = node->getNode("index")->getLocalValue<unsigned int>();
			item->path = node->getNode("path")->value;
			item->name = node->getNode("name")->value;
			item->extension = node->getNode("extension")->value;
            item->length = node->getNode("length")->getLocalValue<unsigned long long int>();
			item->data = nullptr;

			m_DataBuffers.push_back(item);
			++rtit;
		}

		//数据结构排序
		m_DataBuffers.sort([](Item *first, Item *second)
		{
			return first->index < second->index;
		});

		//解包文件
        std::string packageFile = tempFile + ".ttp";
		std::ifstream ini(packageFile, std::ios::binary);
		auto it = m_DataBuffers.begin();
		while (it != m_DataBuffers.end())
		{
			auto i = (*it);
			std::ofstream out(path + i->name + i->extension, std::ios_base::binary);
			i->data = new unsigned char[i->length];
			ini.read((char *)i->data, i->length);
			out.write((char *)i->data, i->length);

			out.flush();
			out.close();
			++it;
		}

		return true;
	}

    BinaryPackager::Item *BinaryPackager::loadOneItem(const std::string file)
	{
		std::ifstream in(file, std::ios::binary);

		if (in.fail())
		{
            return nullptr;
		}

		Item *item = new Item();
		//取得文件名和后缀名
		auto w = file.find_last_of('/');
		auto fpos = file.find_last_of('.');
		if (w == std::string::npos)
		{
			item->name = file.substr(0, fpos);
		}
		else
		{
			item->path = file.substr(0, w + 1);
			item->name = file.substr(w + 1, fpos - w - 1);
		}
		item->extension = file.substr(fpos);

		//取得文件长度
//		auto pos = in.tellg();
		in.seekg(0, std::ios_base::end);
//		item->length = static_cast<unsigned int>(in.tellg());
        item->length = static_cast<unsigned long long int>(in.tellg());
        in.seekg(0, std::ios_base::beg);

        printf("%lld\n", item->length);

		//取得文件数据
        try
        {
            item->data = new unsigned char[item->length];
        }
        catch(std::bad_alloc &memExp)
        {
            printf("内存分配出错:%s\n", memExp.what());
        }


//      item->data = (unsigned char*)malloc(sizeof(unsigned char) * item->length);
		memset(item->data, 0x00, item->length);
		in.read((char *)item->data, item->length);
		in.close();

        item->index = m_DataBuffers.size();
		m_DataBuffers.push_back(item);


		printf("路径:%s\n", item->path.c_str());
		printf("文件名:%s\n", item->name.c_str());
		printf("后缀名:%s\n", item->extension.c_str());
        printf("长度:%lld\n", item->length);
		printf("==============================================\n");

        return item;
	}

	void BinaryPackager::clear()
	{
		auto it = m_DataBuffers.begin();
		while (it != m_DataBuffers.end())
		{
			delete (*it);
			++it;
        }
        m_DataBuffers.clear();
    }

    bool BinaryPackager::hasData()
    {
        return !m_DataBuffers.empty();
    }



}

