#include "EmptyStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;

EmptyStmt::EmptyStmt(location loc)
	:ASTUnit(loc)
{
	this->unitType = ASTUnit::UnitType::isEmptyStmt;
}

void EmptyStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}