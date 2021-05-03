#include "BinaryExp.h"

using namespace saltyfish;
using namespace std;

BinaryExp::BinaryExp() {}

BinaryExp::BinaryExp(BinaryExp::BinaryExpType binaryExpType, unique_ptr<Exp> Lexp, unique_ptr<Exp> Rexp)
	:binaryExpType(binaryExpType), Lexp(std::move(Lexp)), Rexp(std::move(Rexp))
{
	
}

BinaryExp::BinaryExp(BinaryExpType binaryExpType, unique_ptr<Exp> Lexp, unique_ptr<Exp> Rexp, std::string opStr)
	:binaryExpType(binaryExpType),Lexp(std::move(Lexp)),Rexp(std::move(Rexp))
{

}