#pragma once
#include <string>
#include <memory>

#include "Exp.h"
#include "Ident.h"

using namespace std;

#include <vector>
#include <memory>

#include "Exp.h"
#include "ASTUnit.h"


namespace saltyfish {
	class ASTVisitor;

	class ValueDef
		:virtual public ASTUnit
	{
	public:
		class ValueDefBitFields {
		public:
			unsigned hasAssign : 1;
			unsigned isArrayFirstDimEmpty : 1;
			unsigned isArrayAssign : 1;
		} bitFields;

		struct ArrayList {
			enum class Type {
				Val, List
			} type;
			union {
				Exp* val;
				vector<ArrayList*> list;
			};
		public:
			ArrayList() {}
			~ArrayList() {}
		};

		Ident* ident;
		vector<Exp*> arrayDimList;
		Exp* exp;

	public:
		ValueDef(Ident* ident, vector<Exp*> arrayDimList,location loc);
		ValueDef(Ident* ident, vector<Exp*> arrayDimList, Exp* exp,location loc);
		virtual void accept(ASTVisitor& visitor);
	};
}