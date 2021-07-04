#pragma once
#include <iostream>
#include <iomanip>
#include "Table.h"
namespace saltyfish {
    class MMNameTab final :
        public NameTab
    {
	public:
		NameAttr* lastName = nullptr;
		std::vector<NameAttr*> lastNameStack;
		std::unordered_map<std::string, NameAttr*> tab;
		std::vector<std::unordered_map<std::string, NameAttr*>> tabStack;
    public:
		MMNameTab();
		virtual ~MMNameTab();
    	virtual level_t getLevel();
		virtual void inBlock();	// enter a block, either a function block or a block
		virtual void outBlock(); // leave a block, either a function block or a block
		virtual NameAttr* addName(std::string name,NameAttr* nameAttr);
		virtual void delNames(level_t level);	// delete all names in level
		virtual NameAttr* getName(std::string name, level_t level);
		virtual NameAttr* getName(std::string name);
		NameAttr* getLastName(std::string name);
		virtual bool dulDeclare(std::string name);
		friend std::ostream& operator<<(std::ostream& o, const MMNameTab& nameTab);
    };
}
