#include <iomanip>
#include <vector>

#include "TAC.h"

using namespace std;
using namespace saltyfish;

saltyfish::TACOpn::TACOpn()
{

}

saltyfish::TACOpn::TACOpn(OpnType opnType, int intVal)
	:opnType(opnType), intVal(intVal)
{
}

saltyfish::TACOpn::TACOpn(OpnType opnType, string identName)
	: opnType(opnType), identName(identName)
{
}

saltyfish::TACOpn::~TACOpn()
{
}

#define INIT_LIST	\
	this->prev=this;	\
	this->next=this;

saltyfish::TACCode::TACCode(Exp::ExpType op, TACOpn* opn1, TACOpn* result)
	:op(op), opn1(opn1), result(result)
{
	//检验操作符类型
	INIT_LIST;
}

saltyfish::TACCode::TACCode(Exp::ExpType op, TACOpn* opn1, TACOpn* opn2, TACOpn* result)
	: op(op), opn1(opn1), opn2(opn2), result(result)
{
	//检验操作符类型
	INIT_LIST;
}

saltyfish::TACCode::~TACCode()
{
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const TACCode& code) {
		o << "("
			<< setfill(' ')
			<< setw(8) << Exp::ExpTypeMap.at(code.op) << ",";
		TACOpn* opn1 = code.opn1, * opn2 = code.opn2, * result = code.result;
		vector<TACOpn*> opns = { opn1,opn2,result };
		for (TACOpn* opn : opns) {
			if (opn != nullptr)
				if (opn->opnType == TACOpn::OpnType::Int) o << setw(6) << opn->intVal;
				else o << setw(6) << opn->identName;
			else o << setw(6) << "NULL";
			o << ",";
		}

		o << ")";

		return o;
	}
}
