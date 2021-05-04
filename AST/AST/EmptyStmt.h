#pragma once
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class EmptyStmt :
        public Stmt
    {
    public:
        EmptyStmt();
        virtual void accept(ASTVisitor& visitor);
    };
}

