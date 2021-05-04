#include "ReturnStmt.h"

#include "Exp.h"

using namespace std;
using namespace saltyfish;

ReturnStmt::ReturnStmt()
{

}

ReturnStmt::ReturnStmt(std::unique_ptr<Exp> exp)
	:exp(std::move(exp))
{
	
}

void ReturnStmt::setHasExp(bool b)
{
	bitFields.hasExp = b ? 1 : 0;
}