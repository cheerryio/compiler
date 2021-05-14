#pragma once
#include <memory>
#include <map>

#include "Exp.h"
#include "Ident.h"
#include "Constant.h"
#include "ConstantInt.h"
#include "SymbolTable.h"

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
			std::unique_ptr<saltyfish::ConstantInt> constantInt;
		};
	public:
		static std::map<PrimaryExpType, std::string> primaryExpTypeMap;
	public:
		PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Ident> ident,location loc);
		PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::ConstantInt> constantInt,location loc);
		~PrimaryExp();
		virtual bool isConstExp() const;
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const PrimaryExp& primaryExp);
	};
}

