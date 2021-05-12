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
	setHasAssign(false);
}

ValueDef::ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList, unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc), ident(std::move(ident)), arrayDimList(std::move(arrayDimList)), exp(std::move(exp))
{
	this->unitType = ASTUnit::UnitType::isValueDef;
	setHasAssign(true);
}

bool ValueDef::hasAssign() {
	return bitFields.hasAssign == 1 ? true : false;
}

bool ValueDef::isArrayAssign() {
	return bitFields.isArrayAssign == 1 ? true : false;
}

bool ValueDef::isArrayFirstDimEmpty() {
	return bitFields.isArrayFirstDimEmpty == 1 ? true : false;
}

void ValueDef::setHasAssign(bool b) {
	bitFields.hasAssign = b ? 1 : 0;
}

void ValueDef::setIsArrayAssign(bool b) {
	bitFields.isArrayAssign = b ? 1 : 0;
}

void ValueDef::setIsArrayFirstDimEmpty(bool b) {
	bitFields.isArrayFirstDimEmpty = b ? 1 : 0;
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