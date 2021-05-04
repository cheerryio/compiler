#pragma once
#include <string>
#include <memory>

#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
	class UnaryExp:public Exp
	{
	public:
		enum UnaryExpType {
			Add,Sub,Not
		} unaryExpType;
		std::string opStr;
		std::unique_ptr<Exp> exp;

	public:
		UnaryExp(UnaryExpType unaryExpType,std::unique_ptr<Exp> exp);
		virtual void accept(ASTVisitor& visitor);
	};

}

