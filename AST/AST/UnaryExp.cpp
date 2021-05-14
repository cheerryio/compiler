#include <string>

#include "UnaryExp.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

UnaryExp::UnaryExp(Exp::ExpType expType, std::unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc), exp(std::move(exp))
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isUnaryExp;
}

bool UnaryExp::isConstExp() const
{
	return exp->isConstExp();
}

void UnaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish{
	std::ostream& operator<<(std::ostream& o, const UnaryExp& unaryExp)
	{
		o << "<";
		o << "UnaryExp " << "\'" << Exp::ExpTypeMap.at(unaryExp.expType) << "\' ";
		o << "\'" << unaryExp.loc << "\' ";
		o << "\'" << "isConst: " << (unaryExp.isConstExp() ? "Yes" : "No") << "\'";
		o << ">";
		return o;
	}
}
