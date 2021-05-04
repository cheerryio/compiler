#pragma once
#include <vector>
#include <memory>

#include "Type.h"
#include "Decl.h"
#include "ValueDef.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
	class ValueDecl:public Decl
	{
	public:
		unique_ptr<Type> type;
		std::vector<unique_ptr<ValueDef>> ValueDefList;
	public:
		ValueDecl(unique_ptr<Type> type);
		ValueDecl(unique_ptr<Type> type,std::vector<unique_ptr<ValueDef>> ValueDefList);
		virtual void accept(ASTVisitor& visitor);
	};
}
