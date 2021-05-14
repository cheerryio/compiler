#pragma once
#include <map>

#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;

	class Exp :
		virtual public ASTUnit 
	{
	public:
		enum ExpType {
			Mul, Div, Mod, Add, Sub,
			B, A, Be, Ae, E, Ne,
			And, Or,
			Equal, Not,
			UnaryAdd, UnarySub,
			Assign
		} expType;
	public:
		static std::map<Exp::ExpType, std::string> ExpTypeMap;
	public:
		Exp() {
			this->unitType = ASTUnit::UnitType::isExp;
		}
		bool isCondExp();
		virtual bool isConstExp() const = 0;
	};
}