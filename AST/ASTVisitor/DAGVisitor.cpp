#include "DAGVisitor.h"
#include <iostream>
#include "DAGVisitor.h"

using namespace std;
using namespace saltyfish;


DAGVisitor::DAGVisitor(){}
DAGVisitor::~DAGVisitor(){}
/**
* 无表达式存在的节点不做实现
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
* 以下是有表达式存在的节点
* 需要将visitor传递到各自的孩子表达式
* 并在该表达式访问结束以后将全局basket清空迎接下一个exp子树的处理
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
	// 对block遍历所有就好，不会出现光的exp，只会有expStmt
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

/**
* 在原有AST上面将其转化为DAG图（通过改变指针指向）
* DAG只对一个表达式子树进行操作，也就是说我每一次转化仅仅关注一个表达式而不是全局
* 现在我只想象我在处理仅仅一句表达式
* 当我身处一个表达式节点，我只想关心她的孩子能否被替换成出现过的表达式节点
* 
* 关于什么情况下把自己放进expBasket里面？
* BinaryExp: 如果在expBasket里面没有找到与自己相同的点，把自己放进去（注意：采用的是后序遍历）
* UnaryExp : 先访问孩子 ，遍历时看自己和孩子是否在expBasket里面
*/
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
	cout << (binaryExp->Lexp == binaryExp->Rexp) << endl;
}

void DAGVisitor::visit(UnaryExp* unaryExp)
{
	bool find = false;
	Exp* exp = unaryExp->exp;
	exp->accept(*this);
	for (Exp* e : this->expBasket) {
		if (e->equals(exp)) {
			unaryExp->exp = e;
		}
		if (e->equals(unaryExp)) {
			find = true;
		}
	}
	if (!find) {
		this->expBasket.push_back(unaryExp);
	}
}

void DAGVisitor::visit(PrimaryExp* primaryExp) {
	bool find = false;
	for (Exp* e : this->expBasket) {
		if (e->equals(primaryExp)) {
			cout << "find same primaryExp" << endl;
			find = true;
			break;
		}
		else {
			cout << "not find same primaryExp" << endl;
		}
	}
	if (!find) {
		this->expBasket.push_back(primaryExp);
	}
}