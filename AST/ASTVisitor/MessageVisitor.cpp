#include <iostream>
#include <vector>
#include <memory>

#include "MessageVisitor.h"

using namespace std;
using namespace saltyfish;

MessageVisitor::MessageVisitor() {}
MessageVisitor::~MessageVisitor() {}

void MessageVisitor::visit() {
	showDepth();
	cout << "Nothing" << endl;
}

void MessageVisitor::visit(CompUnit* compUnit) {
	showDepth();
	cout << "CompUnit" << endl;
	depth++;
	vector<ASTUnit*>& compUnitList = compUnit->compUnitList;
	for (vector<ASTUnit*>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(FuncDecl* funcDecl){
	showDepth();
	cout << "FuncDecl" << endl;
}

void MessageVisitor::visit(FuncParamDecl* funcParamDecl) {
	showDepth();
	cout << *funcParamDecl << endl;
	depth++;
	funcParamDecl->type->accept(*this);
	funcParamDecl->ident->accept(*this);
	depth--;
}

void MessageVisitor::visit(ValueDecl* valueDecl){
	showDepth();
	cout << "ValueDecl" << endl;
	depth++;
	Type*& type = valueDecl->type;
	vector<ValueDef*>& valueDefList = valueDecl->valueDefList;
	for (vector<ValueDef*>::iterator it = valueDefList.begin(); it < valueDefList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(ValueDef* valueDef) {
	showDepth();
	cout << "ValueDef" << endl;
	depth++;
	valueDef->ident->accept(*this);
	if (valueDef->ident->getArray()) {
		vector<Exp*>& arrayDimList = valueDef->arrayDimList;
		vector<Exp*>::iterator it = arrayDimList.begin();
		if (valueDef->bitFields.isArrayFirstDimEmpty) {
			it++;
		}
		for (it; it < arrayDimList.end(); it++) {
			(*it)->accept(*this);
		}
	}
	if (valueDef->bitFields.hasAssign) {
		valueDef->exp->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(FuncDef* funcDef) {
	showDepth();
	cout << "FuncDef" << endl;
	depth++;
	vector<FuncParamDecl*>& funcParamDeclList = funcDef->funcParamDeclList;
	BlockStmt*& block = funcDef->block;
	funcDef->type->accept(*this);
	funcDef->ident->accept(*this);
	for (vector<FuncParamDecl*>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		(*it)->accept(*this);
	}
	block->accept(*this);
	depth--;
}

void MessageVisitor::visit(AssignStmt* assignStmt){
	showDepth();
	cout << "AssignStmt" << endl;
	depth++;
	Ident*& ident = assignStmt->ident;
	Exp*& exp = assignStmt->exp;
	ident->accept(*this);
	exp->accept(*this);
	depth--;
}
void MessageVisitor::visit(BlockStmt* blockStmt){
	showDepth();
	cout << "BlockStmt" << endl;
	depth++;
	vector<ASTUnit*>& stmts = blockStmt->stmts;
	for (vector<ASTUnit*>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(BreakStmt* breakStmt){
	showDepth();
	cout << "BreakStmt" << endl;
}
void MessageVisitor::visit(ContinueStmt* continueStmt){
	showDepth();
	cout << "ContinueStmt" << endl;
}
void MessageVisitor::visit(EmptyStmt* emptyStmt){
	showDepth();
	cout << "EmptyStmt" << endl;
}
void MessageVisitor::visit(ExpStmt* expStmt){
	showDepth();
	cout << "ExpStmt" << endl;
	depth++;
	Exp*& exp = expStmt->exp;
	exp->accept(*this);
	depth--;
}
void MessageVisitor::visit(IfStmt* ifStmt){
	showDepth();
	cout << "IfStmt" << endl;
	depth++;
	Exp* &cond = ifStmt->cond;
	Stmt*& ifBody = ifStmt->ifBody;
	cond->accept(*this);
	ifBody->accept(*this);
	if (ifStmt->hasElse()) {
		Stmt*& elseBody = ifStmt->elseBody;
		elseBody->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(ReturnStmt* returnStmt){
	showDepth();
	cout << "ReturnStmt" << endl;
	depth++;
	if (returnStmt->hasExp()) {
		Exp*& exp = returnStmt->exp;
		exp->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(WhileStmt* whileStmt){
	showDepth();
	cout << "WhileStmt" << endl;
	depth++;
	Exp* &cond = whileStmt->cond;
	Stmt*& body = whileStmt->body;
	cond->accept(*this);
	body->accept(*this);
	depth--;
}

void MessageVisitor::visit(BinaryExp* binaryExp){
	showDepth();
	cout << *binaryExp << endl;
	depth++;
	binaryExp->Lexp->accept(*this);
	binaryExp->Rexp->accept(*this);
	depth--;
}
void MessageVisitor::visit(FuncallExp* funcallExp){
	showDepth();
	cout << "FuncallExp" << endl;
	depth++;
	vector<Exp*>& funcParamList = funcallExp->funcallParamList;
	funcallExp->ident->accept(*this);
	for (vector<Exp*>::iterator it = funcParamList.begin(); it < funcParamList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(PrimaryExp* primaryExp){
	showDepth();
	cout << *primaryExp << endl;
	depth++;
	if (primaryExp->childType == ASTUnit::UnitType::isIdent) {
		primaryExp->ident->accept(*this);
	}
	else if(primaryExp->childType == ASTUnit::UnitType::isConstantInt) {
		primaryExp->constantInt->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(UnaryExp* unaryExp){
	showDepth();
	cout << *unaryExp << endl;
	unaryExp->exp->accept(*this);
	depth--;
}

void MessageVisitor::visit(Type* type){
	showDepth();
	cout << *type << endl;
}
void MessageVisitor::visit(ConstantInt* constantInt){
	depth++;
	showDepth();
	cout << *constantInt << endl;
	depth--;
}
void MessageVisitor::visit(Ident* ident){
	showDepth();
	cout << *ident << endl;
}

void MessageVisitor::showDepth() {
	for (unsigned i = 0; i < depth; i++) {
		cout << " |";
	}
}