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
		opn = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
		result = new TACOpn(TACOpn::OpnType::Var, symbolAttr->alias);
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
	auto& funcParamDeclList = funcDef->funcParamDeclList;
	auto& block = funcDef->block;
	SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr,this->getAlias(),type->type, SymbolAttr::SymbolRole::Function);
	this->table->addSymbol(ident->identStr, symbolAttr);

	// 生成中间代码
	TACCode* code = nullptr;
	TACOpn* result = nullptr;
	result = new TACOpn(TACOpn::OpnType::Var, symbolAttr->name);
	code = new TACCode(TACCode::OpCode::Function, nullptr, nullptr, result);
	this->mergeCode(code);

	for (vector<unique_ptr<FuncParamDecl>>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		// 符号表
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr, this->getAlias(), type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// 确认const array
		symbolAttr->level = this->table->getLevel() + 1;
		this->table->addSymbol(ident->identStr, symbolAttr);
		// 中间代码
		result = new TACOpn(TACOpn::OpnType::Var, symbolAttr->name);
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
	this->mergeCode(code);
}

void TACVisitor::visit(BlockStmt* blockStmt)
{
	this->table->inScope();
	blockStmt->tac = new TAC();
	auto& stmts = blockStmt->stmts;
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
	TACOpn* result = new TACOpn(TACOpn::OpnType::J);
	TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
	this->mergeCode(code);
}

void TACVisitor::visit(ContinueStmt* continueStmt)
{
	this->continuelist.push_back(this->nextinstr);
	TACOpn* result = new TACOpn(TACOpn::OpnType::J);
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
	this->bitFields.calcCond = 1;	// 该属性指示最近的BinaryOpExp, PrimaryExp, UnaryExp计算生成list属性
	if (!ifStmt->bitFields.hasElse) {
		cond->accept(*this);
		this->backpatch(cond->tac->truelist, nextinstr);
		ifBody->accept(*this);
		ifStmt->tac->nextlist = this->mergeList(cond->tac->falselist, ifBody->tac->nextlist);
	}
	else {
		auto& elseBody = ifStmt->elseBody;
		cond->accept(*this);
		unsigned M1_instr = this->nextinstr;
		ifBody->accept(*this);
		unsigned N_instr = this->nextinstr;
		// 此代码需要回填整个if语句跳出到哪里
		TACOpn* result = new TACOpn(TACOpn::OpnType::J);
		TACCode* code = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, result);
		this->mergeCode(code);
		unsigned M2_instr = this->nextinstr;
		elseBody->accept(*this);

		this->backpatch(cond->tac->truelist, M1_instr);
		this->backpatch(cond->tac->falselist, M2_instr);
		ifStmt->tac->nextlist = this->mergeList(ifBody->tac->nextlist, elseBody->tac->nextlist);
		ifStmt->tac->nextlist.push_back(N_instr);
	}
}

void TACVisitor::visit(ReturnStmt* returnStmt)
{
	returnStmt->tac = new TAC();
	TACCode* code = nullptr;
	if (returnStmt->bitFields.hasExp) {
		auto& exp = returnStmt->exp;
		exp->accept(*this);
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
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
	this->bitFields.calcCond = 1;
	cond->accept(*this);
	unsigned M2_instr = nextinstr;
	body->accept(*this);
	this->backpatch(body->tac->nextlist, M1_instr);
	this->backpatch(this->continuelist, M1_instr);
	this->backpatch(cond->tac->truelist, M2_instr);
	whileStmt->tac->nextlist = this->mergeList(whileStmt->tac->nextlist, this->breaklist, cond->tac->falselist);
	this->continuelist.clear();
	this->breaklist.clear();
	TACOpn* result = new TACOpn(TACOpn::OpnType::J);
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
	ident->accept(*this);	// 让ident去找自己的symbolAttr属性（即在符号表中的对应）

	for (auto& param : params) {
		param->accept(*this);
		result = new TACOpn(TACOpn::OpnType::Var, param->tac->place->alias);
		code = new TACCode(TACCode::OpCode::Arg, nullptr, nullptr, result);
		paramCodes.push_back(code);
	}
	this->mergeCode(paramCodes);
	SymbolAttr* symbolAttr = ident->tac->place;
	opn = new TACOpn(TACOpn::OpnType::Var, symbolAttr->name);
	SymbolAttr* temp = this->getTemp();
	result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
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
	TACOpn* opn1, *opn2;
	TACOpn* trueResult, * falseResult;
	TACCode* code1, * code2;

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
		if (this->bitFields.calcCond) {
			this->bitFields.calcCond = 0;
			binaryExp->tac->truelist.push_back(nextinstr);
			binaryExp->tac->falselist.push_back(nextinstr + 1);
			opn1 = new TACOpn(TACOpn::OpnType::Var, binaryExp->tac->place->alias);
			opn2 = new TACOpn(TACOpn::OpnType::Int, 0);
			trueResult = new TACOpn(TACOpn::OpnType::J);
			falseResult = new TACOpn(TACOpn::OpnType::J);
			code1 = new TACCode(TACCode::OpCode::JNE, opn1, opn2, trueResult);
			code2 = new TACCode(TACCode::OpCode::GOTO, NULL, NULL, falseResult);
			this->mergeCode(code1, code2);
		}
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
		trueResult = new TACOpn(TACOpn::OpnType::J);
		falseResult = new TACOpn(TACOpn::OpnType::J);
		code1 = new TACCode(expTypeMapOpCode.at(binaryExp->expType), opn1, opn2, trueResult);
		code2 = new TACCode(TACCode::OpCode::GOTO, NULL, NULL, falseResult);
		this->mergeCode(code1, code2);
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
	TACOpn* opn1, * opn2, * result, * trueResult, * falseResult;
	TACCode* code, * code1, * code2;
	if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::Ident) {
		auto& ident = primaryExp->ident;
		ident->accept(*this);	// 让ident去寻找自己的symbolAttr
		SymbolAttr* symbolAttr = ident->tac->place;
		primaryExp->tac->place = symbolAttr;
	}
	else if (primaryExp->primaryExpType == PrimaryExp::PrimaryExpType::ConstantInt) {
		opn1 = new TACOpn(TACOpn::OpnType::Int, primaryExp->constantInt->value);
		SymbolAttr* temp = this->getTemp();
		result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		primaryExp->tac->place = temp;
		code = new TACCode(TACCode::OpCode::Assign, opn1, result);
		this->mergeCode(code);
	}

	// 计算cond
	if (this->bitFields.calcCond) {
		this->bitFields.calcCond = 0;
		primaryExp->tac->truelist.push_back(nextinstr);
		primaryExp->tac->falselist.push_back(nextinstr + 1);

		opn1 = new TACOpn(TACOpn::OpnType::Var, primaryExp->tac->place->alias);
		opn2 = new TACOpn(TACOpn::OpnType::Int, 0);
		trueResult = new TACOpn(TACOpn::OpnType::J);
		falseResult = new TACOpn(TACOpn::OpnType::J);
		code1 = new TACCode(TACCode::OpCode::JNE, opn1, opn2, trueResult);
		code2 = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, falseResult);
		this->mergeCode(code1,code2);
	}
}

void TACVisitor::visit(UnaryExp* unaryExp)
{
	TACOpn* opn1, * opn2, * result, * trueResult, * falseResult;
	TACCode* code, * code1, * code2;
	unaryExp->tac = new TAC();
	auto& exp = unaryExp->exp;
	exp->accept(*this);
	if (unaryExp->expType == Exp::ExpType::Not) {
		unaryExp->tac->truelist = exp->tac->falselist;
		unaryExp->tac->falselist = exp->tac->truelist;
	}
	else {
		opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
		SymbolAttr* temp = this->getTemp();
		result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		unaryExp->tac->place = temp;

		TACCode* code = new TACCode(expTypeMapOpCode.at(unaryExp->expType), opn1, result);
		this->mergeCode(code);

		if (this->bitFields.calcCond) {
			this->bitFields.calcCond = 0;
			unaryExp->tac->truelist.push_back(nextinstr);
			unaryExp->tac->falselist.push_back(nextinstr + 1);
			opn1 = new TACOpn(TACOpn::OpnType::Var, unaryExp->tac->place->alias);
			opn2 = new TACOpn(TACOpn::OpnType::Int, 0);
			trueResult = new TACOpn(TACOpn::OpnType::J);
			falseResult = new TACOpn(TACOpn::OpnType::J);
			code1 = new TACCode(TACCode::OpCode::JNE, opn1, opn2, trueResult);
			code2 = new TACCode(TACCode::OpCode::GOTO, nullptr, nullptr, falseResult);
			this->mergeCode(code1, code2);
		}
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
	SymbolAttr* symbolAttr = new SymbolAttr(name, name, Type::TypeCode::Int, SymbolAttr::SymbolRole::TempValue);
	this->table->addSymbol(name, symbolAttr);
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

void TACVisitor::mergeCode(TACCode* code1, TACCode* code2)
{
	this->mergeCode(code1);
	this->mergeCode(code2);
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
	vector<int> newList;
	newList.reserve(a.size() + b.size());
	newList.insert(newList.end(), a.begin(), a.end());
	newList.insert(newList.end(), b.begin(), b.end());

	return newList;
}

vector<int> TACVisitor::mergeList(vector<int>& a, vector<int>& b, vector<int>& c)
{
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