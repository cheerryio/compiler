#include <string>

#include "UnaryExp.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;
using namespace std;

std::map<UnaryExp::UnaryExpType, std::string> UnaryExp::unaryExpTypeMap = {
	{UnaryExp::UnaryExpType::Add,"Add +"},
	{UnaryExp::UnaryExpType::Sub,"Sub -"},
	{UnaryExp::UnaryExpType::Not,"Not !"}
};

UnaryExp::UnaryExp(UnaryExpType unaryExpType, std::unique_ptr<Exp> exp,location loc)
	:ASTUnit(loc), exp(std::move(exp))
{
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
		o << "UnaryExp " << "\'" << UnaryExp::unaryExpTypeMap.at(unaryExp.unaryExpType) << "\' ";
		o << "\'" << unaryExp.loc << "\' ";
		o << "\'" << "isConst: " << (unaryExp.isConstExp() ? "Yes" : "No") << "\'";
		o << ">";
		return o;
	}
}
