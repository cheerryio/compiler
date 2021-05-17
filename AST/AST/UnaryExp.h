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
		std::unique_ptr<Exp> exp;
	public:
		UnaryExp(Exp::ExpType expType, std::unique_ptr<Exp> exp,location loc);
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const UnaryExp& unaryExp);
	};

}

