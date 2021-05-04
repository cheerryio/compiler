#pragma once
#include "ASTVisitor.h"
namespace saltyfish {
    class MessageVisitor :
        public ASTVisitor
    {
    public:
		void visit();
		void visit(FuncDecl* funcDecl);
		void visit(ValueDecl* valueDecl);

		void visit(AssignStmt* assignStmt);
		void visit(BlockStmt* blockStmt);
		void visit(BreakStmt* breakStmt);
		void visit(ContinueStmt* continueStmt);
		void visit(EmptyStmt* emptyStmt);
		void visit(ExpStmt* expStmt);
		void visit(IfStmt* ifStmt);
		void visit(ReturnStmt* returnStmt);
		void visit(WhileStmt* whileStmt);

		void visit(BinaryExp* binaryExp);
		void visit(FuncallExp* funcallExp);
		void visit(PrimaryExp* primaryExp);
		void visit(UnaryExp* unaryExp);

		void visit(Type* type);
		void visit(ConstantInt* constantInt);
		void visit(Ident* ident);

    };
}
