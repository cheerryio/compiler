#pragma once
#include "ASTUnit.h"
#include "BinaryExp.h"
namespace saltyfish {
	class Ident;
	class Type;
	class ConstantInt;
	class EmptyStmt;
	class ExpStmt;
	class AssignStmt;
	class BlockStmt;
	class BreakStmt;
	class ContinueStmt;
	class IfStmt;
	class ReturnStmt;
	class WhileStmt;
	class FuncDecl;
	class ValueDecl;
	class FuncParamDecl;
	class ValueDef;
	class BinaryExp;
	class FuncallExp;
	class PrimaryExp;
	class UnaryExp;
}

namespace saltyfish {
	class ASTVisitor
	{
	public:
		virtual void visit() = 0;
		virtual void visit(FuncDecl* funcDecl) = 0;
		virtual void visit(FuncParamDecl* funcParamDecl) = 0;
		virtual void visit(ValueDecl* valueDecl) = 0;
		virtual void visit(ValueDef* valueDef) = 0;

		virtual void visit(AssignStmt* assignStmt) = 0;
		virtual void visit(BlockStmt* blockStmt) = 0;
		virtual void visit(BreakStmt* breakStmt) = 0;
		virtual void visit(ContinueStmt* continueStmt) = 0;
		virtual void visit(EmptyStmt* emptyStmt) = 0;
		virtual void visit(ExpStmt *expStmt) = 0;
		virtual void visit(IfStmt* ifStmt) = 0;
		virtual void visit(ReturnStmt* returnStmt) = 0;
		virtual void visit(WhileStmt* whileStmt) = 0;

		virtual void visit(BinaryExp* binaryExp) = 0;
		virtual void visit(FuncallExp* funcallExp) = 0;
		virtual void visit(PrimaryExp* primaryExp) = 0;
		virtual void visit(UnaryExp* unaryExp) = 0;

		virtual void visit(Type* type) = 0;
		virtual void visit(ConstantInt* constantInt) = 0;
		virtual void visit(Ident* ident) = 0;
	};
}

