#include "EmptyStmt.h"
using namespace saltyfish;

EmptyStmt::EmptyStmt()
{

}

void EmptyStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}