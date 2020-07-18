#include "Calculator.h"

namespace tezcat
{
	Calculator::Flag Calculator::fStopFlag(Flags::StopFlag, -100);
	Calculator::Flag Calculator::fAddition(Flags::Addition, 0);
	Calculator::Flag Calculator::fSubtraction(Flags::Subtraction, 0);
	Calculator::Flag Calculator::fMultiplication(Flags::Multiplication, 1);
	Calculator::Flag Calculator::fDivision(Flags::Division, 1);
	Calculator::Flag Calculator::fLeftBracket(Flags::LeftBracket, -1);
	Calculator::Flag Calculator::fRightBracket(Flags::RightBracket, -1);
}

