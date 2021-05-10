#pragma once
#include <unordered_map>
#include <string>
#include "SymbolTable.h"

namespace saltyfish {
    class SymbolTableList :
        public SymbolTable
    {
    public:
        std::unordered_map<std::string, SymbolAttr*> table;
    public:
        SymbolTableList();
        ~SymbolTableList();
        void inScope();
        void outScope();
        int addSymbol(std::string symbolName,SymbolAttr* symbolAttr);
        void clearSymbol();
        SymbolAttr* declared(std::string symbolName);
        bool dulplicateDeclared(std::string symbolName);
        friend std::ostream& operator<<(std::ostream& o, const SymbolTableList& symbolTable);
    };
}

