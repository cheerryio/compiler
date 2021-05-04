#include "ContinueStmt.h"

using namespace saltyfish;

ContinueStmt::ContinueStmt() {}

void ContinueStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}