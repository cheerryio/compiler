#pragma once
#include <memory>

#include "Ident.h"
#include "Type.h"
#include "Decl.h"

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
	};
}

