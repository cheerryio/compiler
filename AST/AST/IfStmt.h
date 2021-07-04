#pragma once
#include <memory>
#include <vector>

#include "Stmt.h"
#include "Exp.h"

namespace saltyfish {
    class ASTVisitor;

    class IfStmt :
        public Stmt
    {
    public:
        class IfStmtBitFields {
        public:
            unsigned hasElse : 1;
        } bitFields;
        Exp* cond;
        Stmt* ifBody,* elseBody;

    public:
        IfStmt(Exp* cond, Stmt* ifBody,location loc);
        IfStmt(Exp* cond, Stmt* ifBody, Stmt* elseBody,location loc);
        bool hasElse();
        void setHasElse(bool b);
        virtual void accept(ASTVisitor& visitor);
    };
}

