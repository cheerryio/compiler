#include <memory>
#include <vector>

#include "WhileStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

WhileStmt::WhileStmt(Exp* cond, Stmt* body,location loc)
	:ASTUnit(loc), cond(cond), body(body)
{
	this->unitType = ASTUnit::UnitType::isWhileStmt;
}

void WhileStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}