#pragma once
#include <vector>
#include <memory>

#include "ASTUnit.h"

namespace saltyfish {
    class CompUnit :
        virtual public ASTUnit
    {
    public:
        std::vector<ASTUnit*> compUnitList;

    public:
        CompUnit(std::vector<ASTUnit*> compUnitList,location loc);
        void accept(ASTVisitor& visitor);
    };
}

