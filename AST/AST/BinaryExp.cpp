#include "BinaryExp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

BinaryExp::BinaryExp() {}

BinaryExp::BinaryExp(Exp::ExpType expType, unique_ptr<Exp> Lexp, unique_ptr<Exp> Rexp)
	:Lexp(std::move(Lexp)), Rexp(std::move(Rexp))
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isBinaryExp;
}

BinaryExp::BinaryExp(Exp::ExpType expType, unique_ptr<Exp> Lexp, unique_ptr<Exp> Rexp,location loc)
	:ASTUnit(loc), Lexp(std::move(Lexp)), Rexp(std::move(Rexp))
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isBinaryExp;
}

bool BinaryExp::isConstExp() const
{
	return Lexp->isConstExp() && Rexp->isConstExp();
}

void BinaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const BinaryExp& binaryExp)
	{
		o << "<";
		o << "BinaryExp \'" << Exp::ExpTypeMap.at(binaryExp.expType) << "\' ";
		o << "\'" << "isConst: " << (binaryExp.isConstExp() ? "Yes" : "No") << "\'";
		o << "\'" << binaryExp.loc << "\' ";
		o << ">";
		return o;
	}
}
