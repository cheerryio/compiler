#include "BinaryExp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

BinaryExp::BinaryExp() {}

BinaryExp::BinaryExp(Exp::ExpType expType, Exp* Lexp, Exp* Rexp)
	:Lexp(Lexp), Rexp(Rexp)
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isBinaryExp;
}

BinaryExp::BinaryExp(Exp::ExpType expType, Exp* Lexp, Exp* Rexp,location loc)
	:ASTUnit(loc), Lexp(Lexp), Rexp(Rexp)
{
	this->expType = expType;
	this->unitType = ASTUnit::UnitType::isBinaryExp;
}

void BinaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

bool BinaryExp::isConstExp()
{
	return this->Lexp->isConstExp() && this->Rexp->isConstExp();
}

bool BinaryExp::equals(BinaryExp* binaryExp)
{
	Exp* Lexp1 = this->Lexp;
	Exp* Lexp2 = binaryExp->Lexp;
	Exp* Rexp1 = this->Rexp;
	Exp* Rexp2 = binaryExp->Rexp;
	if (Lexp1->isSameUnitType(Lexp2) && Rexp1->isSameUnitType(Rexp2)) {
		return Lexp1->equals(Lexp2) && Rexp1->equals(Rexp2);
	}
	return false;
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
	if (ISTYPE(L) || ISTYPE(G) || ISTYPE(Le) || ISTYPE(Ge) || ISTYPE(E) || ISTYPE(Ne)) {
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

PrimaryExp* BinaryExp::reduce()
{
	return nullptr;
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
