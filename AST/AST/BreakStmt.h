#pragma once

#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class BreakStmt :
        public Stmt
    {
    public:
        BreakStmt(location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

