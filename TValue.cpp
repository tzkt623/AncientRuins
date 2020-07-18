#include "TValue.h"
#include "TTString.h"

#include <sstream>
#include <stdexcept>
#include <stdio.h>



namespace tezcat
{
	tezcat::TValue TValue::NullValue;

	TValue::TValue():
		m_Type(ValueType::Null), m_IfMove(false)
	{

	}

	TValue::TValue(bool v):
		m_Type(ValueType::Bool), m_IfMove(false)
	{
		m_Values.b = v;
	}

	TValue::TValue(int v) :
		m_Type(ValueType::Int), m_IfMove(false)
	{
		m_Values.i = v;
	}

	TValue::TValue(float v) :
		m_Type(ValueType::Float), m_IfMove(false)
	{
		m_Values.f = v;
	}

	TValue::TValue(double v) :
		m_Type(ValueType::Double), m_IfMove(false)
	{
		m_Values.d = v;
	}

	TValue::TValue(const std::string &v) :
		m_Type(ValueType::String), m_IfMove(false)
	{
		m_Values.str = new std::string();
		*m_Values.str = v;
	}

	TValue::TValue(void *ptr) :
		m_Type(ValueType::ObjPtr), m_IfMove(false)
	{
		m_Values.ptr = ptr;
	}

	TValue::TValue(TValue &&other) :
		m_IfMove(false)
	{
		*this = std::move(other);
		std::cout << "tezcat::TValue Use Move Builder!!!" << std::endl;
	}

	TValue::TValue(const TValue &other)
	{
//		memset(&m_Values, 0, sizeof(m_Values));
		*this = other;
	}

	TValue::~TValue()
	{
		std::cout << "tezcat::TValue Delete!!" << std::endl;
		this->clear();
	}

	bool TValue::asBool()
	{
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			return m_Values.b;
			break;
		case tezcat::ValueType::Int:
			return m_Values.i == 0 ? false : true;
			break;
		case tezcat::ValueType::Float:
			return m_Values.f == 0.0f ? false : true;
			break;
		case tezcat::ValueType::Double:
			return m_Values.d == 0.0 ? false : true;
			break;
		case tezcat::ValueType::String:
			return (*m_Values.str == "0" || *m_Values.str == "false") ? false : true;
			break;
		default:
			throw std::logic_error("tezcat::TValue can not convert to bool");
			break;
		}

		return false;
	}

	int TValue::asInt()
	{
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			return m_Values.b ? 1 : 0;
			break;
		case tezcat::ValueType::Int:
			return m_Values.i;
			break;
		case tezcat::ValueType::Float:
			return static_cast<int>(m_Values.f);
			break;
		case tezcat::ValueType::Double:
			return static_cast<int>(m_Values.d);
			break;
		case tezcat::ValueType::String:
//			return std::stoi(*m_Values.str);
			return String::toNumber<int>(*m_Values.str);

			break;
		default:
			throw std::logic_error("tezcat::TValue can not convert to bool");
			break;
		}

		return std::numeric_limits<int>::min();
	}

	float TValue::asFloat()
	{
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			return m_Values.b ? 1.0f : 0.0f;
			break;
		case tezcat::ValueType::Int:
			return static_cast<float>(m_Values.i);
			break;
		case tezcat::ValueType::Float:
			return m_Values.f;
			break;
		case tezcat::ValueType::Double:
			return static_cast<float>(m_Values.d);
			break;
		case tezcat::ValueType::String:
//			return std::stof(*m_Values.str);
			return String::toNumber<float>(*m_Values.str);
			break;
		default:
			throw std::logic_error("tezcat::TValue can not convert to bool");
			break;
		}

		return std::numeric_limits<float>::min();
	}

	double TValue::asDouble()
	{
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			return m_Values.b ? 1.0 : 0.0;
			break;
		case tezcat::ValueType::Int:
			return static_cast<double>(m_Values.i);
			break;
		case tezcat::ValueType::Float:
			return static_cast<double>(m_Values.f);
			break;
		case tezcat::ValueType::Double:
			return m_Values.d;
			break;
		case tezcat::ValueType::String:
//			return std::stod(*m_Values.str);
			return String::toNumber<double>(*m_Values.str);
			break;
		default:
			throw std::logic_error("tezcat::TValue can not convert to bool");
			break;
		}

		return std::numeric_limits<double>::min();
	}

	std::string TValue::asSTDString()
	{
		std::string temp;
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
//			temp = std::to_string(m_Values.b);
			temp = String::toString(m_Values.b);
			break;
		case tezcat::ValueType::Int:
//			temp = std::to_string(m_Values.i);
			temp = String::toString(m_Values.i);
			break;
		case tezcat::ValueType::Float:
//			temp = std::to_string(m_Values.f);
			temp = String::toString(m_Values.f);
			break;
		case tezcat::ValueType::Double:
//			temp = std::to_string(m_Values.d);
			temp = String::toString(m_Values.d);
			break;
		case tezcat::ValueType::String:
			temp = *m_Values.str;
			break;
		case tezcat::ValueType::ObjPtr:
// 			char tempC[20];
// 			sprintf_s(tempC, "%p", m_Values.ptr);
// 			temp = tempC;
			throw std::logic_error("tezcat::TValue can not convert to string");
			break;
		default:
			throw std::logic_error("tezcat::TValue can not convert to string");
			break;
		}

		return temp;
	}

	bool TValue::toBool()
	{
		*this = this->asBool();
		return m_Values.b;
	}

	int TValue::toInt()
	{
		*this = this->asInt();
		return m_Values.i;
	}

	float TValue::toFloat()
	{
		*this = this->asFloat();
		return m_Values.f;
	}

	double TValue::toDouble()
	{
		*this = this->asDouble();
		return m_Values.d;
	}

	std::string TValue::toSTDString()
	{
		*this = this->asSTDString();
		return *m_Values.str;
	}

	void TValue::clear()
	{
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			m_Values.b = false;
			break;
		case tezcat::ValueType::Int:
			m_Values.i = 0;
			break;
		case tezcat::ValueType::Float:
			m_Values.f = 0.0f;
			break;
		case tezcat::ValueType::Double:
			m_Values.d = 0.0;
			break;
		case tezcat::ValueType::String:
			if (m_Values.str && m_IfMove == false)
			{
				delete m_Values.str;
				m_Values.str = nullptr;
			}
			break;
		case ValueType::ObjPtr:
			if (m_Values.ptr)
			{
				m_Values.ptr = nullptr;
			}
			break;
		}

		m_Type = ValueType::Null;
		memset(&m_Values, 0, sizeof(m_Values));
	}

	void TValue::reset(ValueType type)
	{
		if (m_Type == type)
		{
			return;
		}

		this->clear();

		switch (type)
		{
		case tezcat::ValueType::Null:break;
		case tezcat::ValueType::Bool:break;
		case tezcat::ValueType::Int:break;
		case tezcat::ValueType::Float:break;
		case tezcat::ValueType::Double:break;
		case tezcat::ValueType::String:
			m_Values.str = new std::string();
			break;
		case ValueType::ObjPtr:
			m_Values.ptr = nullptr;
			break;
		}

		m_Type = type;
	}

	TValue & TValue::operator = (bool b)
	{
		this->reset(ValueType::Bool);
		m_Values.b = b;
		return *this;
	}

	TValue & TValue::operator = (int i)
	{
		this->reset(ValueType::Int);
		m_Values.i = i;
		return *this;
	}

	TValue & TValue::operator = (float f)
	{
		this->reset(ValueType::Float);
		m_Values.f = f;
		return *this;
	}

	TValue & TValue::operator = (double d)
	{
		this->reset(ValueType::Double);
		m_Values.d = d;
		return *this;
	}

	TValue & TValue::operator = (const std::string &s)
	{
		this->reset(ValueType::String);
		*m_Values.str = s;
		return *this;
	}

	TValue & TValue::operator = (const char *cc)
	{
		this->reset(ValueType::String);
		*m_Values.str = cc;
		return *this;
	}

	TValue & TValue::operator = (void *ptr)
	{
		this->reset(ValueType::ObjPtr);
		m_Values.ptr = ptr;
		return *this;
	}

	TValue & TValue::operator = (TValue &&other)
	{
		std::cout << "tezcat::TValue Use Move Operator!!!" << std::endl;
		if (this != &other)
		{
			other.m_IfMove = true;
			this->clear();
			m_Type = other.m_Type;
			m_Values = other.m_Values;
		}

		return *this;
	}

	TValue & TValue::operator = (const TValue &other)
	{
		this->reset(other.m_Type);
		switch (m_Type)
		{
		case tezcat::ValueType::Bool:
			m_Values.b = other.m_Values.b;
			break;
		case tezcat::ValueType::Int:
			m_Values.i = other.m_Values.i;
			break;
		case tezcat::ValueType::Float:
			m_Values.f = other.m_Values.f;
			break;
		case tezcat::ValueType::Double:
			m_Values.d = other.m_Values.d;
			break;
		case tezcat::ValueType::String:
			*m_Values.str = *other.m_Values.str;
			break;
		case ValueType::ObjPtr:
			m_Values.ptr = other.m_Values.ptr;
			break;
		}

		return *this;
	}

	bool TValue::operator == (const TValue &other) const
	{
		return this == &other;
	}

	bool TValue::operator != (const TValue &other) const
	{
		return this != &other;
	}


}