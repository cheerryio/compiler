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
        level_t getLevel();
        void inScope();
        void outScope();
        SymbolAttr* addSymbol(std::string symbolName,SymbolAttr* symbolAttr);
        void delSymbols();
        SymbolAttr* getSymbolinLevel(std::string symbolName, level_t level);
        SymbolAttr* getSymbol(std::string symbolName);
        bool dulplicateDeclared(std::string symbolName);
        friend std::ostream& operator<<(std::ostream& o, const SymbolTableList& symbolTable);
    };
}

