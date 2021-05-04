#pragma once
#include <memory>
#include <vector>

#include "Stmt.h"
#include "Exp.h"

namespace saltyfish {
    class ReturnStmt :
        public Stmt
    {
    public:
        class ReturnBitFields {
        public:
            unsigned hasExp : 1;
        } bitFields;
        std::unique_ptr<Exp> exp;

    public:
        ReturnStmt();
        ReturnStmt(std::unique_ptr<Exp> exp);
        void setHasExp(bool b);
    };
}
