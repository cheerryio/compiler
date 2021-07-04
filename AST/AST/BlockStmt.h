#pragma once
#include <vector>

#include "ASTUnit.h"
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class BlockStmt :
        public Stmt
    {
    public:
        std::vector<ASTUnit*> stmts;

    public:
        BlockStmt(location loc);
        BlockStmt(std::vector<ASTUnit*> stmts,location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

