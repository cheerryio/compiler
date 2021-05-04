#include "ValueDecl.h"

using namespace std;
using namespace saltyfish;

ValueDecl::ValueDecl(unique_ptr<Type> type)
	:type(std::move(type))
{

}

ValueDecl::ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> ValueDefList)
	:type(std::move(type)),ValueDefList(std::move(ValueDefList))
{
	
}

void ValueDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}
