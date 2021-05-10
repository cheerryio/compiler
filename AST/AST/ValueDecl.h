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
		unique_ptr<Type> type;
		std::vector<unique_ptr<ValueDef>> valueDefList;
	public:
		ValueDecl(unique_ptr<Type> type,std::vector<unique_ptr<ValueDef>> valueDefList);
		ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> valueDefList,location loc);
		virtual void accept(ASTVisitor& visitor);
	};
}
