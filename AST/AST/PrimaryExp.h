#pragma once
#include <memory>
#include <map>

#include "Exp.h"
#include "Ident.h"
#include "Constant.h"
#include "ConstantInt.h"

namespace saltyfish {
	class ASTVisitor;

	class PrimaryExp:public Exp
	{
	public:
		ASTUnit::UnitType childType;
	public:
		union {
			saltyfish::Ident* ident;
			saltyfish::ConstantInt* constantInt;
		};
	public:
		PrimaryExp(saltyfish::Ident* ident,location loc);
		PrimaryExp(saltyfish::ConstantInt* constantInt,location loc);
		~PrimaryExp();
		virtual void accept(ASTVisitor& visitor);
		virtual bool isConstExp();
		virtual bool equals(PrimaryExp* primaryExp);

		friend std::ostream& operator<<(std::ostream& o, const PrimaryExp& primaryExp);
	};
}

