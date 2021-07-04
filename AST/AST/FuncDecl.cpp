#include "FuncDecl.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

FuncDecl::FuncDecl(Ident* ident,location loc)
	:ASTUnit(loc), ident(ident)
{
	this->unitType = ASTUnit::UnitType::isFuncDecl;
}

void FuncDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}