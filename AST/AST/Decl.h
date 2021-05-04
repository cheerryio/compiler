#pragma once
#include "Type.h"
#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;

	class Decl:public ASTUnit
	{
	public:
		virtual void accept(ASTVisitor& visitor) {
			
		}
	};
}

