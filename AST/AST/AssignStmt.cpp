#include "AssignStmt.h"

using namespace std;
using namespace saltyfish;

AssignStmt::AssignStmt(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp)
	:ident(std::move(ident)), exp(std::move(exp))
{
	
}

void AssignStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}