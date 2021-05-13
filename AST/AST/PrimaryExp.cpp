#include "Exp.h"
#include "PrimaryExp.h"
#include "../ASTVisitor/ASTVisitor.h"
#include "Ident.h"
#include "SymbolTable.h"

using namespace saltyfish;
using namespace std;

std::map<PrimaryExp::PrimaryExpType, std::string> PrimaryExp::primaryExpTypeMap = {
	{PrimaryExp::PrimaryExpType::Ident,		 "ident"},
	{PrimaryExp::PrimaryExpType::ConstantInt,"constantInt"}
};

PrimaryExp::PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Ident> ident,location loc)
	:ASTUnit(loc), primaryExpType(primaryExpType), ident(std::move(ident))
{
	this->unitType = ASTUnit::UnitType::isPrimaryExp;
}

PrimaryExp::PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::ConstantInt> constantInt,location loc)
	:ASTUnit(loc), primaryExpType(primaryExpType), constantInt(std::move(constantInt))
{
	this->unitType = ASTUnit::UnitType::isPrimaryExp;
}

PrimaryExp::~PrimaryExp()
{
	
}

bool PrimaryExp::isConstExp() const
{
	return primaryExpType == PrimaryExp::PrimaryExpType::Ident ? (ident->symbolAttr == nullptr ? false : ident->symbolAttr->isConst) : true;
}

void PrimaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const PrimaryExp& primaryExp)
	{
		o << "<";
		o << "PrimaryExp " << "\'" << PrimaryExp::primaryExpTypeMap.at(primaryExp.primaryExpType) << "\' ";
		o << "\'" << primaryExp.loc << "\'";
		o << "\'" << "isConst: " << (primaryExp.isConstExp() ? "Yes" : "No") << "\'";
		o << ">";
		return o;
	}
}