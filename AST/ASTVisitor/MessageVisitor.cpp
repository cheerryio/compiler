#include <iostream>

#include "MessageVisitor.h"

using namespace std;
using namespace saltyfish;

MessageVisitor::MessageVisitor() {}
MessageVisitor::~MessageVisitor() {}

void MessageVisitor::visit() {
	cout << "void" << endl;
}

void MessageVisitor::visit(FuncDecl* funcDecl){
	cout << "funcDecl" << endl;
}

void MessageVisitor::visit(FuncParamDecl* funcParamDecl) {
	cout << "funcParamDecl" << endl;
}

void MessageVisitor::visit(ValueDecl* valueDecl){
	cout << "valueDecl" << endl;
}

void MessageVisitor::visit(ValueDef* valueDef) {
	cout << "valueDef" << endl;
}

void MessageVisitor::visit(AssignStmt* assignStmt){
	cout << "assignStmt" << endl;
}
void MessageVisitor::visit(BlockStmt* blockStmt){
	cout << "blockStmt" << endl;
}
void MessageVisitor::visit(BreakStmt* breakStmt){
	cout << "breakStmt" << endl;
}
void MessageVisitor::visit(ContinueStmt* continueStmt){
	cout << "continueStmt" << endl;
}
void MessageVisitor::visit(EmptyStmt* emptyStmt){
	cout << "emptyStmt" << endl;
}
void MessageVisitor::visit(ExpStmt* expStmt){
	cout << "expStmt" << endl;
}
void MessageVisitor::visit(IfStmt* ifStmt){
	cout << "ifStmt" << endl;
}
void MessageVisitor::visit(ReturnStmt* returnStmt){
	cout << "returnStmt" << endl;
}
void MessageVisitor::visit(WhileStmt* whileStmt){
	cout << "whileStmt" << endl;
}

void MessageVisitor::visit(BinaryExp* binaryExp){
	cout << "binaryExp" << endl;
}
void MessageVisitor::visit(FuncallExp* funcallExp){
	cout << "funcallExp" << endl;
}
void MessageVisitor::visit(PrimaryExp* primaryExp){
	cout << "primaryExp" << endl;
}
void MessageVisitor::visit(UnaryExp* unaryExp){
	cout << "unaryExp" << endl;
}

void MessageVisitor::visit(Type* type){
	cout << "type" << endl;
}
void MessageVisitor::visit(ConstantInt* constantInt){
	cout << "constantInt" << endl;
}
void MessageVisitor::visit(Ident* ident){
	cout << "ident" << endl;
}