#include "Type.h"

namespace saltyfish {
	Type::Type() {
		
	}

	Type::Type(std::string &typeStr) :typeStr(typeStr) {
		
	}

	void Type::accept(ASTVisitor& visitor) {
		visitor.visit(this);
	}
}