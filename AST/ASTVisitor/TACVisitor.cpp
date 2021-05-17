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
		SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr, this->getAlias(), type->type, SymbolAttr::SymbolRole::Value, ident->getArray(), ident->getConst());	//确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}
}

void TACVisitor::visit(ValueDef* valueDef)
{
}

/**
* 函数名字进入符号表，额外记录其对应参数位置
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
		SymbolAttr* symbolAttr = new SymbolAttr(type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// 确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);
	}

	block->accept(*this);
}

void TACVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	exp->accept(*this);		//先对exp递归计算
	SymbolAttr* symbolAttr = this->table->getSymbol(ident->identStr);
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, symbolAttr->alias);
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
	TACCode* code = new TACCode(Exp::ExpType::Assign, opn1, result);
	assignStmt->tac = new TAC();
	this->mergeCode(code);
	assignStmt->tac->code = exp->tac->code;
	this->displayCode();
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
* 先递归处理子节点，再处理本节点
* 拿到两个子节点的place，做相应操作
*/
void TACVisitor::visit(BinaryExp* binaryExp)
{
	auto& Lexp = binaryExp->Lexp;
	auto& Rexp = binaryExp->Rexp;
	// 先递归处理孩子，得到需要的数据
	Lexp->accept(*this);
	Rexp->accept(*this);
	TAC* tac = new TAC();
	binaryExp->tac = tac;
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias);
	TACOpn* opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias);

	/**
	* 仅仅是op的二元运算节点，一条tac语句运算即可
	* 需要生成新的临时变量
	*/
	if (binaryExp->isOpExp()) {
		SymbolAttr* temp = this->getTemp();
		binaryExp->tac->place = temp;
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		TACCode* code = new TACCode(binaryExp->expType, opn1, opn2, result);
		this->mergeCode(code);
		binaryExp->tac->code = Lexp->tac->code;
	}
	/**
	* 大于小于 等关系运算符，需要生成并设置truelist,falselist为nextistr,nextistr+1
	* 不需要生成新的临时变量
	*/
	else if (binaryExp->isRelExp()) {
		binaryExp->tac->truelist.push_back(nextinstr);
		binaryExp->tac->falselist.push_back(nextinstr + 1);
	}
	/**
	* 布尔运算符，此处需要回填
	* 不需要新的临时变量
	*/
	else if (binaryExp->isBoolExp()) {
		switch (binaryExp->expType) {
		case(Exp::ExpType::And):
			// 需要false短路

			break;
		case(Exp::ExpType::Or):
			// 需要true短路

			break;
		default:
			
			break;
		}
	}
}

/**
* 对最基本的PrimaryExp表达式
* 如果是标识符，生成标识符名字的opn，并将该节点place置为标识符的symbolAttr
* 如果是数字，生成临时变量，将数字字面值赋予临时变量，节点place值为临时变量的symbolAttr
*/
void TACVisitor::visit(PrimaryExp* primaryExp)
{
	TACOpn* opn1 = new TACOpn();
	TACOpn* result = new TACOpn();
	primaryExp->tac = new TAC();
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		opn1->opnType = TACOpn::OpnType::Var;	//需要改
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
	if (unaryExp->expType == Exp::ExpType::Not) {
		
	}
	else {
		TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
		SymbolAttr* temp = this->getTemp();
		unaryExp->tac->place = temp;
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		TACCode* code = new TACCode(unaryExp->expType, opn1, result);
		this->mergeCode(code);
		unaryExp->tac->code = exp->tac->code;
	}
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
* 将code2插入到code1前面
* 注意顺序
*/
void TACVisitor::mergeCode(TACCode* code)
{
	if (code == nullptr) {
		return;
	}
	this->codes.push_back(code);
	code->instr = this->nextinstr;
	this->nextinstr++;
}

void TACVisitor::mergeCode(vector<TACCode*> codes)
{
	// 正确设置指令位置
	for (int i = 0; i < codes.size(); i++) {
		codes[i]->instr = this->nextinstr + i;
	}
	this->codes.reserve(this->codes.size() + codes.size());
	this->codes.insert(this->codes.end(), this->codes.begin(), this->codes.end());
	this->codes.insert(this->codes.end(), codes.begin(), codes.end());
	nextinstr += codes.size();
}

void TACVisitor::displayCode() {
	for (vector<TACCode*>::iterator it = this->codes.begin(); it != this->codes.end(); it++) {
		cout << **it << endl;
	}
}

string TACVisitor::getLable() {
	static unsigned index = 0;
	return "_L" + to_string(index);
}