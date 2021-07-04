#include "MFuncTab.h"

using namespace std;
using namespace saltyfish;

MFuncTab::MFuncTab()
{
}

MFuncTab::~MFuncTab()
{
}

FuncAttr* MFuncTab::addFunc(std::string name, FuncAttr* funcAttr)
{
    if (this->tab.find(name) != this->tab.end())    // find name as key in funcTab
        return nullptr;
    this->tab[name] = funcAttr;
    this->func = funcAttr;
    return funcAttr;
}

FuncAttr* MFuncTab::delFunc(std::string name)
{
    if (this->tab.find(name) == this->tab.end())    // not find name as key in tab
        return nullptr;
    auto it = this->tab.find(name);
    FuncAttr* attr = it->second;
    this->tab.erase(it);
    return attr;
}

FuncAttr* MFuncTab::getFunc()
{
    return this->func;
}
