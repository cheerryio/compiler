#include <iomanip>
#include <vector>

#include "TAC.h"

using namespace std;
using namespace saltyfish;

std::map<TACCode::OpCode, std::string> TACCode::OpCodeMap = {
	{TACCode::OpCode::Add,"Add +"},
	{TACCode::OpCode::Sub,"Sub -"},
	{TACCode::OpCode::Div,"Div *"},
	{TACCode::OpCode::Mul,"Mul *"},
	{TACCode::OpCode::Mod,"Mod %"},
	{TACCode::OpCode::JGT,"JGT >"},
	{TACCode::OpCode::JGE,"JGE >="},
	{TACCode::OpCode::JLT,"JLT <"},
	{TACCode::OpCode::JLE,"JLE <="},
	{TACCode::OpCode::JE,"JE =="},
	{TACCode::OpCode::JNE,"!="},
	{TACCode::OpCode::UAdd,"UAdd +"},
	{TACCode::OpCode::USub,"USub -"},
	{TACCode::OpCode::GOTO,"GOTO"},
	{TACCode::OpCode::Assign,"Assign ="},
	{TACCode::OpCode::Imm,"Imm"},
	{TACCode::OpCode::Var,"Var"},
	{TACCode::OpCode::Param,"Param"},
	{TACCode::OpCode::Call,"Call"},
	{TACCode::OpCode::Arg,"Arg"},
	{TACCode::OpCode::Return,"Return"},
	{TACCode::OpCode::Function,"Function"}
};


TACOpn::TACOpn()
	:opnType(TACOpn::OpnType::Var)
{

}

TACOpn::TACOpn(OpnType opnType)
	:opnType(opnType)
{
}

TACOpn::TACOpn(OpnType opnType, int intVal)
	:opnType(opnType), intVal(intVal)
{
}

TACOpn::TACOpn(OpnType opnType, string identName, NameAttr* nameAttr)
	: opnType(opnType), identName(identName), nameAttr(nameAttr)
{
}

TACOpn::~TACOpn()
{
}

TACCode::TACCode(TACCode::OpCode op, TACOpn* opn1, TACOpn* opn2, TACOpn* result)
	: op(op), opn1(opn1), opn2(opn2), result(result) {}

TACCode::~TACCode()
{
}

bool TACCode::isBinaryOpCode()
{
	return this->op >= TACCode::OpCode::Add && this->op <= TACCode::OpCode::JNE;
}

bool TACCode::isAssignCode()
{
	return this->op == TACCode::OpCode::Assign;
}

namespace saltyfish {
	std::ostream& operator<<(std::ostream& o, const TACOpn& opn) {
		switch (opn.opnType) {
		case(TACOpn::OpnType::Int):
			o << opn.intVal;
			break;
		case(TACOpn::OpnType::Var):
			o << opn.identName;
			break;
		case(TACOpn::OpnType::J):
			o << opn.labelInstr;
			break;
		default:
			break;
		}
		return o;
	}

	std::ostream& operator<<(std::ostream& o, const TACCode& code) {
		o << setw(5) << code.instr << "  ";
		o << "("
			<< setfill(' ')
			<< setw(8) << TACCode::OpCodeMap.at(code.op) << ",";
		TACOpn* opn1 = code.opn1, * opn2 = code.opn2, * result = code.result;
		vector<TACOpn*> opns = { opn1,opn2,result };
		for (TACOpn* opn : opns) {
			if (opn != nullptr)
				o << setw(6) << *opn;
			else o << setw(6) << "NULL";
			o << ",";
		}
		o << ")";
		for (TACOpn* opn : opns) {
			if (opn != nullptr && opn->opnType == TACOpn::OpnType::Var)
				o << "  " << opn->nameAttr->active.first << "  ";
		}
		return o;
	}
}
