#pragma once
#include "Stmt.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class EmptyStmt :
        public Stmt
    {
    public:
        EmptyStmt();
        virtual void accept(ASTVisitor& visitor);
    };
}

