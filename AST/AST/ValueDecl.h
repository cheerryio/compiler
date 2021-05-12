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
		class BitFields {
		public:
			unsigned isConst : 1;
		} bitFields;

	public:
		ValueDecl(unique_ptr<Type> type,std::vector<unique_ptr<ValueDef>> valueDefList,unsigned isConst);
		ValueDecl(unique_ptr<Type> type, std::vector<unique_ptr<ValueDef>> valueDefList, unsigned isConst, location loc);
		bool isConst();
		virtual void accept(ASTVisitor& visitor);
	};
}
