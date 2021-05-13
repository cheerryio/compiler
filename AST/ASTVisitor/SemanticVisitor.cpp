#include <iostream>

#include "SemanticVisitor.h"

using namespace std;
using namespace saltyfish;

map<SemanticVisitor::ErrorCode, string> SemanticVisitor::errorMessage = {
	{SemanticVisitor::ErrorCode::DulicateDeclare,"DulplicateDeclare"},
	{SemanticVisitor::ErrorCode::VariableNotDeclared,"VariableNotDeclared"},
	{SemanticVisitor::ErrorCode::AssignNotLVal,"AssignNotLVal"},
	{SemanticVisitor::ErrorCode::BreakNotInLoop,"BreakNotInLoop"},
	{SemanticVisitor::ErrorCode::ContinueNotInLoop,"ContinueNotInLoop"},
	{SemanticVisitor::ErrorCode::ReturnNotInFunction,"ReturnNotInFunction"},
	{SemanticVisitor::ErrorCode::ConstNotAssignedByVar,"ConstNotAssignedByVar"}
};

SemanticVisitor::SemanticVisitor(SymbolTableList* table)
	:table(table)
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
	for (auto& valueDef : valueDefList) {
		auto& ident = valueDef->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(type->type,SymbolAttr::SymbolRole::Value,ident->getArray(),ident->getConst());	//确认const array
		if (this->table->addSymbol(ident->identStr, symbolAttr) == nullptr) {
			this->error(SemanticVisitor::ErrorCode::DulicateDeclare, ident->identStr, ident->getLoc());
			//exit(-1);
		}
		ident->symbolAttr = symbolAttr;
		//检验赋值表达式常量变量
		if (valueDef->bitFields.hasAssign) {
			auto& exp = valueDef->exp;
			exp->accept(*this);		//判断exp中是否有符号未被定义
			if (ident->getConst()) {
				if (!exp->isConstExp()) {
					string message = "";
					this->error(SemanticVisitor::ErrorCode::ConstNotAssignedByVar, message, ident->getLoc());
					//exit(-1);
				}
			}
		}
	}
}

void SemanticVisitor::visit(ValueDef* valueDef)
{
}

/**
* 函数名字进入符号表，额外记录其对应参数位置
*/
void SemanticVisitor::visit(FuncDef* funcDef)
{
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	SymbolAttr* symbolAttr = new SymbolAttr(type->type,SymbolAttr::SymbolRole::Function);
	if (this->table->addSymbol(ident->identStr, symbolAttr) == nullptr) {
		this->error(SemanticVisitor::ErrorCode::DulicateDeclare, ident->identStr, ident->getLoc());
		//exit(-1);
	}
	vector<unique_ptr<FuncParamDecl>>& funcParamDeclList = funcDef->funcParamDeclList;
	unique_ptr<BlockStmt>& block = funcDef->block;
	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// 确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}

	this->bitFields.inFunction = 1;
	block->accept(*this);
	this->bitFields.inFunction = 0;
}

void SemanticVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	ident->accept(*this);
	exp->accept(*this);
	if (ident->getConst()) {
		this->error(SemanticVisitor::ErrorCode::AssignNotLVal, ident->identStr, ident->getLoc());
		//exit(-1);
	}
	//计算exp属性是否和ident匹配
}

void SemanticVisitor::visit(BlockStmt* blockStmt)
{
	this->table->inScope();
	vector<unique_ptr<ASTUnit>>& stmts = blockStmt->stmts;
	for (vector<unique_ptr<ASTUnit>>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	this->table->outScope();
}

void SemanticVisitor::visit(BreakStmt* breakStmt)
{
	string message = "";
	if (!this->bitFields.inWhile) {
		this->error(SemanticVisitor::ErrorCode::BreakNotInLoop, message, breakStmt->getLoc());
		//exit(-1);
	}
}

void SemanticVisitor::visit(ContinueStmt* continueStmt)
{
	string message = "";
	if (!this->bitFields.inWhile) {
		this->error(SemanticVisitor::ErrorCode::ContinueNotInLoop, message, continueStmt->getLoc());
		//exit(-1);
	}
}

void SemanticVisitor::visit(EmptyStmt* emptyStmt)
{
}

void SemanticVisitor::visit(ExpStmt* expStmt)
{
	auto& exp = expStmt->exp;
	exp->accept(*this);
}

void SemanticVisitor::visit(IfStmt* ifStmt)
{
	auto& cond = ifStmt->cond;
	auto& ifBody = ifStmt->ifBody;
	auto& elseBody = ifStmt->elseBody;
	cond->accept(*this);
	ifBody->accept(*this);
	if (ifStmt->hasElse()) {
		elseBody->accept(*this);
	}
}

void SemanticVisitor::visit(ReturnStmt* returnStmt)
{
	//return语句只能出现在函数之中
	if (this->bitFields.inFunction == 0) {
		string message = "";
		this->error(SemanticVisitor::ErrorCode::ReturnNotInFunction, message, returnStmt->getLoc());
		//exit(-1);
	}
	if (returnStmt->hasExp()) {
		auto& exp = returnStmt->exp;
		exp->accept(*this);
	}
}

void SemanticVisitor::visit(WhileStmt* whileStmt)
{
	this->bitFields.inWhile = 1;;
	auto& cond = whileStmt->cond;
	auto& body = whileStmt->body;
	cond->accept(*this);
	body->accept(*this);
	this->bitFields.inWhile = 0;;
}

void SemanticVisitor::visit(BinaryExp* binaryExp)
{
	auto& Lexp = binaryExp->Lexp;
	auto& Rexp = binaryExp->Rexp;
	Lexp->accept(*this);
	Rexp->accept(*this);
}

void SemanticVisitor::visit(FuncallExp* funcallExp)
{
	auto& ident = funcallExp->ident;
	//在符号表中查找函数名字定义

}

void SemanticVisitor::visit(PrimaryExp* primaryExp)
{
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		auto& ident = primaryExp->ident;
		ident->accept(*this);
	}
}

void SemanticVisitor::visit(UnaryExp* unaryExp)
{
	auto& exp = unaryExp->exp;
	exp->accept(*this);
}

void SemanticVisitor::visit(Type* type)
{
}

void SemanticVisitor::visit(ConstantInt* constantInt)
{
}

/**
* 所有非声明语句变量的出现转到此处
* 需要查符号表判断该符号是否被定义
*/
void SemanticVisitor::visit(Ident* ident)
{
	SymbolAttr* symbolAttr = this->table->getSymbol(ident->identStr);
	if (symbolAttr == nullptr) {
		this->error(SemanticVisitor::ErrorCode::VariableNotDeclared, ident->identStr, ident->getLoc());
		//exit(-1);
	}
	ident->symbolAttr = symbolAttr;
}

void SemanticVisitor::error(ErrorCode code, std::string& message, location loc)
{
	cerr << SemanticVisitor::errorMessage.at(code) << endl
		<< message << "    "
		<< loc << endl;
}
