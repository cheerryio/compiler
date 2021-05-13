#include "TACBuilder.h"

using namespace std;
using namespace saltyfish;

SymbolAttr* TACBuilder::newTemp()
{
	string name = "t" + to_string(this->tempIndex);
	SymbolAttr* symbolAttr = new SymbolAttr(name, name, SymbolAttr::SymbolRole::TempValue);
	return symbolAttr;
}

TACCode* TACBuilder::codeGen(Exp* exp) {
	
}

TACOpn* TACBuilder::getOpn(Exp* exp) {
	
}

TACOpn* TACBuilder::getOpn(PrimaryExp* primaryExp) {
	TACOpn* opn = new TACOpn();
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		opn->opnType = TACOpn::OpnType::Var;	//��Ҫ��
		opn->identName = primaryExp->ident->identStr;
		//opn->offset
	}
	else if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::ConstantInt) {
		opn->opnType = TACOpn::OpnType::Int;
		opn->intVal = primaryExp->constantInt->value;
	}

	return opn;
}

TACOpn* TACBuilder::getOpn(BinaryExp* binaryExp) {
	TACOpn* result = new TACOpn();
	auto& Lexp = binaryExp->Lexp;
	auto& Rexp = binaryExp->Rexp;
	TAC* LTac = Lexp->tac;
	TAC* RTac = Rexp->tac;
	if (LTac == nullptr || RTac == nullptr) {
		//Ӧ���и��ദ��
		return nullptr;
	}
	return result;
}


