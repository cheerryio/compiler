#pragma once
#include <memory>

#include "Ident.h"
#include "Type.h"
#include "Decl.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class FuncParamDecl :
        public Decl
    {
	public:
		std::unique_ptr<Type> type;
		std::unique_ptr<Ident> ident;

	public:
		FuncParamDecl();
		FuncParamDecl(std::unique_ptr<Type> type,std::unique_ptr<Ident> ident);
		virtual void accept(ASTVisitor& visitor);
	};
}

