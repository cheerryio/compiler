#pragma once
#include <string>
#include <vector>
#include <memory>
#include <vector>

#include "Ident.h"
#include "Exp.h"

namespace saltyfish {
	class ASTVisitor;

	class FuncallExp:public Exp
	{
	public:
		Ident* ident;
		std::vector<Exp*> funcallParamList;
	public:
		FuncallExp(Ident* ident,location loc);
		FuncallExp(Ident* ident, std::vector<Exp*>& funcallParamList,location loc);
		virtual bool isConstExp();

		virtual void accept(ASTVisitor& visitor);
	};
}

