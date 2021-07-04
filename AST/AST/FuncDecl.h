#pragma once
#include <memory>

#include "Ident.h"
#include "Decl.h"

namespace saltyfish {
	class ASTVisitor;

	class FuncDecl:public Decl
	{
	public:
		Ident* ident;

	public:
		FuncDecl(Ident* ident,location loc);
		virtual void accept(ASTVisitor& visitor);
	};
}

