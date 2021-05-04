#include <string>

#include "UnaryExp.h"
#include "Exp.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace saltyfish;

UnaryExp::UnaryExp(UnaryExpType unaryExpType,std::unique_ptr<Exp> exp)
	:exp(std::move(exp))
{

}

void UnaryExp::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}