#include <string>
#include <memory>
#include <iostream>
#include <utility>
#include "ValueDef.h"
#include "ConstantInt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;

ValueDef::ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList,location loc)
	:ASTUnit(loc), ident(std::move(ident)), arrayDimList(std::move(arrayDimList))
{
	this->unitType = ASTUnit::UnitType::isValueDef;
	this->bitFields.hasAssign = 0;
}

ValueDef::ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList, unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc), ident(std::move(ident)), arrayDimList(std::move(arrayDimList)), exp(std::move(exp))
{
	this->unitType = ASTUnit::UnitType::isValueDef;
	this->bitFields.hasAssign = 1;
}

void ValueDef::setIdentConst() {
	this->ident->setConst();
}

void ValueDef::setIdentArray() {
	this->ident->setArray();
}

void ValueDef::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}