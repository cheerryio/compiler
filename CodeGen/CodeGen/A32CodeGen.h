#pragma once
#include <set>
#include <unordered_map>
#include <string>
#include <assert.h>
#include "CodeGen.h"
#include "A32.h"

namespace saltyfish {
    class A32CodeGen final:
        public CodeGen
    {
    public:
        std::unordered_map<std::string, std::set<A32::Register>> avalue;    // name to registers and memory
        std::unordered_map<A32::Register, std::set<std::string>> rvalue;    // register to name
    public:
        A32CodeGen();
        A32CodeGen(CFG cfg);
        ~A32CodeGen();
        A32::Register getRegister(TACOpn* opn1, TACOpn* opn2, TACOpn* result);
    };
}
