#pragma once
#include <vector>
#include <memory>

#include "Type.h"
#include "Decl.h"
#include "ValueDef.h"

namespace saltyfish {
	class ASTVisitor;

	class ValueDecl:public Decl
	{
	public:
		Type* type;
		std::vector<ValueDef*> valueDefList;

	public:
		ValueDecl(Type* type, std::vector<ValueDef*> valueDefList, location loc);
		void setIdentConst();
		virtual void accept(ASTVisitor& visitor);
	};
}
