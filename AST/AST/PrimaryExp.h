#pragma once
#include <memory>

#include "Exp.h"
#include "Ident.h"
#include "Constant.h"

namespace saltyfish {
	class ASTVisitor;

	class PrimaryExp:public Exp
	{
	public:
		enum PrimaryExpType {
			Ident, ConstantInt
		} primaryExpType;
		union {
			std::unique_ptr<saltyfish::Ident> ident;
			std::unique_ptr<saltyfish::Constant> constant;
		};
	public:
		PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Ident> ident);
		PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Constant> constant);
		~PrimaryExp();
		virtual void accept(ASTVisitor& visitor);
	};
}

