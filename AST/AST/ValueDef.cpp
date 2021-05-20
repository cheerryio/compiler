#include <string>
#include <memory>
#include <iostream>
#include <utility>
#include "ValueDef.h"
#include "ConstantInt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;

ValueDef::ValueDef(Ident* ident, vector<Exp*> arrayDimList,location loc)
	:ASTUnit(loc), ident(ident), arrayDimList(arrayDimList)
{
	this->unitType = ASTUnit::UnitType::isValueDef;
	this->bitFields.hasAssign = 0;
}

ValueDef::ValueDef(Ident* ident, vector<Exp*> arrayDimList, Exp* exp,location loc)
	:ASTUnit(loc), ident(ident), arrayDimList(arrayDimList), exp(exp)
{
	this->unitType = ASTUnit::UnitType::isValueDef;
	this->bitFields.hasAssign = 1;
}

void ValueDef::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}