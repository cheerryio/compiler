#pragma once
#include "Constant.h"

namespace saltyfish {
	class ConstantInt:public Constant {
	public:
		enum ConstantIntType { Octal, Decimal, Hexadecimal } constantIntType;
		int value;
	public:
		ConstantInt();
		ConstantInt(ConstantInt::ConstantIntType constantIntType, int value);
	};
}