#include "SymbolTableList.h"

using namespace std;
using namespace saltyfish;

SymbolTableList::SymbolTableList()
{

}

SymbolTableList::~SymbolTableList()
{

}

void SymbolTableList::inScope()
{
	this->level++;
}

void SymbolTableList::outScope() {
	this->level--;
}

int SymbolTableList::addSymbol(std::string symbolName,SymbolAttr* symbolAttr) {
	if (this->dulplicateDeclared(symbolName)) {
		return -1;
	}
	symbolAttr->level = this->level;
	SymbolAttr* head = nullptr;
	if (this->table.find(symbolName) == table.end()) {
		head = new SymbolAttr();
		head->prev = head;
		head->next = head;
		this->table[symbolName] = head;
	}
	else {
		head = this->table.find(symbolName)->second;
	}
	symbolAttr->next = head;
	symbolAttr->prev = head->prev;
	head->prev->next = symbolAttr;
	head->prev = symbolAttr;
	this->table[symbolName] = symbolAttr;

	return this->level;
}

// 删除层号等于level的所有符号
void SymbolTableList::clearSymbol() {
	for (unordered_map<string, SymbolAttr*>::iterator it = this->table.begin(); it != table.end(); it++) {
		SymbolAttr* head = it->second;
		SymbolAttr* pos = head;
		if (pos->level == this->level) {
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			delete pos;
		}
	}
}

SymbolAttr* SymbolTableList::declared(std::string symbolName) {
	if (this->table.find(symbolName) == this->table.end()) {
		return nullptr;
	}
	SymbolAttr* head = this->table.find(symbolName)->second;
	for (SymbolAttr* pos = head; pos != head->prev; pos = pos->next) {
		return pos;
	}
	return nullptr;
}

bool SymbolTableList::dulplicateDeclared(std::string symbolName) {
	if (this->table.find(symbolName) == this->table.end()) {
		return false;
	}
	SymbolAttr* head = this->table.find(symbolName)->second;
	SymbolAttr* pos = head;
	if (pos->level == this->level) {
		return true;
	}
	return false;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const SymbolTableList& symbolTable)
	{
		for (auto it = (symbolTable.table).begin(); it != symbolTable.table.end(); it++) {
			o << it->first << ": " << endl;
			SymbolAttr* head = it->second;
			SymbolAttr* pos = nullptr;
			for (pos = head; pos != head->prev; pos = pos -> next) {
				o << "   ";
				o << "level: " << pos->level << endl;
			}
		}
		return o;
	}
}