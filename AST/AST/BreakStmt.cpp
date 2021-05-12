#include "BreakStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

BreakStmt::BreakStmt(location loc)
	:ASTUnit(loc)
{
	this->unitType = ASTUnit::UnitType::isBreakStmt;
}

void BreakStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}