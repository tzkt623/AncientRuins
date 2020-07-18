#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "TTString.h"
#include "TValue.h"
#include "Tools.h"

namespace tezcat
{
	class Calculator
	{
		enum class Flags
		{
			NotFlag,
			StopFlag,
			Addition,
			Subtraction,
			Multiplication,
			Division,
			LeftBracket,
			RightBracket
		};

		struct Package
		{
			Package(double v, Flags f) : value(v), flag(f) {}
			Package() : value(0), flag(Flags::NotFlag) {}

			double value;
			Flags flag;
		};

		struct Flag
		{
			Flag(Flags f, int l) : flag(f), level(l) {}
			Flags flag;
			int level;
		};

		static Flag fStopFlag;
		static Flag fAddition;
		static Flag fSubtraction;
		static Flag fMultiplication;
		static Flag fDivision;
		static Flag fLeftBracket;
		static Flag fRightBracket;

		//************************************
		// Method:    pushOperator
		// FullName:  tezcat::Calculator::pushOperator
		// Access:    private static 
		// Returns:   void
		// Qualifier:
		// Parameter: std::vector<Flag> & flags
		// Parameter: std::vector<Package> & postfix
		// Parameter: std::string & numberStr
		// Parameter: const Flag & flag
		//************************************
		static void pushOperator(std::vector<Flag> &flags, std::vector<Package> &postfix, std::string &numberStr, const Flag &flag)
		{
			//压入数字
			if (!numberStr.empty())
			{
				postfix.push_back(Package(String::toNumber<double>(numberStr), Flags::NotFlag));
				numberStr.clear();
			}

			//检查flag
			if (flags.back().flag == Flags::StopFlag || flag.flag == Flags::LeftBracket || flags.back().flag == Flags::LeftBracket)
			{
				flags.push_back(flag);
			}
			else
			{
				//#(+(+
				//size = 5
				//-进栈
				//弹出+
				//压入-
				//index不变
				//如果小于等于栈顶运算符优先级,弹出栈顶

				while (flag.level <= flags.back().level)
				{
					auto &back = flags.back();
					postfix.push_back(Package(0, back.flag));
					flags.pop_back();
				}

				flags.push_back(flag);
			}
		}


		//************************************
		// Method:    toPostfix
		// FullName:  tezcat::Calculator::toPostfix
		// Access:    private static 
		// Returns:   std::vector<Package>
		// Qualifier:
		// Parameter: const std::string & rule
		//************************************
		static std::vector<Package> toPostfix(const std::string &rule)
		{
			std::vector<Flag> flags;
			flags.push_back(fStopFlag);
			std::vector<Package> postfix;
			std::string numberStr;

			char c;
			std::string tempStr;
			for (size_t i = 0; i < rule.length(); i++)
			{
				c = rule[i];
				switch (c)
				{
				case '+':
					pushOperator(flags, postfix, numberStr, fAddition);
					break;
				case '-':
					pushOperator(flags, postfix, numberStr, fSubtraction);
					break;
				case '*':
					pushOperator(flags, postfix, numberStr, fMultiplication);
					break;
				case '/':
					pushOperator(flags, postfix, numberStr, fDivision);
					break;
				case '(':
					pushOperator(flags, postfix, numberStr, fLeftBracket);
					break;
				case ')':
					if (!numberStr.empty())
					{
						postfix.push_back(Package(String::toNumber<double>(numberStr), Flags::NotFlag));
						numberStr.clear();
					}

					while (flags.back().flag != Flags::LeftBracket)
					{
						auto &back = flags.back();
						postfix.push_back(Package(0, back.flag));
						flags.pop_back();
					}
					flags.pop_back();
					break;
				default:
					if (String::inRange(c, '0', '9'))
					{
						numberStr += c;
					}
					break;

				}
			}

			if (!numberStr.empty())
			{
				postfix.push_back(Package(String::toNumber<double>(numberStr), Flags::NotFlag));
			}

			while (!flags.empty())
			{
				postfix.push_back(Package(0, flags.back().flag));
				flags.pop_back();
			}

			for (size_t i = 0; i < postfix.size(); i++)
			{
				switch (postfix[i].flag)
				{
				case Flags::NotFlag:
					std::cout << postfix[i].value;
					break;
				case Flags::StopFlag:
					break;
				case Flags::Addition:
					std::cout << "+";
					break;
				case Flags::Subtraction:
					std::cout << "-";
					break;
				case Flags::Multiplication:
					std::cout << "*";
					break;
				case Flags::Division:
					std::cout << "/";
					break;
				case Flags::LeftBracket:
					break;
				case Flags::RightBracket:
					break;
				default:
					break;
				}
			}

			std::cout << std::endl;

			return postfix;
		}

		//************************************
		// Method:    toAttributePostfix
		// FullName:  tezcat::Calculator::toAttributePostfix
		// Access:    private static 
		// Returns:   std::vector<Package>
		// Qualifier:
		// Parameter: AnyValue & value
		// Parameter: const std::string & rule
		// Parameter: Property & property
		//************************************
		static std::vector<Package> toAttributePostfix(TValue &value, const std::string &rule, PropertyMap &property)
		{
			std::vector<Flag> flags;
			flags.push_back(fStopFlag);
			std::vector<Package> postfix;
			std::string numberStr;

			char c;
			std::string tempStr;
			for (size_t i = 0; i < rule.length(); i++)
			{
				c = rule[i];
				switch (c)
				{
				case '+':
					pushOperator(flags, postfix, numberStr, fAddition);
					break;
				case '-':
					pushOperator(flags, postfix, numberStr, fSubtraction);
					break;
				case '*':
					pushOperator(flags, postfix, numberStr, fMultiplication);
					break;
				case '/':
					pushOperator(flags, postfix, numberStr, fDivision);
					break;
				case '(':
					pushOperator(flags, postfix, numberStr, fLeftBracket);
					break;
				case ')':
					if (!numberStr.empty())
					{
						postfix.push_back(Package(String::toNumber<double>(numberStr), Flags::NotFlag));
						numberStr.clear();
					}

					while (flags.back().flag != Flags::LeftBracket)
					{
						auto &back = flags.back();
						postfix.push_back(Package(0, back.flag));
						flags.pop_back();
					}
					flags.pop_back();
					break;
				case '@':
					numberStr = value.asSTDString();
					break;
					//找属性文字
				case '!':
					for (size_t j = i + 1; j < rule.length(); j++)
					{
						c = rule[j];
						if (c != '!')
						{
							numberStr += c;
						}
						else
						{
							i = j;//重置游标位置
							postfix.push_back(Package(property[numberStr].asDouble(), Flags::NotFlag));
							numberStr.clear();
							break;//跳出循环,避免读取下一个控制符
						}
					}
					break;
					//随机数
				case '<':
					for (size_t j = i + 1; j < rule.length(); j++)
					{
						c = rule[j];
						if (c != '>')
						{
							numberStr += c;
						}
						else
						{
							i = j;//重置游标位置
							auto pos = numberStr.find_first_of('-');
							auto min = numberStr.substr(0, pos);
							auto max = numberStr.substr(pos + 1);

							if (min.find('.') != std::string::npos)
							{
								float fmin = String::toNumber<float>(min);
								float fmax = String::toNumber<float>(max);
								postfix.push_back(Package(tezcat::tools::random(fmin, fmax), Flags::NotFlag));
							}
							else
							{
								int imin = String::toNumber<int>(min);
								int imax = String::toNumber<int>(max);
								postfix.push_back(Package(tezcat::tools::random(imin, imax), Flags::NotFlag));
							}

							numberStr.clear();
							break;//跳出循环,避免读取下一个控制符
						}
					}
					break;
				default:
					if (String::inRange(c, '0', '9'))
					{
						numberStr += c;
					}
					break;

				}
			}

			if (!numberStr.empty())
			{
				postfix.push_back(Package(String::toNumber<double>(numberStr), Flags::NotFlag));
			}

			while (!flags.empty())
			{
				postfix.push_back(Package(0, flags.back().flag));
				flags.pop_back();
			}

			for (size_t i = 0; i < postfix.size(); i++)
			{
				switch (postfix[i].flag)
				{
				case Flags::NotFlag:
					std::cout << postfix[i].value;
					break;
				case Flags::StopFlag:
					break;
				case Flags::Addition:
					std::cout << "+";
					break;
				case Flags::Subtraction:
					std::cout << "-";
					break;
				case Flags::Multiplication:
					std::cout << "*";
					break;
				case Flags::Division:
					std::cout << "/";
					break;
				case Flags::LeftBracket:
					break;
				case Flags::RightBracket:
					break;
				default:
					break;
				}
			}

			std::cout << std::endl;

			return postfix;
		}

	public:
		//************************************
		// Method:    attributeResult
		// FullName:  tezcat::Calculator::attributeResult
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: AnyValue & value
		// Parameter: const std::string & rule
		// Parameter: Property & property
		// Info:	  属性规则计算
		//************************************
		static void attributeResult(TValue &value, const std::string &rule, PropertyMap &property)
		{
			double result = 0;
			std::vector<double> temp;
			auto postfix = toAttributePostfix(value, rule, property);
			//避免弹出最后的控制符 -1
			for (size_t i = 0; i < postfix.size() - 1; i++)
			{
				auto &pack = postfix[i];
				if (pack.flag == Flags::NotFlag)
				{
					temp.push_back(pack.value);
				}
				else
				{
					auto &p2 = temp[temp.size() - 1];
					auto &p1 = temp[temp.size() - 2];
					temp.pop_back();
					temp.pop_back();

					switch (pack.flag)
					{
					case Flags::NotFlag:
						break;
					case Flags::StopFlag:
						break;
					case Flags::Addition:
						result = p1 + p2;
						break;
					case Flags::Subtraction:
						result = p1 - p2;
						break;
					case Flags::Multiplication:
						result = p1 * p2;
						break;
					case Flags::Division:
						result = p1 / p2;
						break;
					case Flags::LeftBracket:
						break;
					case Flags::RightBracket:
						break;
					default:
						break;
					}

					temp.push_back(result);
				}
			}

			std::cout << temp[0] << std::endl;
			value = temp[0];
		}

		//************************************
		// Method:    toResult
		// FullName:  tezcat::Calculator::toResult
		// Access:    public static 
		// Returns:   double
		// Qualifier:
		// Parameter: const std::string & data
		// Info:	  普通计算
		//************************************
		static double toResult(const std::string &data)
		{
			double result = 0;
			std::vector<double> temp;
			auto postfix = toPostfix(data);
			//避免弹出最后的控制符 -1
			for (size_t i = 0; i < postfix.size() - 1; i++)
			{
				auto &pack = postfix[i];
				if (pack.flag == Flags::NotFlag)
				{
					temp.push_back(pack.value);
				}
				else
				{
					auto &p2 = temp[temp.size() - 1];
					auto &p1 = temp[temp.size() - 2];
					temp.pop_back();
					temp.pop_back();

					switch (pack.flag)
					{
					case Flags::NotFlag:
						break;
					case Flags::StopFlag:
						break;
					case Flags::Addition:
						result = p1 + p2;
						break;
					case Flags::Subtraction:
						result = p1 - p2;
						break;
					case Flags::Multiplication:
						result = p1 * p2;
						break;
					case Flags::Division:
						result = p1 / p2;
						break;
					case Flags::LeftBracket:
						break;
					case Flags::RightBracket:
						break;
					default:
						break;
					}

					temp.push_back(result);
				}
			}

			std::cout << result << std::endl;
			return result;
		}
	};



}

