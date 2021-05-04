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
		std::unique_ptr<Ident> ident;
		std::vector<std::unique_ptr<Exp>> funcallParamList;
	public:
		FuncallExp(std::unique_ptr<Ident> ident);
		FuncallExp(std::unique_ptr<Ident> ident,std::vector<std::unique_ptr<Exp>> funcallParamList);
		virtual void accept(ASTVisitor& visitor);
	};
}

