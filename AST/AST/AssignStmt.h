#pragma once
#include <vector>
#include <memory>

#include "Stmt.h"
#include "Ident.h"
#include "Exp.h"

namespace saltyfish {
    class ASTVisitor;

    class AssignStmt :
        public Stmt
    {
    public:
        std::unique_ptr<Ident> ident;
        std::unique_ptr<Exp> exp;

    public:
        AssignStmt(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp);
        void accept(ASTVisitor& visitor);
    };
}

