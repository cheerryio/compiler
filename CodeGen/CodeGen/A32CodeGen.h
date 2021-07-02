#pragma once
#include "CodeGen.h"

namespace saltyfish {
    class A32CodeGen :
        public CodeGen
    {
    public:
        A32CodeGen(CFG cfg);
        ~A32CodeGen();
    };
}
