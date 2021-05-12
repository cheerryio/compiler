#pragma once
#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;

	class Exp :
		virtual public ASTUnit 
	{
	public:
		class ExpBitFields {
		} bitFields;

	public:
		Exp() {
			this->unitType = ASTUnit::UnitType::isExp;
		}
		virtual bool isConstExp() const = 0;
	};
}