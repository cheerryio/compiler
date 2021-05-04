#pragma once
#include <vector>
#include <memory>

#include "Exp.h"
#include "Stmt.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class ExpStmt :
        public Stmt
    {
    public:
        std::unique_ptr<Exp> exp;

    public:
        ExpStmt(std::unique_ptr<Exp> exp);
        virtual void accept(ASTVisitor& visitor);
    };
}

