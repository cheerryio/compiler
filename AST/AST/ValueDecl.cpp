#include "ValueDecl.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ValueDecl::ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> valueDefList,unsigned isConst)
	:type(std::move(type)),valueDefList(std::move(valueDefList))
{
	this->bitFields.isConst = isConst;
}

ValueDecl::ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> valueDefList,unsigned isConst, location loc)
	:ASTUnit(loc), type(std::move(type)), valueDefList(std::move(valueDefList))
{
	this->bitFields.isConst = isConst;
}

bool ValueDecl::isConst() {
	return this->bitFields.isConst ? true : false;
}

void ValueDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}
