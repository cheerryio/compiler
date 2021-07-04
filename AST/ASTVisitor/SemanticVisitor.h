#pragma once
#include <vector>
#include <map>
#include "ASTVisitor.h"
#include "MMNameTab.h"

namespace saltyfish {
	class SemanticVisitor :
		public ASTVisitor
	{
	public:
		class SemanticBitFields {
		public:
			unsigned inWhile : 1;
			unsigned inFunction : 1;

		} bitFields;
		enum class ErrorCode {
			DulicateDeclare,VariableNotDeclared,AssignNotLVal,
			BreakNotInLoop,ContinueNotInLoop,ReturnNotInFunction,
			ConstNotAssignedByVar
		};
		MMNameTab* nameTab = nullptr;

	public:
		static std::map<ErrorCode, std::string> errorMessage;

	public:
		SemanticVisitor();
		SemanticVisitor(MMNameTab* table);

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
		void error(ErrorCode code,std::string& message,location loc);
	};
}

