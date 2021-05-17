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

void BinaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

#define ISTYPE(TYPE) this->expType == Exp::ExpType::TYPE

bool BinaryExp::isOpExp()
{
	if (ISTYPE(Add) || ISTYPE(Sub) || ISTYPE(Mul) || ISTYPE(Div) || ISTYPE(Mod)) {
		return true;
	}
	return false;
}

bool saltyfish::BinaryExp::isRelExp()
{
	if (ISTYPE(B) || ISTYPE(A) || ISTYPE(Be) || ISTYPE(Ae) || ISTYPE(E) || ISTYPE(Ne)) {
		return true;
	}
	return false;
}

bool saltyfish::BinaryExp::isBoolExp()
{
	if (ISTYPE(And) || ISTYPE(Or)) {
		return true;
	}
	return false;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const BinaryExp& binaryExp)
	{
		o << "<";
		o << "BinaryExp \'" << Exp::ExpTypeMap.at(binaryExp.expType) << "\' ";
		o << "\'" << binaryExp.loc << "\' ";
		o << ">";
		return o;
	}
}
