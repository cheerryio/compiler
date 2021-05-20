#include "FuncDef.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

FuncDef::FuncDef(Type* type, Ident* ident, BlockStmt* block,location loc)
	:ASTUnit(loc), type(type), ident(ident), block(block)
{
	this->unitType = ASTUnit::UnitType::isFuncDef;
}

FuncDef::FuncDef(Type* type, Ident* ident, std::vector<FuncParamDecl*> funcParamDeclList, BlockStmt* block,location loc)
	:ASTUnit(loc), type(type), ident(ident), funcParamDeclList(funcParamDeclList), block(block)
{
	this->unitType = ASTUnit::UnitType::isFuncDef;
}

void FuncDef::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}