#include "FuncallExp.h"
#include "../ASTVisitor/ASTVisitor.h"

#include <string>
#include <vector>

#include "Ident.h"
#include "Exp.h"

using namespace std;
using namespace saltyfish;

FuncallExp::FuncallExp(Ident* ident,location loc)
	:ASTUnit(loc), ident(ident)
{
	this->unitType = ASTUnit::UnitType::isFuncallExp;
}

FuncallExp::FuncallExp(Ident* ident, std::vector<Exp*>& funcallParamList,location loc)
	:ASTUnit(loc), ident(ident), funcallParamList(funcallParamList)
{
	this->unitType = ASTUnit::UnitType::isFuncallExp;
}

bool FuncallExp::isConstExp()
{
	return false;
}

void FuncallExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}