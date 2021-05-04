#pragma once
#include <memory>
#include <vector>

#include "Stmt.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
    class WhileStmt :
        public Stmt
    {
    public:
        std::unique_ptr<Exp> cond;
        std::unique_ptr<Stmt> body;

    public:
        WhileStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> body);
        virtual void accept(ASTVisitor& visitor);
    };
}

