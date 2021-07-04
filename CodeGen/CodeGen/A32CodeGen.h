#pragma once
#include <set>
#include <unordered_map>
#include <string>
#include "CodeGen.h"

namespace saltyfish {
    class A32CodeGen final:
        public CodeGen
    {
    public:
        enum class Registers {
            R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10
        } registers;
    public:
        std::unordered_map<std::string, std::set<A32CodeGen::Registers>> avalue;
        std::unordered_map<A32CodeGen::Registers, std::set<std::string>> rvalue;
    public:
        A32CodeGen(CFG cfg);
        ~A32CodeGen();
        A32CodeGen::Registers getRegister();
    };
}
