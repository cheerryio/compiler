#include <string>

#include "Ident.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

Ident::Ident(string identName,location loc) 
	:ASTUnit(loc),name(identName) 
{
	this->unitType = ASTUnit::UnitType::isIdent;
}

void Ident::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

void Ident::setConst() {
	this->bitFields.isConst = 1;
}

void Ident::setArray() {
	this->bitFields.isArray = 1;
}

bool Ident::getConst() const {
	return this->bitFields.isConst;
}

bool Ident::getArray() const {
	return this->bitFields.isArray;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const Ident& ident)
	{
		o << "<";
		o << "Ident " << "\'" << ident.name << "\' ";
		o << "isConst: " << (ident.getConst() ? "Yes" : "No") << "\' ";
		o << "\'" << ident.loc << "\'";
		cout << ">";
		return o;
	}
}
