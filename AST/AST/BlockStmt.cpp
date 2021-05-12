#include "BlockStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

BlockStmt::BlockStmt(location loc)
	:ASTUnit(loc)
{
	this->unitType = ASTUnit::UnitType::isBlockStmt;
}

BlockStmt::BlockStmt(std::vector<std::unique_ptr<ASTUnit>> stmts,location loc)
	:ASTUnit(loc), stmts(std::move(stmts))
{
	this->unitType = ASTUnit::UnitType::isBlockStmt;
}

void BlockStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}