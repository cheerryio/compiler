#include "DAGVisitor.h"
#include <iostream>
#include "DAGVisitor.h"

using namespace std;
using namespace saltyfish;


DAGVisitor::DAGVisitor(){}
DAGVisitor::~DAGVisitor(){}
/**
* �ޱ���ʽ���ڵĽڵ㲻��ʵ��
*/
void DAGVisitor::visit(FuncDecl* funcDecl) {}
void DAGVisitor::visit(FuncParamDecl* funcParamDecl) {}
void DAGVisitor::visit(BreakStmt* breakStmt) {}
void DAGVisitor::visit(ContinueStmt* continueStmt) {}
void DAGVisitor::visit(EmptyStmt* emptyStmt) {}
void DAGVisitor::visit(Type* type) {}
void DAGVisitor::visit(ConstantInt* constantInt) {}
void DAGVisitor::visit(Ident* ident) {}

/**
* �������б���ʽ���ڵĽڵ�
* ��Ҫ��visitor���ݵ����Եĺ��ӱ���ʽ
* ���ڸñ���ʽ���ʽ����Ժ�ȫ��basket���ӭ����һ��exp�����Ĵ���
*/
void DAGVisitor::visit(CompUnit* compUnit)
{
	vector<ASTUnit*>& compUnitList = compUnit->compUnitList;
	for (vector<ASTUnit*>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
}

void DAGVisitor::visit(ValueDecl* valueDecl)
{
	Type* type = valueDecl->type;
	auto& valueDefList = valueDecl->valueDefList;
	for (ValueDef* valueDef : valueDefList) {
		valueDef->accept(*this);
	}
}
void DAGVisitor::visit(ValueDef* valueDef)
{
	if (valueDef->bitFields.hasAssign) {
		Exp* exp = valueDef->exp;
		exp->accept(*this);
		this->expBasket.clear();
	}
}

void DAGVisitor::visit(FuncDef* funcDef){
	auto block = funcDef->block;
	block->accept(*this);
}

void DAGVisitor::visit(AssignStmt* assignStmt)
{
	Exp* exp = assignStmt->exp;
	exp->accept(*this);
	this->expBasket.clear();
}

void DAGVisitor::visit(BlockStmt* blockStmt)
{
	vector<ASTUnit*>& stmts = blockStmt->stmts;
	// ��block�������оͺã�������ֹ��exp��ֻ����expStmt
	for (vector<ASTUnit*>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
}

void DAGVisitor::visit(ExpStmt* expStmt)
{
	Exp* exp = expStmt->exp;
	exp->accept(*this);
	this->expBasket.clear();
}

void DAGVisitor::visit(IfStmt* ifStmt)
{
	Exp* cond = ifStmt->cond;
	Stmt* ifBody = ifStmt->ifBody;
	Stmt* elseBody = ifStmt->elseBody;

	cond->accept(*this);
	this->expBasket.clear();
	ifBody->accept(*this);
	if (ifStmt->bitFields.hasElse) {
		elseBody->accept(*this);
	}
}

void DAGVisitor::visit(ReturnStmt* returnStmt)
{
	if (returnStmt->bitFields.hasExp) {
		returnStmt->exp->accept(*this);
		this->expBasket.clear();
	}
}

void DAGVisitor::visit(WhileStmt* whileStmt)
{
	Exp* cond = whileStmt->cond;
	cond->accept(*this);
	this->expBasket.clear();
	whileStmt->body->accept(*this);
}

void DAGVisitor::visit(FuncallExp* funcallExp)
{
	auto& params = funcallExp->funcallParamList;
	for (Exp* param : params) {
		param->accept(*this);
		this->expBasket.clear();
	}
}

void DAGVisitor::visit(BinaryExp* binaryExp)
{
	Exp* Lexp = binaryExp->Lexp;
	Exp* Rexp = binaryExp->Rexp;
	Lexp->accept(*this);
	Rexp->accept(*this);
	bool find = false;

	for (Exp* e : this->expBasket) {
		if (e->equals(Lexp)) {
			binaryExp->Lexp = e;
		}
		if (e->equals(Rexp)) {
			binaryExp->Rexp = e;
		}
		if (e->equals(binaryExp)) {
			find = true;
		}
	}
	if (!find) {
		this->expBasket.push_back(binaryExp);
	}
}

void DAGVisitor::visit(UnaryExp* unaryExp)
{
	bool find = false;
	Exp* exp = unaryExp->exp;
	exp->accept(*this);
}

void DAGVisitor::visit(PrimaryExp* primaryExp) {
}