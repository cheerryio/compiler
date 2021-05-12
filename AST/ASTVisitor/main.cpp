#include <iostream>
#include <unordered_map>
#include <string>
#include "EmptyStmt.h"
#include "Ident.h"
#include "MessageVisitor.h"
#include "Exp.h"
#include "ExpStmt.h"
#include "BinaryExp.h"
#include "ValueDef.h"
#include "SymbolTableList.h"

using namespace std;
using namespace saltyfish;

int main() {
	SymbolTableList table;
	SymbolAttr* attr1 = new SymbolAttr();
	SymbolAttr* attr2 = new SymbolAttr();
	attr1->level = 1;
	attr2->level = 2;
	table.inScope();
	table.addSymbol("attr1", attr1);
	table.inScope();
	table.addSymbol("attr2", attr2);
	table.outScope();
	return 0;
}