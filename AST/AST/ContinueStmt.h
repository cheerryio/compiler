#pragma once
#include "Stmt.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class ContinueStmt :
        public Stmt
    {
    public:
        ContinueStmt();
        virtual void accept(ASTVisitor& visitor);
    };
}

