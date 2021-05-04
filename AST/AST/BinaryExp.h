#pragma once
#include <string>
#include <memory>

#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
	class BinaryExp:public Exp {
	public:
		enum BinaryExpType {
			Mul, Div, Mod, Add, Sub,
			B, A, Be, Ae, E, Ne,
			And, Or,
			Equal
		} binaryExpType;
		std::string opStr;
		std::unique_ptr<Exp> Lexp;
		std::unique_ptr<Exp> Rexp;
	public:
		BinaryExp();
		BinaryExp(BinaryExpType binaryExpType, std::unique_ptr<Exp> Lexp, std::unique_ptr <Exp> Rexp);
		BinaryExp(BinaryExpType binaryExpType, std::unique_ptr<Exp> Lexp, std::unique_ptr<Exp> Rexp, std::string opStr);
		virtual void accept(ASTVisitor& visitor);
	};
}