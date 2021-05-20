#include "AssignStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

AssignStmt::AssignStmt(Ident* ident, Exp* exp)
	:ident(ident), exp(exp)
{
	this->unitType = ASTUnit::UnitType::isAssignStmt;
}

AssignStmt::AssignStmt(Ident* ident, Exp* exp, location loc)
	:ASTUnit(loc), ident(ident), exp(exp)
{
	this->unitType = ASTUnit::UnitType::isAssignStmt;
}

void AssignStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}