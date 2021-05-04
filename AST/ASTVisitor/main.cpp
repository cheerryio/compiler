#include <iostream>
#include "EmptyStmt.h"
#include "Ident.h"
#include "MessageVisitor.h"
#include "Exp.h"
#include "ExpStmt.h"
#include "BinaryExp.h"

using namespace std;
using namespace saltyfish;

int main() {
	auto Lexp = make_unique<Exp>();
	auto Rexp = make_unique<Exp>();
	auto binaryExp1 = make_unique<BinaryExp>(BinaryExp::BinaryExpType::Add, move(Lexp), move(Rexp));
	auto binaryExp = make_unique<BinaryExp>(BinaryExp::BinaryExpType::Add, move(binaryExp1), move(Rexp));
	MessageVisitor visitor;
	binaryExp->accept(visitor);

	return 0;
}