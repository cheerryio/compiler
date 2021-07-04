#pragma once
#include <map>

#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;
	class BinaryExp;
	class UnaryExp;
	class PrimaryExp;

	class Exp :
		virtual public ASTUnit 
	{
	public:
		enum ExpType {
			Add, Sub, Mul, Div, Mod,
			L, G, Le, Ge, E, Ne,
			And, Or,
			Equal, Not,
			UnaryAdd, UnarySub,
			Assign
		} expType;
	public:
		static std::map<Exp::ExpType, std::string> ExpTypeMap;
	public:
		class ExpBitFields {
		public:
			unsigned isConst : 1;
		} bitFields;
	public:
		Exp() {
			this->unitType = ASTUnit::UnitType::isExp;
		}
		virtual bool equals(Exp* exp) {
			switch (exp->unitType) {
			case(ASTUnit::UnitType::isBinaryExp):
				return this->equals((BinaryExp*)exp);
			case(ASTUnit::UnitType::isUnaryExp):
				return this->equals((UnaryExp*)exp);
			case(ASTUnit::UnitType::isPrimaryExp):
				return this->equals((PrimaryExp*)exp);
			default:
				return false;
			}
		}
		virtual bool equals(BinaryExp* binaryExp) { return false; }
		virtual bool equals(UnaryExp* unaryExp) { return false; }
		virtual bool equals(PrimaryExp* primaryExp) { return false; }
		virtual bool isConstExp() = 0;
	};
}