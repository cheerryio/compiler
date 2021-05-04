#pragma once

#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class BreakStmt :
        public Stmt
    {
    public:
        virtual void accept(ASTVisitor& visitor);
    };
}

