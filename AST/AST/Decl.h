#pragma once
#include "Type.h"
#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;

	class Decl :
		virtual public ASTUnit
	{
	public:
		Decl() {
			this->unitType = ASTUnit::UnitType::isDecl;
		}
		virtual void accept(ASTVisitor& visitor) {
			
		}
	};
}

