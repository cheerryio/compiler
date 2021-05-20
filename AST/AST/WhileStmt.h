#pragma once
#include <memory>
#include <vector>

#include "Stmt.h"
#include "Exp.h"

namespace saltyfish {
    class ASTVisitor;

    class WhileStmt :
        public Stmt
    {
    public:
        Exp* cond;
        Stmt* body;

    public:
        WhileStmt(Exp* cond, Stmt* body,location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

