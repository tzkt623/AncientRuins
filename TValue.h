#pragma once


#ifdef WIN32
#include <unordered_map>
#else
#include <map>
#include <unordered_map>
#endif // WIN32

#include <string>
#include <iostream>
#include <vector>

namespace tezcat
{
	enum class ValueType : unsigned char
	{
		Null,
		Bool,
		Int,
		Float,
		Double,
		String,
		ObjPtr,
	};

	class TValue
	{
	public:
		TValue();
		explicit TValue(bool v);
		explicit TValue(int v);
		explicit TValue(float v);
		explicit TValue(double v);
		explicit TValue(const std::string &v);
		explicit TValue(TValue &&other);
		explicit TValue(void *ptr);
		TValue(const TValue &other);
		~TValue();

		//*************************
		//
		// 转化数据格式,并返回结果
		// 不改变内部数据格式,只返回一个副本
		// 如需改变内部格式,请使用toXX函数
		//
		//*************************
	public:
		bool asBool();
		int asInt();
		float asFloat();
		double asDouble();
		std::string asSTDString();
		template<class T>
		typename std::enable_if<std::is_pointer<T>::value, T>::type asObject()
		{
			switch (m_Type)
			{
			case ValueType::Null:
				throw std::logic_error("tezcat::TValue Null can not convert to object");
				break;
			case tezcat::ValueType::Bool:
				throw std::logic_error("tezcat::TValue Bool can not convert to object");
				break;
			case tezcat::ValueType::Int:
				throw std::logic_error("tezcat::TValue Int can not convert to object");
				break;
			case tezcat::ValueType::Float:
				throw std::logic_error("tezcat::TValue Float can not convert to object");
				break;
			case tezcat::ValueType::Double:
				throw std::logic_error("tezcat::TValue Double can not convert to object");
				break;
			case tezcat::ValueType::String:
				throw std::logic_error("tezcat::TValue String can not convert to object");
				break;
			case ValueType::ObjPtr:
				return m_Values.ptr;
				break;
			default:
				throw std::logic_error("tezcat::TValue Unknown can not convert to object");
				break;
			}

			return nullptr;
		}

		//*************************
		//
		// 转化内部数据格式,并返回结果副本
		// 如果不需要转化,请使用asXX函数
		//
		//*************************
	public:
		bool toBool();
		int toInt();
		float toFloat();
		double toDouble();
		std::string toSTDString();

	public:
		bool isNull() const { return m_Type == ValueType::Null; }
		ValueType getType() const { return m_Type; }

	public:
		TValue &operator = (TValue &&other);
		TValue &operator = (const TValue &other);
		TValue &operator = (bool b);
		TValue &operator = (int i);
		TValue &operator = (float f);
		TValue &operator = (double d);
		TValue &operator = (const std::string &s);
		TValue &operator = (const char *cc);
		TValue &operator = (void *ptr);

	public:
		// +
		float operator + (float f)
		{
			return this->asFloat() + f;
		}

		int operator + (int i)
		{
			return this->asInt() + i;
		}

		double operator + (double d)
		{
			return this->asDouble() + d;
		}

		// -
		float operator - (float f)
		{
			return this->asFloat() - f;
		}

		int operator - (int i)
		{
			return this->asInt() - i;
		}

		double operator - (double d)
		{
			return this->asDouble() - d;
		}

		// *
		float operator * (float f)
		{
			return this->asFloat() * f;
		}

		int operator * (int i)
		{
			auto v = this->asDouble() * i;
			return static_cast<int>(v);
		}

		double operator * (double d)
		{
			return this->asDouble() * d;
		}

		// /
		float operator / (float f)
		{
			return this->asFloat() / f;
		}

		int operator / (int i)
		{
			auto v = this->asDouble() / i;
			return static_cast<int>(v);
		}

		double operator / (double d)
		{
			return this->asDouble() * d;
		}

		// +=
		void operator += (float f)
		{
			*this = this->asFloat() + f;
		}

		void operator += (int i)
		{
			*this = this->asInt() + i;
		}

		void operator += (double d)
		{
			*this = this->asDouble() + d;
		}

		// -=
		void operator -= (float f)
		{
			*this = this->asFloat() - f;
		}

		void operator -= (int i)
		{
			*this = this->asInt() - i;
		}

		void operator -= (double d)
		{
			*this = this->asDouble() - d;
		}

		// *=
		void operator *= (float f)
		{
			*this = this->asFloat() * f;
		}

		void operator *= (int i)
		{
			*this = this->asInt() * i;
		}

		void operator *= (double d)
		{
			*this = this->asDouble() * d;
		}

		// /=
		void operator /= (float f)
		{
			*this = this->asFloat() / f;
		}

		void operator /= (int i)
		{
			*this = this->asInt() / i;
		}

		void operator /= (double d)
		{
			*this = this->asDouble() / d;
		}

	public:
		bool operator == (const TValue &other) const;
		bool operator != (const TValue &other) const;

	private:
		void clear();
		void reset(ValueType type);

	private:
		union __Values
		{
			bool b;
			int i;
			float f;
			double d;
			void *ptr;
			std::string *str;
		}m_Values;

		ValueType m_Type;
//		char m_IfMove;
		bool m_IfMove;
	public:
		static TValue NullValue;
	};

	typedef std::unordered_map<std::string, TValue> PropertyMap;
	typedef std::vector<TValue> PropertyArray;
}