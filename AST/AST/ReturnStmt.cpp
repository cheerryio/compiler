#include "ReturnStmt.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ReturnStmt::ReturnStmt(location loc)
	:ASTUnit(loc)
{
	setHasExp(false);
	this->unitType = ASTUnit::UnitType::isReturnStmt;
}

ReturnStmt::ReturnStmt(std::unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc),exp(std::move(exp))
{
	setHasExp(true);
	this->unitType = ASTUnit::UnitType::isReturnStmt;
}

bool ReturnStmt::hasExp() {
	return bitFields.hasExp == 1 ? true : false;
}

void ReturnStmt::setHasExp(bool b)
{
	bitFields.hasExp = b ? 1 : 0;
}

void ReturnStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}