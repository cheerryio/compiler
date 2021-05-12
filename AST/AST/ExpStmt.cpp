#include "ExpStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ExpStmt::ExpStmt(std::unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc), exp(std::move(exp))
{
	this->unitType = ASTUnit::UnitType::isExpStmt;
}


void ExpStmt::accept(ASTVisitor &visitor) {
	visitor.visit(this);
}
