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

#define TEST(format,...) printf(format,__VA_ARGS__)

int main() {
	TEST("%d", 12,13,14);
	return 0;
}