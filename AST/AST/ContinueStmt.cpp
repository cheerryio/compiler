#include "ContinueStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;

ContinueStmt::ContinueStmt(location loc):ASTUnit(loc) {
	this->unitType = ASTUnit::UnitType::isContinueStmt;
}

void ContinueStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}