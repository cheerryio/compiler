#pragma once
#include "Table.h"
namespace saltyfish {
    class MFuncTab final:
        public FuncTab
    {
    public:
        std::unordered_map<std::string, FuncAttr*> tab;
    public:
        MFuncTab();
        virtual ~MFuncTab();
        virtual FuncAttr* addFunc(std::string name, FuncAttr* funcAttr);
        virtual FuncAttr* delFunc(std::string name);
        virtual FuncAttr* getFunc();
    };
}
