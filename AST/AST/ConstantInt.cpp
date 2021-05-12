#include <iostream>

#include "ConstantInt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

map<ConstantInt::ConstantIntType, string> ConstantInt::constantIntTypeMap = {
	{ConstantInt::ConstantIntType::Octal,"Octal Integer"},
	{ConstantInt::ConstantIntType::Decimal,"Decimal Integer"},
	{ConstantInt::ConstantIntType::Hexadecimal,"Hexadecimal Integer"}
};

ConstantInt::ConstantInt(ConstantInt::ConstantIntType constantIntType, int value,location loc)
	:ASTUnit(loc),constantIntType(constantIntType), value(value)
{
	this->unitType = ASTUnit::UnitType::isConstantInt;
}

void ConstantInt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const ConstantInt& constantInt)
	{
		o << "<";
		o << "ConstantInt ";
		o << "\'" << ConstantInt::constantIntTypeMap.at(constantInt.constantIntType) << "\' ";
		o << "\'" << constantInt.value << "\' ";
		cout << "\'" << constantInt.loc << "\'";
		o << ">";
		return o;
	}
}
