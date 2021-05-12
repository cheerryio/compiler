#pragma once
#include "ASTUnit.h"

namespace saltyfish {
    class ASTVisitor;

    class Stmt :
        virtual public ASTUnit
    {
    public:
        Stmt() {
            this->unitType = ASTUnit::UnitType::isStmt;
        }
        virtual void accept(ASTVisitor& visitor) {

        }
    };
}

