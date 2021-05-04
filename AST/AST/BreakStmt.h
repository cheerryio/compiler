#pragma once

#include "Stmt.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class BreakStmt :
        public Stmt
    {
    public:
        virtual void accept(ASTVisitor& visitor);
    };
}

