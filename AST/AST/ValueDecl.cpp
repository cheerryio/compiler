#include "ValueDecl.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ValueDecl::ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> valueDefList,location loc)
	:ASTUnit(loc), type(std::move(type)), valueDefList(std::move(valueDefList))
{
	this->unitType = ASTUnit::UnitType::isValueDecl;
}

void ValueDecl::setIdentConst() {
	for (auto& valueDef : this->valueDefList) {
		valueDef->setIdentConst();
	}
}

void ValueDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}
