#include "TACVisitor.h"

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
	this->nameTab = new MMNameTab();
	this->funcTab = new MFuncTab();
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

// handle variable registration in nameTab
void TACVisitor::visit(ValueDecl* valueDecl)
{
	auto& type = valueDecl->type;
	auto& valueDefList = valueDecl->valueDefList;
	for (auto& valueDef : valueDefList) {
		NameAttr::NameKind kind;
		unsigned val;
		bool isParam=false;
		auto& ident = valueDef->ident;
		// if constant, set val=some number, else if variable, set val=offset address
		if (ident->getConst()) {
			kind = NameAttr::NameKind::Constant;
			val = 5;
		}
		else {
			kind = NameAttr::NameKind::Variable;
			val = 5;
		}
		NameAttr* nameAttr = new NameAttr(ident->name, this->getAlias(), kind, this->nameTab->getLevel(), isParam);	// must not be a param
		nameAttr->type = type->type;
		nameAttr->val = val;	// !--------- should be offset address ------------!	
		this->nameTab->addName(ident->name, nameAttr);
		valueDef->accept(*this);
	}
}

// handle variable declare initial tac code, be aware to distinguish from the above function **visit(valueDecl)**
void TACVisitor::visit(ValueDef* valueDef)
{
	valueDef->tac = new TAC();
	TACOpn* opn = nullptr;
	TACOpn* result = nullptr;
	if (valueDef->bitFields.hasAssign) {
		auto& exp = valueDef->exp;
		exp->accept(*this);
		NameAttr* nameAttr = this->nameTab->getName(valueDef->ident->name);
		opn = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias,exp->tac->place);
		result = new TACOpn(TACOpn::OpnType::Var, nameAttr->alias,nameAttr);
		TACCode* code = new TACCode(TACCode::OpCode::Assign, opn, nullptr, result);
		this->mergeCode(code);
	}
}

void TACVisitor::visit(FuncDef* funcDef)
{
	NameAttr* fnameAttr=nullptr,*nameAttr=nullptr;	// fnameAttr for funcion name while nameAttr for param name
	auto& type = funcDef->type;
	auto& ident = funcDef->ident;
	auto& funcParamDeclList = funcDef->funcParamDeclList;
	auto& block = funcDef->block;
	fnameAttr = new NameAttr(ident->name,this->getAlias(),NameAttr::NameKind::Function,this->nameTab->getLevel(),false);	// insert function name to nameTab
	fnameAttr->type = type->type;
	fnameAttr->val=5;	// !!!!!----- should be function entry point -----!!!!!!
	this->nameTab->addName(ident->name, fnameAttr);

	TACCode* code = nullptr;
	TACOpn* result = nullptr;
	result = new TACOpn(TACOpn::OpnType::Var, fnameAttr->name,fnameAttr);
	code = new TACCode(TACCode::OpCode::Function, nullptr, nullptr, result);
	this->mergeCode(code);

	for (vector<FuncParamDecl*>::iterator it = funcParamDeclList.begin(); it < funcParamDeclList.end(); it++) {
		// loop insert function params to nameTab
		auto& type = (*it)->type;
		auto& ident = (*it)->ident;
		nameAttr = new NameAttr(ident->name, this->getAlias(), NameAttr::NameKind::Variable,this->nameTab->getLevel()+1,true);
		nameAttr->type=type->type;
		nameAttr->val=5;	// !--------------- should be offset address -----------!
		this->nameTab->addName(ident->name, nameAttr);
		result = new TACOpn(TACOpn::OpnType::Var, nameAttr->name,nameAttr);
		code = new TACCode(TACCode::OpCode::Param, nullptr, nullptr, result);
		this->mergeCode(code);
	}
	block->accept(*this);
	FuncAttr* funcAttr=new FuncAttr(ident->name,nameAttr,nullptr,0,0);
	this->funcTab->addFunc(ident->name,funcAttr);
}

void TACVisitor::visit(AssignStmt* assignStmt)
{
	auto& ident = assignStmt->ident;
	auto& exp = assignStmt->exp;
	assignStmt->tac = new TAC();
	exp->accept(*this);
	NameAttr* nameAttr = this->nameTab->getName(ident->name);
	TACOpn* opn1 = new TACOpn(TACOpn::OpnType::Var, nameAttr->alias,nameAttr);
	TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias,nameAttr);
	TACCode* code = new TACCode(TACCode::OpCode::Assign, opn1, nullptr,result);
	this->mergeCode(code);
}

void TACVisitor::visit(BlockStmt* blockStmt)
{
	this->nameTab->inBlock();
	blockStmt->tac = new TAC();
	auto& stmts = blockStmt->stmts;
	for (vector<ASTUnit*>::iterator it = stmts.begin(); it < stmts.end(); it++) {
			(*it)->accept(*this);
			if ((*it)->tac != nullptr) {
				this->backpatch((*it)->tac->nextlist, nextinstr);
			}
	}
	this->nameTab->outBlock();
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
	this->bitFields.calcCond = 1;
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
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias,exp->tac->place);
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
	ident->accept(*this);

	for (auto& param : params) {
		param->accept(*this);
		result = new TACOpn(TACOpn::OpnType::Var, param->tac->place->alias,param->tac->place);
		code = new TACCode(TACCode::OpCode::Arg, nullptr, nullptr, result);
		paramCodes.push_back(code);
	}
	this->mergeCode(paramCodes);
	NameAttr* nameAttr = ident->tac->place;
	opn = new TACOpn(TACOpn::OpnType::Var, nameAttr->name,nameAttr);
	NameAttr* temp = this->getTemp();
	result = new TACOpn(TACOpn::OpnType::Var, temp->alias,temp);
	funcallExp->tac->place = temp;
	code = new TACCode(TACCode::OpCode::Call, opn, nullptr, result);
	this->mergeCode(code);
}

void TACVisitor::visit(BinaryExp* binaryExp)
{
	Exp* Lexp = binaryExp->Lexp;
	Exp* Rexp = binaryExp->Rexp;

	TACOpn* opn1, * opn2;
	TACOpn* trueResult, * falseResult;
	TACCode* code1, * code2;


	if (binaryExp->isOpExp() && binaryExp->tac == nullptr) {
		Lexp->accept(*this);
		Rexp->accept(*this);


		binaryExp->tac = new TAC();
		NameAttr* temp = this->getTemp();
		binaryExp->tac->place = temp;

		opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias,Lexp->tac->place);
		opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias,Rexp->tac->place);
		TACOpn* result = new TACOpn(TACOpn::OpnType::Var, binaryExp->tac->place->alias,binaryExp->tac->place);
		TACCode* code = new TACCode(expTypeMapOpCode.at(binaryExp->expType), opn1, opn2, result);
		this->mergeCode(code);

		if (this->bitFields.calcCond) {
			this->bitFields.calcCond = 0;
			binaryExp->tac->truelist.push_back(nextinstr);
			binaryExp->tac->falselist.push_back(nextinstr + 1);
			opn1 = new TACOpn(TACOpn::OpnType::Var, binaryExp->tac->place->alias,binaryExp->tac->place);
			opn2 = new TACOpn(TACOpn::OpnType::Int, 0);
			trueResult = new TACOpn(TACOpn::OpnType::J);
			falseResult = new TACOpn(TACOpn::OpnType::J);
			code1 = new TACCode(TACCode::OpCode::JNE, opn1, opn2, trueResult);
			code2 = new TACCode(TACCode::OpCode::GOTO, NULL, NULL, falseResult);
			this->mergeCode(code1, code2);
		}
	}
	else if (binaryExp->isRelExp()) {
		if (binaryExp->tac == nullptr) {
			binaryExp->tac = new TAC();
		}
		this->bitFields.calcCond = 0;
		Lexp->accept(*this);
		Rexp->accept(*this);
		opn1 = new TACOpn(TACOpn::OpnType::Var, Lexp->tac->place->alias,Lexp->tac->place);
		opn2 = new TACOpn(TACOpn::OpnType::Var, Rexp->tac->place->alias,Rexp->tac->place);
		binaryExp->tac->truelist.push_back(nextinstr);
		binaryExp->tac->falselist.push_back(nextinstr + 1);
		trueResult = new TACOpn(TACOpn::OpnType::J);
		falseResult = new TACOpn(TACOpn::OpnType::J);
		code1 = new TACCode(expTypeMapOpCode.at(binaryExp->expType), opn1, opn2, trueResult);
		code2 = new TACCode(TACCode::OpCode::GOTO, NULL, NULL, falseResult);
		this->mergeCode(code1, code2);
	}
	else if (binaryExp->isBoolExp()) {
		if (binaryExp->tac == nullptr) {
			binaryExp->tac = new TAC();
		}
		this->bitFields.calcCond = 0;
		switch (binaryExp->expType) {
		case(Exp::ExpType::And):

			Lexp->accept(*this);
			this->backpatch(Lexp->tac->truelist, nextinstr);
			Rexp->accept(*this);
			binaryExp->tac->truelist = Rexp->tac->truelist;
			binaryExp->tac->falselist = this->mergeList(Lexp->tac->falselist, Rexp->tac->falselist);
			break;
		case(Exp::ExpType::Or):
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

void TACVisitor::visit(PrimaryExp* primaryExp)
{
	primaryExp->tac = new TAC();
	TACOpn* opn1, * opn2, * result, * trueResult, * falseResult;
	TACCode* code, * code1, * code2;
	if (primaryExp->childType == ASTUnit::UnitType::isIdent) {
		Ident* ident = primaryExp->ident;
		ident->accept(*this);
		NameAttr* nameAttr = ident->tac->place;
		primaryExp->tac->place = nameAttr;
	}
	else if (primaryExp->childType == ASTUnit::UnitType::isConstantInt) {
		opn1 = new TACOpn(TACOpn::OpnType::Int, primaryExp->constantInt->value);
		NameAttr* temp = this->getTemp();
		result = new TACOpn(TACOpn::OpnType::Var, temp->alias,temp);
		primaryExp->tac->place = temp;
		code = new TACCode(TACCode::OpCode::Assign, opn1, nullptr,result);
		this->mergeCode(code);
	}

	// calculating cond
	if (this->bitFields.calcCond) {
		this->bitFields.calcCond = 0;
		primaryExp->tac->truelist.clear();
		primaryExp->tac->falselist.clear();
		primaryExp->tac->truelist.push_back(nextinstr);
		primaryExp->tac->falselist.push_back(nextinstr + 1);

		opn1 = new TACOpn(TACOpn::OpnType::Var, primaryExp->tac->place->alias,primaryExp->tac->place);
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

	exp->accept(*this);
	if (unaryExp->expType == Exp::ExpType::Not) {
		this->bitFields.calcCond = 0;
		unaryExp->tac->truelist = exp->tac->falselist;
		unaryExp->tac->falselist = exp->tac->truelist;
	}
	else {
		NameAttr* temp = this->getTemp();
		unaryExp->tac->place = temp;
		opn1 = new TACOpn(TACOpn::OpnType::Var, exp->tac->place->alias,exp->tac->place);
		result = new TACOpn(TACOpn::OpnType::Var, unaryExp->tac->place->alias,unaryExp->tac->place);

		TACCode* code = new TACCode(expTypeMapOpCode.at(unaryExp->expType), opn1, nullptr, result);
		this->mergeCode(code);

		if (this->bitFields.calcCond) {
			this->bitFields.calcCond = 0;
			unaryExp->tac->truelist.push_back(nextinstr);
			unaryExp->tac->falselist.push_back(nextinstr + 1);
			opn1 = new TACOpn(TACOpn::OpnType::Var, unaryExp->tac->place->alias,unaryExp->tac->place);
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
	ident->tac->place = this->nameTab->getName(ident->name);
}

string TACVisitor::getAlias() {
	static unsigned index = 0;
	string alias = "_v" + to_string(index);
	index++;
	return alias;
}

NameAttr* TACVisitor::getTemp() {
	static unsigned index = 0;
	string name = "_t" + to_string(index);
	index++;
	NameAttr* nameAttr = new NameAttr(name, name,NameAttr::NameKind::Variable,this->nameTab->getLevel(),false);
	this->nameTab->addName(name, nameAttr);
	return nameAttr;
}

/**
* the following functions add codes to codes vector and maintain coresponding instr
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