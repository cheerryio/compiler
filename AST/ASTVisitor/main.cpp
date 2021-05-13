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
	enum AEnum {
		Enum1, Enum2
	} Aenum;
public:
	void AFunc() const {
		cout << "function" << endl;
	}
};

class B
	:public A {

};

int main() {
	cout << "aaa";
	string a = "abababa";
	cout << a + "dddddd";
	return 0;
}