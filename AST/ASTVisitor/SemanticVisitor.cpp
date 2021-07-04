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

SemanticVisitor::SemanticVisitor() {
	this->nameTab = new MMNameTab();
}

SemanticVisitor::SemanticVisitor(MMNameTab* nameTab)
	:nameTab(nameTab)
{
	
}

void SemanticVisitor::visit(CompUnit* compUnit)
{
	vector<ASTUnit*>& compUnitList = compUnit->compUnitList;
	for (vector<ASTUnit*>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
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
	Type* type = valueDecl->type;
	auto& valueDefList = valueDecl->valueDefList;
	for (ValueDef* valueDef : valueDefList) {
		Ident* ident = valueDef->ident;
		NameAttr* nameAttr = new NameAttr(ident->name, ident->name, NameAttr::NameKind::Variable, this->nameTab->getLevel(), false);
		if (this->nameTab->addName(ident->name, nameAttr) == nullptr) {
			this->error(SemanticVisitor::ErrorCode::DulicateDeclare, ident->name, ident->getLoc());
			//exit(-1);
		}

		if (valueDef->bitFields.hasAssign) {
			Exp* exp = valueDef->exp;
			exp->accept(*this);
			if (ident->getConst()) {
				// check assign exp const exp
				if (!(exp->bitFields.isConst)) {
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

void SemanticVisitor::visit(FuncDef* funcDef)
{
	auto type = funcDef->type;
	auto ident = funcDef->ident;
	NameAttr* nameAttr = new NameAttr(ident->name, ident->name, NameAttr::NameKind::Function,this->nameTab->getLevel(),false);
	if (this->nameTab->addName(ident->name, nameAttr) == nullptr) {
		this->error(SemanticVisitor::ErrorCode::DulicateDeclare, ident->name, ident->getLoc());
		//exit(-1);
	}
	auto& funcParamDeclList = funcDef->funcParamDeclList;
	auto block = funcDef->block;
	for (vector<FuncParamDecl*>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		auto type = (*it)->type;
		auto ident = (*it)->ident;
		NameAttr* nameAttr = new NameAttr(ident->name,ident->name,NameAttr::NameKind::Variable,this->nameTab->getLevel(),true);
		this->nameTab->addName(ident->name, nameAttr);
	}

	block->accept(*this);
}

void SemanticVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	ident->accept(*this);
	exp->accept(*this);
	if (ident->getConst()) {
		this->error(SemanticVisitor::ErrorCode::AssignNotLVal, ident->name, ident->getLoc());
		//exit(-1);
	}
}

void SemanticVisitor::visit(BlockStmt* blockStmt)
{
	this->nameTab->inBlock();
	vector<ASTUnit*>& stmts = blockStmt->stmts;
	for (vector<ASTUnit*>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	this->nameTab->outBlock();
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
	auto cond = ifStmt->cond;
	auto ifBody = ifStmt->ifBody;
	auto elseBody = ifStmt->elseBody;
	cond->accept(*this);
	ifBody->accept(*this);
	if (ifStmt->hasElse()) {
		elseBody->accept(*this);
	}
}

void SemanticVisitor::visit(ReturnStmt* returnStmt)
{
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
	binaryExp->bitFields.isConst = Lexp->bitFields.isConst && Rexp->bitFields.isConst;
}

void SemanticVisitor::visit(FuncallExp* funcallExp)
{
	auto& ident = funcallExp->ident;

}

void SemanticVisitor::visit(PrimaryExp* primaryExp)
{
	if (primaryExp->childType == ASTUnit::UnitType::isIdent) {
		auto& ident = primaryExp->ident;
		ident->accept(*this);
		if (ident->bitFields.isConst) {
			primaryExp->bitFields.isConst = 1;
		}
	}
	else if(primaryExp->childType == ASTUnit::UnitType::isConstantInt) {
		primaryExp->bitFields.isConst = 1;
	}
}

void SemanticVisitor::visit(UnaryExp* unaryExp)
{
	auto& exp = unaryExp->exp;
	exp->accept(*this);
	unaryExp->bitFields.isConst = exp->bitFields.isConst;
}

void SemanticVisitor::visit(Type* type)
{
}

void SemanticVisitor::visit(ConstantInt* constantInt)
{
}

/**
* all non declare variable occurrences are directed here
* in here whether a variable was declared is checked
*/
void SemanticVisitor::visit(Ident* ident)
{
	NameAttr* nameAttr = this->nameTab->getName(ident->name);
	if (nameAttr == nullptr) {
		this->error(SemanticVisitor::ErrorCode::VariableNotDeclared, ident->name, ident->getLoc());
		//exit(-1);
	}
	ident->nameAttr = nameAttr;
}

void SemanticVisitor::error(ErrorCode code, std::string& message, location loc)
{
	cerr << SemanticVisitor::errorMessage.at(code) << endl
		<< message << "    "
		<< loc << endl;
}
