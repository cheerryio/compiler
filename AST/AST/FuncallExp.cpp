#include "FuncallExp.h"
#include "../ASTVisitor/ASTVisitor.h"

#include <string>
#include <vector>

#include "Ident.h"
#include "Exp.h"

using namespace std;
using namespace saltyfish;

FuncallExp::FuncallExp(std::unique_ptr<Ident> ident,location loc)
	:ASTUnit(loc), ident(std::move(ident))
{
	this->unitType = ASTUnit::UnitType::isFuncallExp;
}

FuncallExp::FuncallExp(std::unique_ptr<Ident> ident, std::vector<std::unique_ptr<Exp>> funcallParamList,location loc)
	:ASTUnit(loc), ident(std::move(ident)), funcallParamList(std::move(funcallParamList))
{
	this->unitType = ASTUnit::UnitType::isFuncallExp;
}

bool saltyfish::FuncallExp::isConstExp() const
{
	return false;
}

void FuncallExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}