#include <string>

#include "UnaryExp.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

UnaryExp::UnaryExp(Exp::ExpType expType, Exp* exp,location loc)
	:ASTUnit(loc), exp(exp)
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isUnaryExp;
}

void UnaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

bool UnaryExp::isConstExp()
{
	return exp->isConstExp();
}

bool UnaryExp::equals(UnaryExp* unaryExp)
{
	if (this->expType == unaryExp->expType) {
		return this->exp->equals(unaryExp);
	}
	return false;
}

namespace saltyfish{
	std::ostream& operator<<(std::ostream& o, const UnaryExp& unaryExp)
	{
		o << "<";
		o << "UnaryExp " << "\'" << Exp::ExpTypeMap.at(unaryExp.expType) << "\' ";
		o << "\'" << unaryExp.loc << "\' ";
		o << ">";
		return o;
	}
}
