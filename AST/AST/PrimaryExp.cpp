#include "Exp.h"
#include "PrimaryExp.h"


using namespace saltyfish;
PrimaryExp::PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Ident> ident)
	:primaryExpType(primaryExpType),ident(std::move(ident))
{

}

PrimaryExp::PrimaryExp(PrimaryExpType primaryExpType, std::unique_ptr<saltyfish::Constant> constant)
	: primaryExpType(primaryExpType), constant(std::move(constant))
{

}

PrimaryExp::~PrimaryExp()
{
	
}