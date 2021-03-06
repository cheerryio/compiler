#pragma once
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class EmptyStmt :
        public Stmt
    {
    public:
        EmptyStmt(location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

