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
	while (true) {
		cout << 1 << endl;
		{
			cout << 2 << endl;
			{
				cout << 3 << endl;
				break;
			}
		}
	}
	return 0;
}