#include <string>

#include "Ident.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

Ident::Ident() {}
Ident::Ident(string identStr) :identStr(identStr) {}

void Ident::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}