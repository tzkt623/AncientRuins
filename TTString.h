#pragma once

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>


namespace tezcat
{
	namespace String
	{
		//************************************
		// Method:    isEqual
		// FullName:  tezcat::String::isEqual
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & str
		// Parameter: const char * p
		//************************************
		static inline bool isEqual(const std::string &str, const char *p)
		{
			const char *temp = str.c_str();
			auto result = memcmp(temp, p, sizeof(p));
			return result == 0;
		}

		//************************************
		// Method:    isEqual
		// FullName:  tezcat::String::isEqual
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const char * str
		// Parameter: const char * p
		//************************************
		static inline bool isEqual(const char *str, const char *p)
		{
			auto result = memcmp(str, p, sizeof(p));
			return result == 0;
		}

		//************************************
		// Method:    isEqual
		// FullName:  tezcat::String::isEqual
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & str
		// Parameter: const std::string & p
		//************************************
		static inline bool isEqual(const std::string &str, const std::string &p)
		{
			return str == p;
		}

		//************************************
		// Method:    split
		// FullName:  tezcat::String::split
		// Access:    public static 
		// Returns:   std::list<std::string>
		// Qualifier:
		// Parameter: const std::string & data
		// Parameter: const char & flag
		//************************************
		static inline std::list<std::string> split2List(const std::string &data, const char &flag)
		{
			std::list<std::string> list;
			std::string temp;
			char c;
			for (size_t i = 0; i < data.length(); i++)
			{
				c = data[i];

				if (c == flag)
				{
					list.push_back(temp);
					temp.clear();
				}
				else
				{
					temp += c;
				}
			}

			if (!temp.empty())
			{
				list.push_back(temp);
			}

			return list;
		}

		//************************************
		// Method:    split2Vector
		// FullName:  tezcat::String::split2Vector
		// Access:    public static 
		// Returns:   std::vector<std::string>
		// Qualifier:
		// Parameter: const std::string & data
		// Parameter: const char & flag
		//************************************
		static inline std::vector<std::string> split2Vector(const std::string &data, const char &flag)
		{
			std::vector<std::string> vec;
			std::string temp;
			char c;
			for (size_t i = 0; i < data.length(); i++)
			{
				c = data[i];

				if (c == flag)
				{
					vec.push_back(temp);
					temp.clear();
				}
				else
				{
					temp += c;
				}
			}

			if (!temp.empty())
			{
				vec.push_back(temp);
			}

			return vec;
		}

		//************************************
		// Method:    removeByFlag
		// FullName:  tezcat::String::removeByFlag
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: std::string & str
		// Parameter: const std::string & flag
		//************************************
		static inline void removeByFlag(std::string &str, const std::string &flag)
		{
			str.erase(std::remove_if(str.begin(), str.end(), [&](char c)
			{
				return flag.find(c) != std::string::npos;
			}), str.end());
		}

		//************************************
		// Method:    inRange
		// FullName:  tezcat::String::inRange
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: char & c
		// Parameter: char begin
		// Parameter: char end
		//************************************
		static inline bool inRange(const char &c, const char &begin, const char &end)
		{
			return (c >= begin && c <= end);
		}

		//************************************
		// Method:    hasChar
		// FullName:  tezcat::String::hasChar
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const char & c
		// Parameter: const std::string & chars
		//************************************
		static inline bool hasChar(const char &c, const std::string &chars)
		{
			return chars.find(c) != std::string::npos;
		}


		template<typename T>
		static inline std::string toString(const T &value)
		{
//  		Global::StringStream.str("");
// 			Global::StringStream << value;
// 			return Global::StringStream.str();

			std::stringstream ss;
			ss << value;
			return ss.str();
		}

		template<typename T>
		static inline T toNumber(const std::string &str)
		{
			T temp;

// 			Global::StringStream.str(str);
// 			Global::StringStream >> temp;
// 			return temp;

			std::stringstream ss(str);
			ss >> temp;
			return temp;
		}
	}
}