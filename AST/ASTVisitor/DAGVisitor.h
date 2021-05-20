#pragma once
#include "ASTVisitor.h"

namespace saltyfish {
    class DAGVisitor :
        public ASTVisitor
    {
	public:
		vector<Exp*> expBasket;
	public:
		DAGVisitor();
		virtual ~DAGVisitor();

		virtual void visit(CompUnit* compUnit);

		virtual void visit(FuncDecl* funcDecl);
		virtual void visit(FuncParamDecl* funcParamDecl);
		virtual void visit(ValueDecl* valueDecl);

		virtual void visit(ValueDef* valueDef);
		virtual void visit(FuncDef* funcDef);

		virtual void visit(AssignStmt* assignStmt);
		virtual void visit(BlockStmt* blockStmt);
		virtual void visit(BreakStmt* breakStmt);
		virtual void visit(ContinueStmt* continueStmt);
		virtual void visit(EmptyStmt* emptyStmt);
		virtual void visit(ExpStmt* expStmt);
		virtual void visit(IfStmt* ifStmt);
		virtual void visit(ReturnStmt* returnStmt);
		virtual void visit(WhileStmt* whileStmt);

		virtual void visit(BinaryExp* binaryExp);
		virtual void visit(FuncallExp* funcallExp);
		virtual void visit(PrimaryExp* primaryExp);
		virtual void visit(UnaryExp* unaryExp);

		virtual void visit(Type* type);
		virtual void visit(ConstantInt* constantInt);
		virtual void visit(Ident* ident);
    };
}

