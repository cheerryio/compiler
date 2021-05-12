#include <iomanip>
#include <iostream>

#include "SymbolTableList.h"

using namespace std;
using namespace saltyfish;

SymbolTableList::SymbolTableList()
{

}

SymbolTableList::~SymbolTableList()
{

}

SymbolTable::level_t SymbolTableList::getLevel()
{
	return this->level;
}

void SymbolTableList::inScope()
{
	this->level++;
}

void SymbolTableList::outScope() {
	this->delSymbols();
	this->level--;
}

/**
* 加入符号，实现是将新的symbolAttr插入到头节点后面
*/
SymbolAttr* SymbolTableList::addSymbol(std::string symbolName,SymbolAttr* symbolAttr) {
	if (this->dulplicateDeclared(symbolName)) {
		return nullptr;
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
	symbolAttr->prev = head;
	symbolAttr->next = head->next;
	head->next->prev = symbolAttr;
	head->next = symbolAttr;

	return symbolAttr;
}

// 删除层号等于level的所有符号
void SymbolTableList::delSymbols() {
	for (unordered_map<string, SymbolAttr*>::iterator it = this->table.begin(); it != table.end(); it++) {
		SymbolAttr* head = it->second;
		SymbolAttr* pos = head->next;
		if (pos->level == this->level) {
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			delete pos;
		}
	}
}

SymbolAttr* SymbolTableList::getSymbolinLevel(std::string symbolName, level_t level) {
	if (level > this->level)
		return nullptr;
	if (this->table.find(symbolName) == this->table.end())
		return nullptr;
	SymbolAttr* head = this->table.find(symbolName)->second;

	for (SymbolAttr* pos = head->next; pos != head; pos = pos->next) {
		if (pos->level == this->level) {
			return pos;
		}
	}
	return nullptr;
}

SymbolAttr* SymbolTableList::getSymbol(std::string symbolName) {
	if (this->table.find(symbolName) == this->table.end()) {
		return nullptr;
	}
	SymbolAttr* head = this->table.find(symbolName)->second;
	if (head->next != head)
		return head->next;
	return nullptr;
}

bool SymbolTableList::dulplicateDeclared(std::string symbolName) {
	if (this->table.find(symbolName) == this->table.end()) {
		return false;
	}
	SymbolAttr* head = this->table.find(symbolName)->second;
	SymbolAttr* pos = head->next;
	if (pos->level != this->level) {
		return false;
	}
	return true;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const SymbolTableList& symbolTable)
	{
		o << setfill(' ')
			<< endl << endl << endl << endl << endl << endl;

		o << setfill(' ')
			<< setw(16) << "ident"
			<< setw(6) << "|"
			<< setw(6) << "level"
			<< setw(6) << "|"
			<< setw(6) << "type"
			<< setw(6) << "|"
			<< setw(6) << "array"
			<< setw(6) << "|"
			<< setw(6) << "const"
			<< setw(6) << "|"
			<< setw(18) << "role"
			<< setw(6) << "|"
			<< setw(6) << "offset"
			<< setw(6) << "|" << endl;
		for (auto it = (symbolTable.table).begin(); it != symbolTable.table.end(); it++) {
			SymbolAttr* head = it->second;
			SymbolAttr* pos = nullptr;
			for (pos = head->next; pos != head; pos = pos -> next) {
				o << setfill('-') << setw(120) << "" << endl;
				o << setfill(' ')
					<< setw(16) << it->first
					<< setw(6) << "|"
					<< setw(6) << pos->level
					<< setw(6) << "|"
					<< setw(6) << (pos->type == Type::IdentType::Void ? "Void" : "Int")
					<< setw(6) << "|"
					<< setw(6) << (pos->isArray ? "Yes" : "No")
					<< setw(6) << "|"
					<< setw(6) << (pos->isConst ? "Yes" : "No")
					<< setw(6) << "|"
					<< setw(18) << (pos->role == SymbolAttr::SymbolRole::Function ? "Function" : pos->role == SymbolAttr::SymbolRole::FunctionParam ? "FunctionParam" : "Value")
					<< setw(6) << "|"
					<< setw(6) << 15
					<< setw(6) << "|" << endl;
			}
		}
		return o;
	}
}