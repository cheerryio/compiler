#include "FuncParamDecl.h"
#include "Type.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

FuncParamDecl::FuncParamDecl(Type* type, Ident* ident,location loc)
	:ASTUnit(loc), type(type), ident(ident)
{
	this->unitType = ASTUnit::UnitType::isFuncParamDecl;
}

void FuncParamDecl::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const FuncParamDecl& funcParamDecl)
	{
		o << "<";
		o << "FuncParamDecl";
		o << ">";
		return o;
	}
}
