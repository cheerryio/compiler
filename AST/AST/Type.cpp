#include "Type.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

std::map<std::string, Type::IdentType> Type::strTypeMap = {
	{"void",Type::IdentType::Void},
	{"int",Type::IdentType::Int}
};

std::map<Type::IdentType, std::string> Type::typeMap = {
	{Type::IdentType::Void,"void"},
	{Type::IdentType::Int, "int "}
};

Type::Type(IdentType type, location loc)
	:ASTUnit(loc),type(type)
{
	this->unitType = ASTUnit::UnitType::isType;
}

Type::IdentType Type::mapType(std::string& typeStr)
{
	return Type::strTypeMap.at(typeStr);
}

std::string saltyfish::Type::mapTypeStr(const Type& type)
{
	return Type::typeMap.at(type.type);
}



void Type::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const Type& type)
	{
		o << "<";
		o << "Type " << "\'" << Type::mapTypeStr(type) << "\' ";
		cout << "\'" << type.loc << "\'";
		o << ">";
		return o;
	}
}