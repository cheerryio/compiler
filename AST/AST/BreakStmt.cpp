#include "BreakStmt.h"

using namespace std;
using namespace saltyfish;

void BreakStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}