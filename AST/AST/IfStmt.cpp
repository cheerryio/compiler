#include "IfStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

IfStmt::IfStmt(Exp* cond, Stmt* ifBody,location loc)
	:ASTUnit(loc), cond(cond), ifBody(ifBody)
{
	this->bitFields.hasElse = 0;
	this->unitType = ASTUnit::UnitType::isIfStmt;
}

IfStmt::IfStmt(Exp* cond, Stmt* ifBody, Stmt* elseBody,location loc)
	:ASTUnit(loc), cond(cond), ifBody(ifBody), elseBody(elseBody)
{
	this->bitFields.hasElse = 1;
	this->unitType = ASTUnit::UnitType::isIfStmt;
}

bool IfStmt::hasElse() {
	return bitFields.hasElse == 1 ? true : false;
}

void IfStmt::setHasElse(bool b) {
	bitFields.hasElse = b ? 1 : 0;
}

void IfStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}