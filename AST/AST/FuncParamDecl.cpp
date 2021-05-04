#include "FuncParamDecl.h"
#include "Type.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

FuncParamDecl::FuncParamDecl() {}

FuncParamDecl::FuncParamDecl(unique_ptr<Type> type, unique_ptr<Ident> ident)
	:type(std::move(type)), ident(std::move(ident))
{

}

void FuncParamDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}