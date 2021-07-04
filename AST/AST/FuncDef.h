#pragma once
#include <memory>
#include <vector>

#include "Type.h"
#include "Ident.h"
#include "FuncParamDecl.h"
#include "BlockStmt.h"
#include "ASTUnit.h"

namespace saltyfish {
    class ASTVisitor;

    class FuncDef :
        public ASTUnit
    {
    public:
        Type* type;
        Ident* ident;
        std::vector<FuncParamDecl*> funcParamDeclList;
        BlockStmt* block;

    public:
        FuncDef(Type* type, Ident* ident, BlockStmt* block,location loc);
        FuncDef(Type* type, Ident* ident, std::vector<FuncParamDecl*> funcParamDeclList, BlockStmt* block,location loc);
        void accept(ASTVisitor& visitor);
    };
}

