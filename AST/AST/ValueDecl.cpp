#include "ValueDecl.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ValueDecl::ValueDecl(Type* type, std::vector<ValueDef*> valueDefList,location loc)
	:ASTUnit(loc), type(type), valueDefList(valueDefList)
{
	this->unitType = ASTUnit::UnitType::isValueDecl;
}

void ValueDecl::setIdentConst() {
	for (ValueDef* valueDef : this->valueDefList) {
		valueDef->ident->bitFields.isConst = 1;
		valueDef->ident->exp = valueDef->exp;
	}
}

void ValueDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}
