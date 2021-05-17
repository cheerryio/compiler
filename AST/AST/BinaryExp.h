#pragma once
#include <string>
#include <memory>
#include <map>

#include "Exp.h"

namespace saltyfish {
	class ASTVisitor;

	class BinaryExp :
		public Exp 
	{
	public:
		std::string opStr;
		std::unique_ptr<Exp> Lexp;
		std::unique_ptr<Exp> Rexp;
	public:
		BinaryExp();
		BinaryExp(Exp::ExpType expType, std::unique_ptr<Exp> Lexp, std::unique_ptr <Exp> Rexp);
		BinaryExp(Exp::ExpType expType, std::unique_ptr<Exp> Lexp, std::unique_ptr <Exp> Rexp,location loc);
		virtual void accept(ASTVisitor& visitor);

		bool isOpExp();
		bool isRelExp();
		bool isBoolExp();

		friend std::ostream& operator<<(std::ostream& o, const BinaryExp& binaryExp);
	};
}