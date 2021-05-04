#include "ReturnStmt.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

ReturnStmt::ReturnStmt()
{

}

ReturnStmt::ReturnStmt(std::unique_ptr<Exp> exp)
	:exp(std::move(exp))
{
	
}

void ReturnStmt::setHasExp(bool b)
{
	bitFields.hasExp = b ? 1 : 0;
}

void ReturnStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}