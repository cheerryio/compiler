#include "ConstantInt.h"

using namespace saltyfish;

ConstantInt::ConstantInt() {}

ConstantInt::ConstantInt(ConstantInt::ConstantIntType constantIntType,int value)
	:constantIntType(constantIntType),value(value)
{
	
}

void ConstantInt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}