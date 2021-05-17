#include "TACVisitor.h"
#include "SymbolTableList.h"

using namespace std;
using namespace saltyfish;

map<Exp::ExpType, TACCode::OpCode> TACVisitor::expTypeMapOpCode = {
	{Exp::ExpType::Add,TACCode::OpCode::Add},
	{Exp::ExpType::Sub,TACCode::OpCode::Sub},
	{Exp::ExpType::Mul,TACCode::OpCode::Mul},
	{Exp::ExpType::Div,TACCode::OpCode::Div},
	{Exp::ExpType::Mod,TACCode::OpCode::Mod},
	{Exp::ExpType::UnaryAdd,TACCode::OpCode::UAdd},
	{Exp::ExpType::UnarySub,TACCode::OpCode::USub},
	{Exp::ExpType::Mod,TACCode::OpCode::Mod},
	{Exp::ExpType::L,TACCode::OpCode::JLT},
	{Exp::ExpType::Le,TACCode::OpCode::JLE},
	{Exp::ExpType::G,TACCode::OpCode::JGT},
	{Exp::ExpType::Ge,TACCode::OpCode::JGE},
	{Exp::ExpType::E,TACCode::OpCode::JE},
	{Exp::ExpType::Ne,TACCode::OpCode::JNE},
};

TACVisitor::TACVisitor() {
	this->table = new SymbolTableList();
}

TACVisitor::~TACVisitor() {
	
}

void TACVisitor::visit(CompUnit* compUnit)
{
	vector<unique_ptr<ASTUnit>>& compUnitList = compUnit->compUnitList;
	for (vector<unique_ptr<ASTUnit>>::iterator it = compUnitList.begin(); it != compUnitList.end(); it++) {
		(*it)->accept(*this);
	}
	this->displayCode();
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

		valueDef->accept(*this);
	}
}

void TACVisitor::visit(ValueDef* valueDef)
{
	valueDef->tac = new TAC();
	TACOpn* opn = nullptr;
	TACOpn* result = nullptr;
	if (valueDef->bitFields.hasAssign) {
		auto& exp = valueDef->exp;
		exp->accept(*this);
		SymbolAttr* symbolAttr = this->table->getSymbol(valueDef->ident->identStr);
		opn = new TACOpn();
		result = new TACOpn();
		result->identName = symbolAttr->alias;
		opn->identName = exp->tac->place->alias;
		TACCode* code = new TACCode(TACCode::OpCode::Assign, opn, result);
		this->mergeCode(code);
	}
}

/**
* 函数名字进入符号表，额外记录其对应参数位置
*/
void TACVisitor::visit(FuncDef* funcDef)
{
	// 处理符号表
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr,this->getAlias(),type->type, SymbolAttr::SymbolRole::Function);
	this->table->addSymbol(ident->identStr, symbolAttr);
	vector<unique_ptr<FuncParamDecl>>& funcParamDeclList = funcDef->funcParamDeclList;
	unique_ptr<BlockStmt>& block = funcDef->block;

	// 生成中间代码
	TACCode* code = nullptr;
	TACOpn* result = nullptr;
	result = new TACOpn();
	result->identName = symbolAttr->name;
	code = new TACCode(TACCode::OpCode::Function, nullptr, nullptr, result);
	this->mergeCode(code);

	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		// 符号表
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr, this->getAlias(), type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// 确认const array
		this->table->addSymbol(ident->identStr, symbolAttr);

		// 中间代码
		result->identName = symbolAttr->name;
		code = new TACCode(TACCode::OpCode::Param, nullptr, nullptr, result);
		this->mergeCode(code);
	}
	block->accept(*this);
}

void TACVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	assignStmt->tac = new TAC();
	exp->accept(*this);		//先对exp递归计算
	SymbolAttr* symbolAttr = this->table->getSymbol(ident->identStr);
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, symbolAttr->alias);
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
	TACCode* code = new TACCode(TACCode::OpCode::Assign, opn1, result);
	assignStmt->tac = new TAC();
	this->mergeCode(code);
	assignStmt->tac->code = exp->tac->code;
}

void TACVisitor::visit(BlockStmt* blockStmt)
{
	this->table->inScope();
	blockStmt->tac = new TAC();
	vector<unique_ptr<ASTUnit>>& stmts = blockStmt->stmts;
	TACCode* code = nullptr;
	TACOpn* result = nullptr;
	for (vector<unique_ptr<ASTUnit>>::iterator it = stmts.begin(); it < stmts.end(); it++) {
			(*it)->accept(*this);
			if ((*it)->tac != nullptr) {
				this->backpatch((*it)->tac->nextlist, nextinstr);
			}
	}
	this->table->outScope();
}

void TACVisitor::visit(BreakStmt* breakStmt)
{
	this->breaklist.push_back(this->nextinstr);
	TACOpn* result = new TACOpn();
	result->opnType = TACOpn::OpnType::J;
	TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
	this->mergeCode(code);
}

void TACVisitor::visit(ContinueStmt* continueStmt)
{
	this->continuelist.push_back(this->nextinstr);
	TACOpn* result = new TACOpn();
	result->opnType = TACOpn::OpnType::J;
	TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
	this->mergeCode(code);
}

void TACVisitor::visit(EmptyStmt* emptyStmt)
{
}

void TACVisitor::visit(ExpStmt* expStmt)
{
	expStmt->tac = new TAC();
	auto& exp = expStmt->exp;
	exp->accept(*this);
}

void TACVisitor::visit(IfStmt* ifStmt)
{
	auto& cond = ifStmt->cond;
	auto& ifBody = ifStmt->ifBody;
	ifStmt->tac = new TAC();
	if (!ifStmt->bitFields.hasElse) {
		cond->accept(*this);
		this->backpatch(cond->tac->truelist, nextinstr);
		ifBody->accept(*this);
		this->mergeList(cond->tac->falselist, ifBody->tac->nextlist);
	}
	else {
		auto& elseBody = ifStmt->elseBody;
		cond->accept(*this);
		this->backpatch(cond->tac->truelist, nextinstr);
		ifBody->accept(*this);
		ifStmt->tac->nextlist.push_back(nextinstr);
		TACOpn* result = new TACOpn();
		result->opnType = TACOpn::OpnType::J;
		TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
		this->mergeCode(code);
		this->backpatch(cond->tac->falselist, nextinstr);
		elseBody->accept(*this);
		ifStmt->tac->nextlist = this->mergeList(ifStmt->tac->nextlist, ifBody->tac->nextlist, elseBody->tac->nextlist);
	}
}

void TACVisitor::visit(ReturnStmt* returnStmt)
{
	returnStmt->tac = new TAC();
	TACCode* code = nullptr;
	if (returnStmt->bitFields.hasExp) {
		auto& exp = returnStmt->exp;
		exp->accept(*this);
		TACOpn* result = new TACOpn();
		result->identName = exp->tac->place->alias;
		code = new TACCode(TACCode::OpCode::Return, nullptr, nullptr, result);
	}
	else {
		code = new TACCode(TACCode::OpCode::Return, nullptr, nullptr, nullptr);
	}
	this->mergeCode(code);
}

void TACVisitor::visit(WhileStmt* whileStmt)
{
	whileStmt->tac = new TAC();
	auto& cond = whileStmt->cond;
	auto& body = whileStmt->body;
	unsigned M1_instr = nextinstr;
	cond->accept(*this);
	unsigned M2_instr = nextinstr;
	body->accept(*this);
	this->backpatch(body->tac->nextlist, M1_instr);
	this->backpatch(this->continuelist, M1_instr);
	this->backpatch(cond->tac->truelist, M2_instr);
	whileStmt->tac->nextlist = this->mergeList(whileStmt->tac->nextlist, this->breaklist, cond->tac->falselist);
	this->continuelist.clear();
	this->breaklist.clear();
	TACOpn* result = new TACOpn();
	result->opnType = TACOpn::OpnType::J;
	result->labelInstr = M1_instr;
	TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
	this->mergeCode(code);
}

void TACVisitor::visit(FuncallExp* funcallExp)
{
	funcallExp->tac = new TAC();
	auto& ident = funcallExp->ident;
	auto& params = funcallExp->funcallParamList;
	vector<TACCode*> paramCodes;
	TACCode* code = nullptr;
	TACOpn* opn = nullptr;
	TACOpn* result = nullptr;
	ident->accept(*this);
	for (auto& param : params) {
		param->accept(*this);
		result = new TACOpn();
		result->identName = param->tac->place->alias;
		code = new TACCode(TACCode::OpCode::Arg, nullptr, nullptr, result);
		paramCodes.push_back(code);
	}
	this->mergeCode(paramCodes);
	SymbolAttr* symbolAttr = this->table->getSymbol(ident->identStr);
	opn = new TACOpn();
	result = new TACOpn();
	opn->identName = symbolAttr->name;
	SymbolAttr* temp = this->getTemp();
	result->identName = temp->alias;
	funcallExp->tac->place = temp;
	code = new TACCode(TACCode::OpCode::Call, opn, result);
	this->mergeCode(code);
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
	TAC* tac = new TAC();
	binaryExp->tac = tac;
	TACOpn* opn1 = nullptr;
	TACOpn* opn2 = nullptr;

	/**
	* 仅仅是op的二元运算节点，一条tac语句运算即可
	* 需要生成新的临时变量
	*/
	if (binaryExp->isOpExp()) {
		Lexp->accept(*this);
		Rexp->accept(*this);
		opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias);
		opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias);
		SymbolAttr* temp = this->getTemp();
		binaryExp->tac->place = temp;
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		TACCode* code = new TACCode(expTypeMapOpCode.at(binaryExp->expType), opn1, opn2, result);
		this->mergeCode(code);
		binaryExp->tac->code = Lexp->tac->code;
	}
	/**
	* 大于小于 等关系运算符，需要生成并设置truelist,falselist为nextistr,nextistr+1
	* 不需要生成新的临时变量
	*/
	else if (binaryExp->isRelExp()) {
		Lexp->accept(*this);
		Rexp->accept(*this);
		opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias);
		opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias);
		binaryExp->tac->truelist.push_back(nextinstr);
		binaryExp->tac->falselist.push_back(nextinstr + 1);
		TACOpn* trueResult = new TACOpn();
		TACOpn* falseResult = new TACOpn();
		trueResult->opnType = TACOpn::OpnType::J;
		falseResult->opnType = TACOpn::OpnType::J;
		TACCode* code1 = new TACCode(expTypeMapOpCode.at(binaryExp->expType), opn1, opn2, trueResult);
		TACCode* code2 = new TACCode(TACCode::OpCode::GOTO, NULL, NULL, falseResult);
		this->mergeCode(code1);
		this->mergeCode(code2);
	}
	/**
	* 布尔运算符，此处需要回填
	* 不需要新的临时变量
	*/
	else if (binaryExp->isBoolExp()) {
		switch (binaryExp->expType) {
		case(Exp::ExpType::And):
			// 需要false短路
			// B -> B1 && M B2 生成B1代码后，nextinstr就是M的代码位置
			Lexp->accept(*this);
			this->backpatch(Lexp->tac->truelist, nextinstr);
			Rexp->accept(*this);
			binaryExp->tac->truelist = Rexp->tac->truelist;
			binaryExp->tac->falselist = this->mergeList(Lexp->tac->falselist, Rexp->tac->falselist);
			break;
		case(Exp::ExpType::Or):
			// 需要true短路
			Lexp->accept(*this);
			this->backpatch(Lexp->tac->falselist, nextinstr);
			Rexp->accept(*this);
			binaryExp->tac->truelist = this->mergeList(Lexp->tac->truelist, Rexp->tac->truelist);
			binaryExp->tac->falselist = Rexp->tac->falselist;
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
	primaryExp->tac = new TAC();
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		SymbolAttr* symbolAttr = this->table->getSymbol(primaryExp->ident->identStr);
		primaryExp->tac->place = symbolAttr;
		//opn->offset
	}
	else if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::ConstantInt) {
		TACOpn* opn1 = new TACOpn();
		TACOpn* result = new TACOpn();
		result->opnType = TACOpn::OpnType::Var;
		opn1->opnType = TACOpn::OpnType::Int;
		SymbolAttr* temp = this->getTemp();
		result->identName = temp->alias;
		opn1->intVal = primaryExp->constantInt->value;
		primaryExp->tac->place = temp;
		TACCode* code = new TACCode(TACCode::OpCode::Assign, opn1, result);
		this->mergeCode(code);
	}
}

void TACVisitor::visit(UnaryExp* unaryExp)
{
	unaryExp->tac = new TAC();
	auto& exp = unaryExp->exp;
	exp->accept(*this);
	if (unaryExp->expType == Exp::ExpType::Not) {
		vector<int> t = unaryExp->tac->truelist;
		unaryExp->tac->truelist = unaryExp->tac->falselist;
		unaryExp->tac->falselist = t;
	}
	else {
		TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
		TACOpn* result = new TACOpn();
		result->opnType = TACOpn::OpnType::Var;
		SymbolAttr* temp = this->getTemp();
		opn1->identName = temp->alias;
		result->identName = temp->alias;
		unaryExp->tac->place = temp;
		TACCode* code = new TACCode(expTypeMapOpCode.at(unaryExp->expType), opn1, result);
		this->mergeCode(code);
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
	ident->tac = new TAC();
	ident->tac->place = this->table->getSymbol(ident->identStr);
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
	this->codes.insert(this->codes.end(), codes.begin(), codes.end());
	nextinstr += codes.size();
}

vector<int> TACVisitor::mergeList(vector<int>& a, vector<int>& b)
{
	if (a.size() + b.size() == 0) {
		return vector<int>();
	}
	vector<int> newList;
	newList.reserve(a.size() + b.size());
	newList.insert(newList.end(), a.begin(), a.end());
	newList.insert(newList.end(), b.begin(), b.end());

	return newList;
}

vector<int> TACVisitor::mergeList(vector<int>& a, vector<int>& b, vector<int>& c)
{
	if (a.size() + b.size() + c.size() == 0) {
		return vector<int>();
	}
	vector<int> newList;
	newList.reserve(a.size() + b.size() + c.size());
	newList.insert(newList.end(), a.begin(), a.end());
	newList.insert(newList.end(), b.begin(), b.end());
	newList.insert(newList.end(), c.begin(), c.end());
	return newList;
}

void TACVisitor::backpatch(vector<int>& list,unsigned instr)
{
	for (vector<int>::iterator it = list.begin(); it != list.end(); it++) {
		this->codes[*it]->result->labelInstr = instr;
	}
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