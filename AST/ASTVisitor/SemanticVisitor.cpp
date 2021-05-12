#include <iostream>

#include "SemanticVisitor.h"

using namespace std;
using namespace saltyfish;

void SemanticVisitor::visit()
{
}

void SemanticVisitor::visit(CompUnit* compUnit)
{
	vector<unique_ptr<ASTUnit>>& compUnitList = compUnit->compUnitList;
	for (vector<unique_ptr<ASTUnit>>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
}

void SemanticVisitor::visit(FuncDecl* funcDecl)
{

}

void SemanticVisitor::visit(FuncParamDecl* funcParamDecl)
{
}

void SemanticVisitor::visit(ValueDecl* valueDecl)
{
	auto &type = valueDecl->type;
	auto &valueDefList = valueDecl->valueDefList;
	bool isConst = valueDecl->isConst();
	for (auto& valueDef : valueDefList) {
		auto& ident = valueDef->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(type->type,SymbolAttr::SymbolRole::Value,0,isConst);	//确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}
}

void SemanticVisitor::visit(ValueDef* valueDef)
{
}

void SemanticVisitor::visit(FuncDef* funcDef)
{
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	SymbolAttr* symbolAttr = new SymbolAttr(type->type,SymbolAttr::SymbolRole::Function);
	this->table->addSymbol(ident->identStr, symbolAttr);

	vector<unique_ptr<FuncParamDecl>>& funcParamDeclList = funcDef->funcParamDeclList;
	unique_ptr<BlockStmt>& block = funcDef->block;
	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// 确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}
	block->accept(*this);
}

void SemanticVisitor::visit(AssignStmt* assignStmt)
{
}

void SemanticVisitor::visit(BlockStmt* blockStmt)
{
	this->table->inScope();
	vector<unique_ptr<ASTUnit>>& stmts = blockStmt->stmts;
	for (vector<unique_ptr<ASTUnit>>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	cout << *(this->table) << endl;
	this->table->outScope();	//包含了清空局部变量动作
}

void SemanticVisitor::visit(BreakStmt* breakStmt)
{
}

void SemanticVisitor::visit(ContinueStmt* continueStmt)
{
}

void SemanticVisitor::visit(EmptyStmt* emptyStmt)
{
}

void SemanticVisitor::visit(ExpStmt* expStmt)
{
}

void SemanticVisitor::visit(IfStmt* ifStmt)
{
}

void SemanticVisitor::visit(ReturnStmt* returnStmt)
{
}

void SemanticVisitor::visit(WhileStmt* whileStmt)
{
}

void SemanticVisitor::visit(BinaryExp* binaryExp)
{
}

void SemanticVisitor::visit(FuncallExp* funcallExp)
{
}

void SemanticVisitor::visit(PrimaryExp* primaryExp)
{
}

void SemanticVisitor::visit(UnaryExp* unaryExp)
{
}

void SemanticVisitor::visit(Type* type)
{
}

void SemanticVisitor::visit(ConstantInt* constantInt)
{
}

void SemanticVisitor::visit(Ident* ident)
{
}