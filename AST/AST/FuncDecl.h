#pragma once
#include <memory>

#include "Ident.h"
#include "Decl.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
	class FuncDecl:public Decl
	{
	public:
		std::unique_ptr<Ident> ident;

	public:
		FuncDecl(std::unique_ptr<Ident> ident);
		virtual void accept(ASTVisitor& visitor);
	};
}

