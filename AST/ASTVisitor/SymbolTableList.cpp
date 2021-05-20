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
	this->offsetStack.push_back(this->offset);
	this->offset = 0;
}

void SymbolTableList::outScope() {
	if (this->level == 1) {
		if (this->functionSymbol != nullptr) {
			functionSymbol->offset = this->offset;
		}
	}
	// cout << (*this) << endl;

	this->delSymbols();
	this->level--;
	this->offset = this->offsetStack.back();
	this->offsetStack.pop_back();
}

/**
* 加入符号，实现是将新的symbolAttr插入到头节点后面
*/
SymbolAttr* SymbolTableList::addSymbol(std::string symbolName, SymbolAttr* symbolAttr)
{
	if (this->dulplicateDeclared(symbolName)) {
		return nullptr;
	}
	// 记录最近的一次function符号
	if (symbolAttr->role == SymbolAttr::SymbolRole::Function) {
		this->functionSymbol = symbolAttr;
		symbolAttr->level = this->level;
	}
	else if (symbolAttr->role == SymbolAttr::SymbolRole::FunctionParam) {
		paramOffset = paramOffset == -1 ? 0 : paramOffset;
		symbolAttr->offset = this->paramOffset;
		symbolAttr->width = 4;
		paramOffset += symbolAttr->width;
	}
	else {
		if (this->paramOffset != -1) {
			this->offset = this->paramOffset;
			this->paramOffset = -1;
		}
		symbolAttr->offset = this->offset;
		symbolAttr->width = 4;	// 查type得到宽度
		this->offset = symbolAttr->offset + symbolAttr->width;
		symbolAttr->level = this->level;
	}

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
			<< endl << endl
			<< "Level: " << symbolTable.level
			<< endl << endl << endl << endl;

		o << setfill(' ')
			<< setw(6) << "ident"
			<< setw(3) << "|"
			<< setw(6) << "alias"
			<< setw(3) << "|"
			<< setw(6) << "level"
			<< setw(3) << "|"
			<< setw(6) << "type"
			<< setw(3) << "|"
			<< setw(6) << "array"
			<< setw(3) << "|"
			<< setw(6) << "const"
			<< setw(3) << "|"
			<< setw(18) << "role"
			<< setw(3) << "|"
			<< setw(6) << "offset"
			<< setw(3) << "|"
			<< setw(6) << "width"
			<< setw(3) << "|"
			<< endl;
		for (auto it = (symbolTable.table).begin(); it != symbolTable.table.end(); it++) {
			SymbolAttr* head = it->second;
			SymbolAttr* pos = nullptr;
			for (pos = head->next; pos != head; pos = pos -> next) {
				o << setfill('-') << setw(120) << "" << endl;
				o << setfill(' ')
					<< setw(6) << it->first
					<< setw(3) << "|"
					<< setw(6) << pos->alias
					<< setw(3) << "|"
					<< setw(6) << pos->level
					<< setw(3) << "|"
					<< setw(6) << (pos->type == Type::TypeCode::Void ? "Void" : "Int")
					<< setw(3) << "|"
					<< setw(6) << (pos->isArray ? "Yes" : "No")
					<< setw(3) << "|"
					<< setw(6) << (pos->isConst ? "Yes" : "No")
					<< setw(3) << "|"
					<< setw(18) << (pos->role == SymbolAttr::SymbolRole::Function ? "Function" : pos->role == SymbolAttr::SymbolRole::FunctionParam ? "FunctionParam" : "Value")
					<< setw(3) << "|"
					<< setw(6) << pos->offset
					<< setw(3) << "|"
					<< setw(6) << pos->width
					<< setw(3) << "|" << endl;
			}
		}
		return o;
	}
}