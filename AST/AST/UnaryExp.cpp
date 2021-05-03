#include "UnaryExp.h"
#include <string>
#include "Exp.h"

using namespace saltyfish;

UnaryExp::UnaryExp(UnaryExpType unaryExpType,std::unique_ptr<Exp> exp)
	:exp(std::move(exp))
{

}