#pragma once
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class ContinueStmt :
        public Stmt
    {
    public:
        ContinueStmt();
        virtual void accept(ASTVisitor& visitor);
    };
}

