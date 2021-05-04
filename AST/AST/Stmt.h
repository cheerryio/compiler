#pragma once
#include "ASTUnit.h"

namespace saltyfish {
    class ASTVisitor;

    class Stmt :
        public ASTUnit
    {
    public:
        virtual void accept(ASTVisitor& visitor) {

        }
    };
}

