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

class A {
public:
	int a, b;
	friend bool operator==(const A& A1,const A& A2) {
		return A1.a == A2.a && A1.b == A2.b;
	}
};

int main() {
	A A1, A2;
	A1.a = A2.a = 1;
	A1.b = A2.b = 3;
	cout << (A1 == A2) << endl;
	return 0;
}