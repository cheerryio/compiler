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
	vector<ASTUnit*>& compUnitList = compUnit->compUnitList;
	for (vector<ASTUnit*>::iterator it = compUnitList.begin(); it != compUnitList.end(); it++) {
		(*it)->accept(*this);
	}

	this->displayCodes();
	this->storeCodes("output.tac");
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
* �������ֽ�����ű��������¼���Ӧ����λ��
*/
void TACVisitor::visit(FuncDef* funcDef)
{
	// �������ű�
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	auto& funcParamDeclList = funcDef->funcParamDeclList;
	auto& block = funcDef->block;
	SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr,this->getAlias(),type->type, SymbolAttr::SymbolRole::Function);
	this->table->addSymbol(ident->identStr, symbolAttr);

	// �����м����
	TACCode* code = nullptr;
	TACOpn* result = nullptr;
	result = new TACOpn(TACOpn::OpnType::Var, symbolAttr->name);
	code = new TACCode(TACCode::OpCode::Function, nullptr, nullptr, result);
	this->mergeCode(code);

	for (vector<FuncParamDecl*>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		// ���ű�
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		SymbolAttr* symbolAttr = new SymbolAttr(ident->identStr, this->getAlias(), type->type, SymbolAttr::SymbolRole::FunctionParam, 0, 0);	// ȷ��const array
		symbolAttr->level = this->table->getLevel() + 1;
		this->table->addSymbol(ident->identStr, symbolAttr);
		// �м����
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
	exp->accept(*this);		//�ȶ�exp�ݹ����
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
	for (vector<ASTUnit*>::iterator it = stmts.begin(); it < stmts.end(); it++) {
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
	this->bitFields.calcCond = 1;	// ������ָʾ�����BinaryOpExp, PrimaryExp, UnaryExp��������list����
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
		// �˴�����Ҫ��������if�������������
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
	ident->accept(*this);	// ��identȥ���Լ���symbolAttr���ԣ����ڷ��ű��еĶ�Ӧ��

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
* �ȵݹ鴦���ӽڵ㣬�ٴ������ڵ�
* �õ������ӽڵ��place������Ӧ����
* 
* ��binaryExp�У������������ӽ�����Һ��ӽ���Լ�op����һ������
* ����DAG
*/
void TACVisitor::visit(BinaryExp* binaryExp)
{
	Exp* Lexp = binaryExp->Lexp;
	Exp* Rexp = binaryExp->Rexp;
	// �ȵݹ鴦�����ӣ��õ���Ҫ������
	TACOpn* opn1, * opn2;
	TACOpn* trueResult, * falseResult;
	TACCode* code1, * code2;

	/**
	* ������op�Ķ�Ԫ����ڵ㣬һ��tac������㼴��
	* ��Ҫ�����µ���ʱ����
	*/
	if (binaryExp->isOpExp() && binaryExp->tac == nullptr) {
		Lexp->accept(*this);
		Rexp->accept(*this);

		// �ȷ��ʺ��ӣ��������Լ�������temp�������
		binaryExp->tac = new TAC();
		SymbolAttr* temp = this->getTemp();
		binaryExp->tac->place = temp;

		opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias);
		opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias);
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, binaryExp->tac->place->alias);
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
	* ����С�� �ȹ�ϵ���������Ҫ���ɲ�����truelist,falselistΪnextistr,nextistr+1
	* ����Ҫ�����µ���ʱ����
	*/
	else if (binaryExp->isRelExp()) {
		if (binaryExp->tac == nullptr) {
			binaryExp->tac = new TAC();
		}
		this->bitFields.calcCond = 0;
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
	* ������������˴���Ҫ����
	* ����Ҫ�µ���ʱ����
	*/
	else if (binaryExp->isBoolExp()) {
		if (binaryExp->tac == nullptr) {
			binaryExp->tac = new TAC();
		}
		this->bitFields.calcCond = 0;
		switch (binaryExp->expType) {
		case(Exp::ExpType::And):
			// ��Ҫfalse��·
			// B -> B1 && M B2 ����B1�����nextinstr����M�Ĵ���λ��
			Lexp->accept(*this);
			this->backpatch(Lexp->tac->truelist, nextinstr);
			Rexp->accept(*this);
			binaryExp->tac->truelist = Rexp->tac->truelist;
			binaryExp->tac->falselist = this->mergeList(Lexp->tac->falselist, Rexp->tac->falselist);
			break;
		case(Exp::ExpType::Or):
			// ��Ҫtrue��·
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
* ���������PrimaryExp����ʽ
* ����Ǳ�ʶ�������ɱ�ʶ�����ֵ�opn�������ýڵ�place��Ϊ��ʶ����symbolAttr
* ��������֣�������ʱ����������������ֵ������ʱ�������ڵ�placeֵΪ��ʱ������symbolAttr
* 
* ���ڴ˽ڵ��DAG����Ȼ���ߵ����Ҷ�ӽڵ㣬��������ڵ�һ��û�б�������
*/
void TACVisitor::visit(PrimaryExp* primaryExp)
{
	primaryExp->tac = new TAC();
	TACOpn* opn1, * opn2, * result, * trueResult, * falseResult;
	TACCode* code, * code1, * code2;
	if (primaryExp->childType == ASTUnit::UnitType::isIdent) {
		Ident* ident = primaryExp->ident;
		ident->accept(*this);	// ��identȥѰ���Լ���symbolAttr
		SymbolAttr* symbolAttr = ident->tac->place;
		primaryExp->tac->place = symbolAttr;
	}
	else if (primaryExp->childType == ASTUnit::UnitType::isConstantInt) {
		opn1 = new TACOpn(TACOpn::OpnType::Int, primaryExp->constantInt->value);
		SymbolAttr* temp = this->getTemp();
		result = new TACOpn(TACOpn::OpnType::Var, temp->alias);
		primaryExp->tac->place = temp;
		code = new TACCode(TACCode::OpCode::Assign, opn1, result);
		this->mergeCode(code);
	}

	// ����cond
	if (this->bitFields.calcCond) {
		this->bitFields.calcCond = 0;
		primaryExp->tac->truelist.clear();
		primaryExp->tac->falselist.clear();
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
	unaryExp->tac = new TAC();
	TACOpn* opn1, * opn2, * result, * trueResult, * falseResult;
	TACCode* code, * code1, * code2;
	Exp* exp = unaryExp->exp;

	// ���ڲ���DAG�������ýڵ�û�б��������ŵ��ô�������
	exp->accept(*this);
	if (unaryExp->expType == Exp::ExpType::Not) {
		this->bitFields.calcCond = 0;
		unaryExp->tac->truelist = exp->tac->falselist;
		unaryExp->tac->falselist = exp->tac->truelist;
	}
	else {
		SymbolAttr* temp = this->getTemp();
		unaryExp->tac->place = temp;
		opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias);
		result = new TACOpn(TACOpn::OpnType::Var, unaryExp->tac->place->alias);

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
* ��code2���뵽code1ǰ��
* ע��˳��
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
	// ��ȷ����ָ��λ��
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

void TACVisitor::displayCodes() {
	for (vector<TACCode*>::iterator it = this->codes.begin(); it != this->codes.end(); it++) {
		cout << **it << endl;
	}
}

void TACVisitor::storeCodes(string filename){
	ofstream f;
	f.open(filename);
	for (vector<TACCode*>::iterator it = this->codes.begin(); it != this->codes.end(); it++) {
		f << **it << endl;
	}
	f.close();
}

string TACVisitor::getLable() {
	static unsigned index = 0;
	return "_L" + to_string(index);
}