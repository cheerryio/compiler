#pragma once
#include <string>
#include <memory>
#include <map>

#include "Exp.h"

namespace saltyfish {
	class ASTVisitor;

	class UnaryExp:public Exp
	{
	public:
		std::string opStr;
		Exp* exp;
	public:
		UnaryExp(Exp::ExpType expType, Exp* exp,location loc);
		virtual void accept(ASTVisitor& visitor);
		virtual bool isConstExp();
		virtual bool equals(UnaryExp* unaryExp);

		friend std::ostream& operator<<(std::ostream& o, const UnaryExp& unaryExp);
	};

}

