#include "TACVisitor.h"
#include "SymbolTableList.h"

using namespace std;
using namespace saltyfish;

TACVisitor::TACVisitor() {
	this->table = new SymbolTableList();
}

TACVisitor::~TACVisitor() {
	
}

void TACVisitor::visit(CompUnit* compUnit)
{
	vector<unique_ptr<ASTUnit>>& compUnitList = compUnit->compUnitList;
	for (vector<unique_ptr<ASTUnit>>::iterator it = compUnitList.begin(); it < compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
}

void TACVisitor::visit(FuncDecl* funcDecl)
{

}

void TACVisitor::visit(FuncParamDecl* funcParamDecl)
{
}

void TACVisitor::visit(ValueDecl* valueDecl)
{
	auto& type = valueDecl->type;
	auto& valueDefList = valueDecl->valueDefList;
	for (auto& valueDef : valueDefList) {
		auto& ident = valueDef->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr, this->getAlias(), type->type, SymbolAttr::SymbolRole::Value, ident->getArray(), ident->getConst());	//ȷ��const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}
}

void TACVisitor::visit(ValueDef* valueDef)
{
}

/**
* �������ֽ�����ű������¼���Ӧ����λ��
*/
void TACVisitor::visit(FuncDef* funcDef)
{
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	SymbolAttr* symbolAttr = new SymbolAttr(type->type, SymbolAttr::SymbolRole::Function);
	this->table->addSymbol(ident->identStr, symbolAttr);
	vector<unique_ptr<FuncParamDecl>>& funcParamDeclList = funcDef->funcParamDeclList;
	unique_ptr<BlockStmt>& block = funcDef->block;
	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// ȷ��const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}

	block->accept(*this);
}

void TACVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	exp->accept(*this);		//�ȶ�exp�ݹ����
	SymbolAttr* symbolAttr = this->table->getSymbol(ident->identStr);
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, symbolAttr->alias);
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
	TACCode* code = new TACCode(Exp::ExpType::Assign, opn1, result);
	assignStmt->tac = new TAC();
	this->mergeCode(exp->tac->code, code);
	assignStmt->tac->code = exp->tac->code;
	this->displayCode(exp->tac->code);
}

void TACVisitor::visit(BlockStmt* blockStmt)
{
	this->table->inScope();
	vector<unique_ptr<ASTUnit>>& stmts = blockStmt->stmts;
	for (vector<unique_ptr<ASTUnit>>::iterator it = stmts.begin(); it < stmts.end(); it++) {
		(*it)->accept(*this);
	}
	this->table->outScope();
}

void TACVisitor::visit(BreakStmt* breakStmt)
{
}

void TACVisitor::visit(ContinueStmt* continueStmt)
{
}

void TACVisitor::visit(EmptyStmt* emptyStmt)
{
}

void TACVisitor::visit(ExpStmt* expStmt)
{
	auto& exp = expStmt->exp;
	exp->accept(*this);
}

void TACVisitor::visit(IfStmt* ifStmt)
{
	auto& cond = ifStmt->cond;
	auto& ifBody = ifStmt->ifBody;
	cond->tac = new TAC();
	cond->tac->Etrue = this->getLable();
	cond->tac->Efalse = this->getLable();
	this->bitFields.calcBranch = 1;

}

void TACVisitor::visit(ReturnStmt* returnStmt)
{
}

void TACVisitor::visit(WhileStmt* whileStmt)
{
}

void TACVisitor::visit(FuncallExp* funcallExp)
{
}

/**
* �ȵݹ鴦���ӽڵ㣬�ٴ����ڵ�
* �õ������ӽڵ��place������Ӧ����
*/
void TACVisitor::visit(BinaryExp* binaryExp)
{
	auto& Lexp = binaryExp->Lexp;
	auto& Rexp = binaryExp->Rexp;
	// �ȵݹ鴦���ӣ��õ���Ҫ������
	Lexp->accept(*this);
	Rexp->accept(*this);
	TAC* tac = new TAC();
	binaryExp->tac = tac;

	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias);
	TACOpn* opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias);
	SymbolAttr* temp = this->getTemp();
	binaryExp->tac->place = temp;
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
	TACCode* code = new TACCode(binaryExp->expType, opn1, opn2, result);
	this->mergeCode(Lexp->tac->code, Rexp->tac->code);
	this->mergeCode(Lexp->tac->code,code);
	binaryExp->tac->code = Lexp->tac->code;
}

/**
* ���������PrimaryExp���ʽ
* ����Ǳ�ʶ�������ɱ�ʶ�����ֵ�opn�������ýڵ�place��Ϊ��ʶ����symbolAttr
* ��������֣�������ʱ����������������ֵ������ʱ�������ڵ�placeֵΪ��ʱ������symbolAttr
*/
void TACVisitor::visit(PrimaryExp* primaryExp)
{
	TACOpn* opn1 = new TACOpn();
	TACOpn* result = new TACOpn();
	primaryExp->tac = new TAC();
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		opn1->opnType = TACOpn::OpnType::Var;	//��Ҫ��
		opn1->identName = primaryExp->ident->identStr;
		//opn->offset
	}
	else if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::ConstantInt) {
		opn1->opnType = TACOpn::OpnType::Int;
		opn1->intVal = primaryExp->constantInt->value;
	}
	SymbolAttr* temp = this->getTemp();
	result->opnType = TACOpn::OpnType::Var;
	result->identName = temp->alias;
	primaryExp->tac->place = temp;
	TACCode* code = new TACCode(Exp::ExpType::Assign, opn1, result);
	primaryExp->tac->code = code;
}

void TACVisitor::visit(UnaryExp* unaryExp)
{
	unaryExp->tac = new TAC();
	auto& exp = unaryExp->exp;
	exp->accept(*this);
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
	SymbolAttr* temp = this->getTemp();
	unaryExp->tac->place = temp;
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
	TACCode* code = new TACCode(unaryExp->expType, opn1, result);
	this->mergeCode(exp->tac->code, code);
	unaryExp->tac->code = exp->tac->code;
}

void TACVisitor::visit(Type* type)
{
}

void TACVisitor::visit(ConstantInt* constantInt)
{
}

void TACVisitor::visit(Ident* ident)
{
}

string TACVisitor::getAlias() {
	static unsigned index = 0;
	string alias = "_v" + to_string(index);
	index++;
	return alias;
}

SymbolAttr* TACVisitor::getTemp() {
	static unsigned index = 0;
	string name = "_t" + to_string(index);
	index++;
	SymbolAttr* symbolAttr = new SymbolAttr(name, name, Type::IdentType::Int, SymbolAttr::SymbolRole::TempValue);
	return symbolAttr;
}

/**
* ��code2���뵽code1ǰ��
* ע��˳��
*/
void TACVisitor::mergeCode(TACCode* code1, TACCode* code2)
{
	if (code1 == nullptr || code2 == nullptr)
		return;
	code1->prev->next = code2;
	code2->prev->next = code1;
	TACCode* t = code2->prev;
	code2->prev = code1->prev;
	code1->prev = t;
}

void TACVisitor::displayCode(TACCode* code) {
	if (code == nullptr)
		return;
	TACCode* c = code;
	do {
		cout << *c << endl;
		c = c->next;
	} while (c != code);
}

string TACVisitor::getLable() {
	static unsigned index = 0;
	return "_L" + to_string(index);
}