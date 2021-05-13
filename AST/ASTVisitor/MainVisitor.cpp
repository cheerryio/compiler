#include "MainVisitor.h"

using namespace std;
using namespace saltyfish;

#define MESSAGE_VISITOR		0x00000001
#define SEMANTIC_VISITOR	0x00000010

MainVisitor::MainVisitor(unsigned mode) {
	SymbolTableList* table = new SymbolTableList();
	new (this)MainVisitor(mode, table);
}

MainVisitor::MainVisitor(unsigned mode, SymbolTableList* table)
	:table(table)
{
	this->messageVisitor = new MessageVisitor();
	this->semanticVisitor = new SemanticVisitor(table);

	if (mode & MESSAGE_VISITOR)	this->visitors.push_back(messageVisitor);
	if (mode & SEMANTIC_VISITOR) this->visitors.push_back(semanticVisitor);
}

void MainVisitor::visit(CompUnit* compUnit)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(compUnit);
}

void MainVisitor::visit(FuncDecl* funcDecl)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(funcDecl);
}

void MainVisitor::visit(FuncParamDecl* funcParamDecl)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(funcParamDecl);
}

void MainVisitor::visit(ValueDecl* valueDecl)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(valueDecl);
}

void MainVisitor::visit(ValueDef* valueDef)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(valueDef);
}

void MainVisitor::visit(FuncDef* funcDef)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(funcDef);
}

void MainVisitor::visit(AssignStmt* assignStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(assignStmt);
}

void MainVisitor::visit(BlockStmt* blockStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(blockStmt);
}

void MainVisitor::visit(BreakStmt* breakStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(breakStmt);
}

void MainVisitor::visit(ContinueStmt* continueStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(continueStmt);
}

void MainVisitor::visit(EmptyStmt* emptyStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(emptyStmt);
}

void MainVisitor::visit(ExpStmt* expStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(expStmt);
}

void MainVisitor::visit(IfStmt* ifStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(ifStmt);
}

void MainVisitor::visit(ReturnStmt* returnStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(returnStmt);
}

void MainVisitor::visit(WhileStmt* whileStmt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(whileStmt);
}

void MainVisitor::visit(BinaryExp* binaryExp)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(binaryExp);
}

void MainVisitor::visit(FuncallExp* funcallExp)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(funcallExp);
}

void MainVisitor::visit(PrimaryExp* primaryExp)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(primaryExp);
}

void MainVisitor::visit(UnaryExp* unaryExp)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(unaryExp);
}

void MainVisitor::visit(Type* type)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(type);
}

void MainVisitor::visit(ConstantInt* constantInt)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(constantInt);
}

void MainVisitor::visit(Ident* ident)
{
	for (ASTVisitor* visitor : this->visitors)	visitor->visit(ident);
}