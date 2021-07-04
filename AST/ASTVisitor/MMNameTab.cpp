#include "MMNameTab.h"

using namespace std;
using namespace saltyfish;

saltyfish::MMNameTab::MMNameTab()
{
}

saltyfish::MMNameTab::~MMNameTab()
{
}

MMNameTab::level_t MMNameTab::getLevel()
{
    return this->level;
}

void MMNameTab::inBlock()
{
    this->level++;
    assert(this->level > 0);
    tabStack.push_back(this->tab);
    this->tab.clear();
    assert(this->tab.empty());
    this->lastNameStack.push_back(this->lastName);
    this->lastName = nullptr;
}

void MMNameTab::outBlock()
{
    this->delNames(this->level);
    assert(!this->tabStack.empty());
    this->tab=tabStack.back();
    tabStack.pop_back();
    assert(this->level > 0);
    this->level--;
    assert(!this->lastNameStack.empty());
    this->lastName = this->lastNameStack.back();
    this->lastNameStack.pop_back();
}

NameAttr* MMNameTab::addName(std::string name, NameAttr* nameAttr)
{
    if(this->tab.find(name)!=this->tab.end()){
        // find name as key in this->tab
        return nullptr;
    }
    nameAttr->link = this->getLastName(name);
    this->tab[name]=nameAttr;
    this->lastName = nameAttr;
    return nameAttr;
}

void MMNameTab::delNames(level_t level)
{
// no need to implement the function in this tab implementation
}

NameAttr* MMNameTab::getName(std::string name, level_t level)
{
    return nullptr;
}

NameAttr* MMNameTab::getName(std::string name)
{
    // check current this->tab first, and then this->tabStack in back-to-front order
    if(this->tab.find(name)!=this->tab.end())
        return this->tab.at(name);
    for(auto it=this->tabStack.rbegin();it!=this->tabStack.rend();it++){
        if(it->find(name)!=it->end())
            return it->at(name);
    }
    return nullptr;
}

NameAttr* MMNameTab::getLastName(std::string name)
{
    return this->lastName;
}

bool MMNameTab::dulDeclare(std::string name)
{
    // only have to check current block variables to see if dul declare
    return this->tab.find(name)!=this->tab.end()?true:false;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const MMNameTab& nameTab)
	{
		o << setfill(' ')
			<< endl << endl
			<< "Level: " << nameTab.level
			<< endl << endl << endl << endl;

		o << setfill(' ')
			<< setw(6) << "name"
			<< setw(3) << "|"
			<< setw(6) << "alias"
            << setw(3) << "|"
			<< setw(12) << "kind"
			<< setw(3) << "|"
			<< setw(6) << "level"
			<< setw(3) << "|"
			<< setw(6) << "type"
			<< setw(3) << "|"
			<< setw(6) << "isParam"
			<< setw(3) << "|"
			<< setw(6) << "val"
			<< setw(3) << "|"
			<< endl;
		for (auto it = nameTab.tab.begin(); it != nameTab.tab.end(); it++) {
            NameAttr* nameAttr=it->second;
            o << setfill('-') << setw(120) << "" << endl;
            o << setfill(' ')
                << setw(6) << nameAttr->name
                << setw(3) << "|"
                << setw(6) << nameAttr->alias
                << setw(3) << "|"
                << setw(12) << (nameAttr->kind==NameAttr::NameKind::Constant?"Constant":nameAttr->kind==NameAttr::NameKind::Variable?"Variable":nameAttr->kind==NameAttr::NameKind::Function?"Function":"Type")
                << setw(3) << "|"
                << setw(6) << nameAttr->level
                << setw(3) << "|"
                << setw(6) << (nameAttr->type == Type::TypeCode::Void ? "Void" : "Int")
                << setw(3) << "|"
                << setw(6) << (nameAttr-> isParam? "Yes" : "No")
                << setw(3) << "|"
                << setw(6) << nameAttr->val
                << setw(3) << "|" << endl;
		}
		return o;
	}
}