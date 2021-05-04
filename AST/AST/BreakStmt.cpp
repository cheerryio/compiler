#include "BreakStmt.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

void BreakStmt::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}