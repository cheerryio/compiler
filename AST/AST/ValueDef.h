#pragma once
#include <string>
#include <memory>

#include "Exp.h"
#include "Ident.h"

using namespace std;

#include <vector>
#include <memory>

#include "Exp.h"


namespace saltyfish {
	class ASTVisitor;

	class ValueDef {
	public:
		class ValueDefBitFields {
		public:
			unsigned hasAssign : 1;
			unsigned isArray : 1;
		} bitFields;
		unique_ptr<Ident> ident;
		vector<unique_ptr<Exp>> arrayDimList;
		unique_ptr<Exp> exp;

	public:
		ValueDef();
		ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList);
		ValueDef(unique_ptr<Ident> ident, vector<unique_ptr<Exp>> arrayDimList, unique_ptr<Exp> exp);
		void setHasAssign(bool b);
		void setIsArray(bool b);
		virtual void accept(ASTVisitor& visitor);
	};
}