#include "Type.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

std::map<std::string, Type::IdentType> Type::strTypeMap = {
	{"void",Type::IdentType::Void},
	{"int",Type::IdentType::Int}
};


Type::Type() {
		
}

Type::Type(IdentType type, location loc)
	:ASTUnit(loc),type(type)
{

}

Type::IdentType Type::mapType(std::string& typeStr)
{
	return Type::strTypeMap.at(typeStr);
}



void Type::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const Type& type)
	{
		o << "<";
		o << "Type " << "\'" << type.typeStr << "\' ";
		cout << "\'" << type.loc << "\'";
		o << ">";
		return o;
	}
}