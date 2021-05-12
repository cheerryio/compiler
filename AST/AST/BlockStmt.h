#pragma once
#include <vector>
#include <memory>

#include "ASTUnit.h"
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class BlockStmt :
        public Stmt
    {
    public:
        std::vector<std::unique_ptr<ASTUnit>> stmts;

    public:
        BlockStmt(location loc);
        BlockStmt(std::vector<std::unique_ptr<ASTUnit>> stmts,location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

