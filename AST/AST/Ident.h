#pragma once
#include <string>

#include "ASTUnit.h"

namespace saltyfish {
	class ASTVisitor;
	class SymbolAttr;

	class Ident
		:virtual public ASTUnit
	{
	public:
		class IdentBitFields {
		public:
			unsigned isConst : 1;
			unsigned isArray : 1;
		} bitFields;
	public:
		std::string identStr;
		SymbolAttr* symbolAttr = nullptr;
	public:
		Ident(std::string identStr, location loc);
		void setConst();
		void setArray();
		bool getConst() const;
		bool getArray() const;
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const Ident& ident);
	};
}