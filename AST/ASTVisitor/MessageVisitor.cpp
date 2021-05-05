#include <iostream>
#include <vector>
#include <memory>

#include "MessageVisitor.h"

using namespace std;
using namespace saltyfish;

MessageVisitor::MessageVisitor() {}
MessageVisitor::~MessageVisitor() {}

unsigned int MessageVisitor::depth = 0;

void MessageVisitor::visit() {
	showDepth(depth);
	cout << "Nothing" << endl;
}

void MessageVisitor::visit(CompUnit* compUnit) {
	showDepth(depth);
	cout << "CompUnit" << endl;
	depth++;
	vector<unique_ptr<ASTUnit>>& compUnitList = compUnit->compUnitList;
	for (vector<unique_ptr<ASTUnit>>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(FuncDecl* funcDecl){
	showDepth(depth);
	cout << "FuncDecl" << endl;
}

void MessageVisitor::visit(FuncParamDecl* funcParamDecl) {
	showDepth(depth);
	cout << "FuncParamDecl" << endl;
	depth++;
	unique_ptr<Type>& type = funcParamDecl->type;
	unique_ptr<Ident> &ident = funcParamDecl->ident;
	type->accept(*this);
	ident->accept(*this);
	depth--;
}

void MessageVisitor::visit(ValueDecl* valueDecl){
	showDepth(depth);
	cout << "ValueDecl" << endl;
	depth++;
	unique_ptr<Type>& type = valueDecl->type;
	vector<unique_ptr<ValueDef>>& valueDefList = valueDecl->ValueDefList;
	for (vector<unique_ptr<ValueDef>>::iterator it = valueDefList.begin(); it < valueDefList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(ValueDef* valueDef) {
	showDepth(depth);
	cout << "ValueDef" << endl;
	depth++;
	valueDef->ident->accept(*this);
	if (valueDef->isArray()) {
		vector<unique_ptr<Exp>>& arrayDimList = valueDef->arrayDimList;
		vector<unique_ptr<Exp>>::iterator it = arrayDimList.begin();
		if (valueDef->isArrayFirstDimEmpty()) {
			it++;
		}
		for (it; it < arrayDimList.end(); it++) {
			(*it)->accept(*this);
		}
	}
	if (valueDef->hasAssign()) {
		valueDef->exp->accept(*this);
	}
	depth--;
}

void MessageVisitor::visit(FuncDef* funcDef) {
	showDepth(depth);
	cout << "FuncDef" << endl;
	depth++;
	vector<unique_ptr<FuncParamDecl>>& funcParamDeclList = funcDef->funcParamDeclList;
	unique_ptr<BlockStmt>& block = funcDef->block;
	funcDef->type->accept(*this);
	funcDef->ident->accept(*this);
	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		(*it)->accept(*this);
	}
	block->accept(*this);
	depth--;
}

void MessageVisitor::visit(AssignStmt* assignStmt){
	showDepth(depth);
	cout << "AssignStmt" << endl;
	depth++;
	unique_ptr<Ident>& ident = assignStmt->ident;
	unique_ptr<Exp>& exp = assignStmt->exp;
	ident->accept(*this);
	exp->accept(*this);
	depth--;
}
void MessageVisitor::visit(BlockStmt* blockStmt){
	showDepth(depth);
	cout << "BlockStmt" << endl;
	depth++;
	vector<unique_ptr<ASTUnit>>& stmts = blockStmt->stmts;
	for (vector<unique_ptr<ASTUnit>>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(BreakStmt* breakStmt){
	showDepth(depth);
	cout << "BreakStmt" << endl;
}
void MessageVisitor::visit(ContinueStmt* continueStmt){
	showDepth(depth);
	cout << "ContinueStmt" << endl;
}
void MessageVisitor::visit(EmptyStmt* emptyStmt){
	showDepth(depth);
	cout << "EmptyStmt" << endl;
}
void MessageVisitor::visit(ExpStmt* expStmt){
	showDepth(depth);
	cout << "ExpStmt" << endl;
	depth++;
	unique_ptr<Exp>& exp = expStmt->exp;
	exp->accept(*this);
	depth--;
}
void MessageVisitor::visit(IfStmt* ifStmt){
	showDepth(depth);
	cout << "IfStmt" << endl;
	depth++;
	unique_ptr<Exp> &cond = ifStmt->cond;
	unique_ptr<Stmt>& ifBody = ifStmt->ifBody;
	cond->accept(*this);
	ifBody->accept(*this);
	if (ifStmt->hasElse()) {
		unique_ptr<Stmt>& elseBody = ifStmt->elseBody;
		elseBody->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(ReturnStmt* returnStmt){
	showDepth(depth);
	cout << "ReturnStmt" << endl;
	depth++;
	if (returnStmt->hasExp()) {
		unique_ptr<Exp>& exp = returnStmt->exp;
		exp->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(WhileStmt* whileStmt){
	showDepth(depth);
	cout << "WhileStmt" << endl;
	depth++;
	unique_ptr<Exp> &cond = whileStmt->cond;
	unique_ptr<Stmt>& body = whileStmt->body;
	cond->accept(*this);
	body->accept(*this);
	depth--;
}

void MessageVisitor::visit(BinaryExp* binaryExp){
	showDepth(depth);
	cout << "BinaryExpType: " << binaryExp->binaryExpType << endl;
	binaryExp->Lexp->accept(*this);
	binaryExp->Rexp->accept(*this);
}
void MessageVisitor::visit(FuncallExp* funcallExp){
	showDepth(depth);
	cout << "FuncallExp" << endl;
	depth++;
	vector<unique_ptr<Exp>>& funcParamList = funcallExp->funcallParamList;
	funcallExp->ident->accept(*this);
	for (vector<unique_ptr<Exp>>::iterator it = funcParamList.begin(); it < funcParamList.end(); it++) {
		(*it)->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(PrimaryExp* primaryExp){
	showDepth(depth);
	cout << "PrimaryExp" << endl;
	depth++;
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		primaryExp->ident->accept(*this);
	}
	else {
		primaryExp->constant->accept(*this);
	}
	depth--;
}
void MessageVisitor::visit(UnaryExp* unaryExp){
	showDepth(depth);
	cout << "UnaryExp" << endl;
	depth++;
	showDepth(depth);
	cout << "UnaryExpType: " << unaryExp->unaryExpType << endl;
	showDepth(depth);
	cout << "OpStr: " << unaryExp->opStr << endl;
	unaryExp->exp->accept(*this);
	depth--;
}

void MessageVisitor::visit(Type* type){
	showDepth(depth);
	cout << "Type:" << type->typeStr << endl;
}
void MessageVisitor::visit(ConstantInt* constantInt){
	showDepth(depth);
	cout << "ConstantInt" << endl;
	depth++;
	showDepth(depth);
	cout << "ConstantIntType: " << constantInt->constantIntType << endl;
	showDepth(depth);
	cout << "ConstantIntValue: " << constantInt->value << endl;
	depth--;
}
void MessageVisitor::visit(Ident* ident){
	showDepth(depth);
	cout << "Ident: " << ident->identStr << endl;
}

void MessageVisitor::showDepth(unsigned int depth) {
	for (int i = 0; i < depth; i++) {
		cout << "  ";
	}
}