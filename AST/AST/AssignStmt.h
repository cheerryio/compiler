#pragma once
#include <vector>

#include "Stmt.h"
#include "Ident.h"
#include "Exp.h"

namespace saltyfish {
    class ASTVisitor;

    class AssignStmt :
        public Stmt
    {
    public:
        Ident* ident;
        Exp* exp;

    public:
        AssignStmt(Ident* ident, Exp* exp);
        AssignStmt(Ident* ident, Exp* exp,location loc);
        void accept(ASTVisitor& visitor);
    };
}

