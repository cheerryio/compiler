#pragma once
#include <unordered_map>
#include <string>
#include <deque>
#include "SymbolTable.h"

namespace saltyfish {
    class SymbolTableList :
        public SymbolTable
    {
    public:
        unsigned tempIndex = 0;
        unsigned offset = 0;
        int paramOffset = -1;
        SymbolAttr* functionSymbol;
        std::deque<unsigned> offsetStack;
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

