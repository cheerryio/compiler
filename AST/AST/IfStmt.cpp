#include "IfStmt.h"

using namespace std;
using namespace saltyfish;

IfStmt::IfStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> ifBody)
	:cond(std::move(cond)), ifBody(std::move(ifBody))
{
	
}

IfStmt::IfStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> ifBody, std::unique_ptr<Stmt> elseBody)
	: cond(std::move(cond)), ifBody(std::move(ifBody)), elseBody(std::move(elseBody))
{
	
}

void IfStmt::setHasElse(bool b) {
	bitFields.hasElse = b ? 1 : 0;
}