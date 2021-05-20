#include "Exp.h"
#include "PrimaryExp.h"
#include "ASTUnit.h"
#include "../ASTVisitor/ASTVisitor.h"
#include "Ident.h"

using namespace saltyfish;
using namespace std;

PrimaryExp::PrimaryExp(saltyfish::Ident* ident,location loc)
	:ASTUnit(loc), ident(ident)
{
	this->unitType = ASTUnit::UnitType::isPrimaryExp;
	this->childType = ASTUnit::UnitType::isIdent;
}

PrimaryExp::PrimaryExp(saltyfish::ConstantInt* constantInt,location loc)
	:ASTUnit(loc), constantInt(constantInt)
{
	this->unitType = ASTUnit::UnitType::isPrimaryExp;
	this->childType = ASTUnit::UnitType::isConstantInt;
}

PrimaryExp::~PrimaryExp()
{
	
}

void PrimaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

bool PrimaryExp::isConstExp()
{
	if (this->childType==ASTUnit::UnitType::isIdent) {
		if (this->ident == nullptr)
			return false;
		return this->ident->bitFields.isConst;
	}
	else if(this->childType==ASTUnit::UnitType::isConstantInt) {
		if (this->constantInt == nullptr)
			return false;
	}
	return true;
}

bool PrimaryExp::equals(PrimaryExp* primaryExp)
{
	bool r = false;
	if (this->childType == primaryExp->childType) {
		switch (this->childType) {
		case(ASTUnit::UnitType::isIdent):
			r=this->ident->identStr == primaryExp->ident->identStr;
			break;
		case(ASTUnit::UnitType::isConstantInt):
			r=this->constantInt->value == primaryExp->constantInt->value;
			break;
		default:
			break;
		}
		return r;
	}
	return false;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const PrimaryExp& primaryExp)
	{
		o << "<";
		o << "PrimaryExp ";
		o << "\'" << primaryExp.loc << "\'";
		o << ">";
		return o;
	}
}