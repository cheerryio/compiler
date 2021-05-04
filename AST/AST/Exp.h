#pragma once
#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;

	class Exp :public ASTUnit {
	public:
		class ExpBitFields {
		} bitFields;

	public:
		Exp();
		virtual void accept(ASTVisitor& visitor) {
			
		}
	};
}