#include "AssignStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

AssignStmt::AssignStmt(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp)
	:ident(std::move(ident)), exp(std::move(exp))
{
	this->unitType = ASTUnit::UnitType::isAssignStmt;
}

AssignStmt::AssignStmt(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp, location loc)
	:ASTUnit(loc), ident(std::move(ident)), exp(std::move(exp))
{
	this->unitType = ASTUnit::UnitType::isAssignStmt;
}

void AssignStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}