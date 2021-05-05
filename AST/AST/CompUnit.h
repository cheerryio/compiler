#pragma once
#include <vector>
#include <memory>

#include "ASTUnit.h"

namespace saltyfish {
    class CompUnit :
        public ASTUnit
    {
    public:
        std::vector<std::unique_ptr<ASTUnit>> compUnitList;

    public:
        CompUnit();
        CompUnit(std::vector<std::unique_ptr<ASTUnit>> compUnitList);
        void accept(ASTVisitor& visitor);
    };
}

