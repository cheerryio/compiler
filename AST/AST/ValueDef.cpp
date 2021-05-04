#include <string>
#include <memory>

#include "ValueDef.h"
#include "ConstantInt.h"

using namespace saltyfish;

ValueDef::ValueDef() {}

ValueDef::ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList)
	:ident(std::move(ident)), arrayDimList(std::move(arrayDimList))
{
	setHasAssign(false);
}

ValueDef::ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList, unique_ptr<Exp> exp)
	: ident(std::move(ident)), arrayDimList(std::move(arrayDimList)), exp(std::move(exp))
{
}

void ValueDef::setHasAssign(bool b) {
	if (b) {
		bitFields.hasAssign = 1;
	}
	else {
		bitFields.hasAssign = 0;
	}
}

void ValueDef::setIsArray(bool b) {
	if (b) {
		bitFields.isArray = 1;
	}
	else {
		bitFields.isArray = 0;
	}
}

void ValueDef::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}