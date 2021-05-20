#pragma once
#include <string>
#include <memory>
#include <map>
#include <memory>
#include "PrimaryExp.h"

#include "Exp.h"

namespace saltyfish {
	class ASTVisitor;

	class BinaryExp :
		public Exp 
	{
	public:
		std::string opStr;
		Exp* Lexp;
		Exp* Rexp;
	public:
		BinaryExp();
		BinaryExp(Exp::ExpType expType, Exp* Lexp, Exp* Rexp);
		BinaryExp(Exp::ExpType expType, Exp* Lexp, Exp* Rexp,location loc);
		virtual void accept(ASTVisitor& visitor);
		virtual bool isConstExp();
		virtual bool equals(BinaryExp* binaryExp);

		bool isOpExp();
		bool isRelExp();
		bool isBoolExp();
		PrimaryExp* reduce();

		friend std::ostream& operator<<(std::ostream& o, const BinaryExp& binaryExp);
	};
}