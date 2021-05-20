#pragma once
#include <vector>
#include <memory>

#include "Exp.h"
#include "Stmt.h"

namespace saltyfish {
    class ASTVisitor;

    class ExpStmt :
        public Stmt
    {
    public:
        Exp* exp;

    public:
        ExpStmt(Exp* exp,location loc);
        virtual void accept(ASTVisitor& visitor);
    };
}

