#pragma once
#include <memory>

#include "Ident.h"
#include "Type.h"
#include "Decl.h"

namespace saltyfish {
	class ASTVisitor;

    class FuncParamDecl :
        public Decl
    {
	public:
		Type* type;
		Ident* ident;

	public:
		FuncParamDecl(Type* type, Ident* ident,location loc);
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const FuncParamDecl& funcParamDecl);
	};
}

