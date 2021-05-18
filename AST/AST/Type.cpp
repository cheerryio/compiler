#include "Type.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

std::map<std::string, Type::TypeCode> Type::strTypeMap = {
	{"void",Type::TypeCode::Void},
	{"int",Type::TypeCode::Int}
};

std::map<Type::TypeCode, std::string> Type::typeMap = {
	{Type::TypeCode::Void,"void"},
	{Type::TypeCode::Int, "int "}
};

Type::Type(TypeCode type, location loc)
	:ASTUnit(loc),type(type)
{
	this->unitType = ASTUnit::UnitType::isType;
}

Type::TypeCode Type::mapType(std::string& typeStr)
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