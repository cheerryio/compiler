%require "3.5"
%language "c++"
%output "parser.cpp"
%defines
%locations
%lex-param	 { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%define parse.error verbose
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { saltyfish }

%code requires
{
		#include <iostream>
		#include <string>
		#include <vector>
		#include <stdint.h>
		#include <utility>
		#include "AST/AST/ASTUnit.h"
		#include "AST/AST/CompUnit.h"
		#include "AST/AST/ConstantInt.h"
		#include "AST/AST/Ident.h"
		#include "AST/AST/Type.h"
		#include "AST/AST/ValueDef.h"
		#include "AST/AST/FuncDef.h"
		#include "AST/AST/Decl.h"
		#include "AST/AST/ValueDecl.h"
		#include "AST/AST/FuncDecl.h"
		#include "AST/AST/FuncParamDecl.h"
		#include "AST/AST/Exp.h"
		#include "AST/AST/BinaryExp.h"
		#include "AST/AST/UnaryExp.h"
		#include "AST/AST/PrimaryExp.h"
		#include "AST/AST/FuncallExp.h"
		#include "AST/AST/Stmt.h"
		#include "AST/AST/IfStmt.h"
		#include "AST/AST/WhileStmt.h"
		#include "AST/AST/BreakStmt.h"
		#include "AST/AST/ReturnStmt.h"
		#include "AST/AST/ContinueStmt.h"
		#include "AST/AST/AssignStmt.h"
		#include "AST/AST/EmptyStmt.h"
		#include "AST/AST/BlockStmt.h"
		#include "AST/AST/ExpStmt.h"
		#include "AST/ASTVisitor/VisitorLauncher.h"
		using namespace std;

		namespace saltyfish {
			class Driver;
			class Scanner;
		}

		#define BINARY_EXP(a,b,c,binaryExpType,d) {	\
			Exp* Lexp=(b);Exp* Rexp=(c);	\
			Exp* e=new BinaryExp(Exp::ExpType::binaryExpType,Lexp,Rexp,d);	\
			(a)=e;	\
		}
}

%code top
{
		#include <iostream>
		#include "scanner.hpp"
		#include "parser.hpp"
		#include "location.hh"
		#include "driver.hpp"
		using namespace saltyfish;
}

%code
{
	#define yylex scanner.get_next_token
}

%token T_COMMA "逗号"
%token T_SEMICOLON "分号"
%token T_LB "左大括号"
%token T_RB "右大括号"
%token T_LM "左中括号"
%token T_RM "右中括号"
%token T_LS "左小括号"
%token T_RS "右小括号"

%token T_EQUAL  "等号"

%token <string> T_CONST "const关键字";
%token <string> T_INT   "int关键字"
%token <string> T_VOID "void关键字"

%token <string> T_IF "if关键字"
%token <string> T_ELSE "else关键字"
%token <string> T_WHILE "while关键字"
%token <string> T_BREAK "break关键字"
%token <string> T_CONTINUE "continue关键字"
%token <string> T_RETURN "return关键字"

%token T_ADD "加号"
%token T_SUB "减号"
%token T_MUL "乘号"
%token T_DIV "除号"
%token T_MOD "余号"
%token T_NOT "感叹号"
%token T_L "小于号"
%token T_G "大于号"
%token T_LE "小于等于号"
%token T_GE "大于等于号"
%token T_E "等于等于号"
%token T_NE "不等于号"
%token T_AND "与号"
%token T_OR "或号"

%left T_EQUAL
%left T_OR
%left  T_AND
%left T_L T_G T_LE T_GE
%left T_E T_NE
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
%right T_NOT

%token <string> IdentStr "标识符"
%token <int> DECIMAL "十进制常数"
%token <int> OCTAL "八进制常数"
%token <int> HEXADECIMAL "十六进制常数"

%token END 0 "文件结尾"

%nonassoc T_LOWER_THEN_ELSE
%nonassoc T_ELSE

%type < ConstantInt* > Number
%type < Ident* >       Ident
%type < Type* >        BType
%type < ValueDef* >      ValueDef
%type < vector<ValueDef*> > ValueDefList
%type < Exp* >         Exp
%type < ValueDecl* >    ValueDecl
%type < FuncParamDecl* > FuncParamDecl
%type < vector<FuncParamDecl*> > FuncParamDeclList
%type < vector<Exp*> >  FuncallParamList
%type < vector<Exp*> >			ArrayDimSubList ArrayDimList 
%type < Stmt* >		Stmt
%type < Decl* >		Decl
%type < vector<ASTUnit*> > BlockItemList
%type < BlockStmt* >	Block
%type < FuncDef* >	FuncDef
%type < vector<ASTUnit*> > CompUnitList
%type < CompUnit* >	CompUnit


%start CompUnit

%%

CompUnit:
	CompUnitList
		{
			vector<ASTUnit*> compUnitList=$1;
			CompUnit* compUnit=new CompUnit(compUnitList,@$);
			VisitorLauncher* visitorLauncher=new VisitorLauncher(0x00001010);
			visitorLauncher->launch(compUnit);
			//$$=compUnit;
		}

CompUnitList:
	%empty
		{
			$$=vector<ASTUnit*>();
		}
|	CompUnitList Decl
		{
			ASTUnit* decl=$2;
			vector<ASTUnit*> compUnitList=$1;
			compUnitList.push_back(decl);
			$$=compUnitList;
		}
|	CompUnitList FuncDef
		{
			ASTUnit* funcDef=$2;
			vector<ASTUnit*> compUnitList=$1;
			compUnitList.push_back(funcDef);
			$$=compUnitList;
		}

ArrayDimList:
	%empty
		{
			vector<Exp*> arrayDimList;
			$$=arrayDimList;
		}
|	ArrayDimSubList
		{
			vector<Exp*> &arrayDimList=$1;
			$$=arrayDimList;
		}
|	T_LM T_RM ArrayDimSubList
		{
			vector<Exp*> &arrayDimList=$3;
			arrayDimList.insert(arrayDimList.begin(),nullptr);
			$$=arrayDimList;
		}

ArrayDimSubList:
	T_LM Exp T_RM
		{
			vector<Exp*> arrayDimSubList;
			Exp* exp=$2;
			arrayDimSubList.push_back(exp);
			$$=arrayDimSubList;
		}
|	ArrayDimSubList T_LM Exp T_RM
		{
			vector<Exp*> &arrayDimSubList=$1;
			Exp* exp=$3;
			arrayDimSubList.push_back(exp);
			$$=arrayDimSubList;
		}

BType:
	T_INT {$$=new Type(Type::mapType($1),@$);}
|	T_VOID {$$=new Type(Type::mapType($1),@$);}

Decl:
	ValueDecl	{$$=$1;}

ValueDecl:
	T_CONST BType ValueDefList T_SEMICOLON
		{
			Type* type=$2;
			vector<ValueDef*> &valueDefList=$3;
			ValueDecl* v=new ValueDecl(type,valueDefList,@$);
			v->setIdentConst();
			$$=v;
		}
|	BType ValueDefList T_SEMICOLON
		{
			Type*  type=$1;
			vector<ValueDef*> &valueDefList=$2;
			auto v=new ValueDecl(type,valueDefList,@$);
			$$=v;
		}

ValueDefList:
	ValueDef
		{
			ValueDef* valueDef=$1;
			$$=vector<ValueDef*>();
			$$.push_back(valueDef);
		}
|	ValueDefList T_COMMA ValueDef
		{
			ValueDef* valueDef=$3;
			vector<ValueDef*> &varDefList=$1;
			varDefList.push_back(valueDef);
			$$=varDefList;
		}

ValueDef:
	Ident ArrayDimList
		{
			Ident* ident=$1;
			vector<Exp*> &arrayDimList=$2;
			auto valueDef=new ValueDef(ident,arrayDimList,@$);
			$$=valueDef;
		}
|	Ident ArrayDimList T_EQUAL Exp
		{
			Ident* ident=$1;
			vector<Exp*> &arrayDimList=$2;
			Exp* exp=$4;
			auto valueDef=new ValueDef(ident,arrayDimList,exp,@$);
			valueDef->bitFields.hasAssign=1;
			ident->exp=exp;
			$$=valueDef;
		}
|	Ident ArrayDimList T_EQUAL ArrayAssignList
		{

		}

ArrayAssignList:
	T_LB T_RB {}
|	T_LB ArrayAssignSubList T_RB {}

ArrayAssignSubList:
	Exp
		{
		}
|	ArrayAssignSubList T_COMMA Exp
		{
		}
|	ArrayAssignSubList T_COMMA ArrayAssignList
		{
		}

FuncDef:
	BType Ident T_LS T_RS Block
	{
		Type* type=$1;
		Ident* ident=$2;
		BlockStmt* block=$5;
		auto funcDef=new FuncDef(type,ident,block,@$);
		$$=funcDef;
	}
|	BType Ident T_LS FuncParamDeclList T_RS Block
		{
			Type* type=$1;
			Ident* ident=$2;
			vector<FuncParamDecl*> funcParamDeclList=$4;
			BlockStmt* block=$6;
			auto funcDef=new FuncDef(type,ident,funcParamDeclList,block,@$);
			$$=funcDef;
		}

FuncParamDeclList:
	FuncParamDecl
		{
			$$=vector<FuncParamDecl*>();
			FuncParamDecl* funcParamDecl=$1;
			$$.push_back(funcParamDecl);
		}
|	FuncParamDeclList T_COMMA FuncParamDecl
		{
			vector<FuncParamDecl*> &funcParamDeclList=$1;
			FuncParamDecl* funcParamDecl=$3;
			funcParamDeclList.push_back(funcParamDecl);
			$$=funcParamDeclList;
		}

FuncParamDecl:
	BType Ident
		{
			Type* type=$1;
			Ident* ident=$2;
			FuncParamDecl*  funcParamDecl=new FuncParamDecl(type,ident,@$);
			$$=funcParamDecl;
		}

Block:
	T_LB T_RB {$$=new BlockStmt(@$);}
|	T_LB BlockItemList T_RB
		{
			vector<ASTUnit*> blockItemList=$2;
			auto block=new BlockStmt(blockItemList,@$);
			$$=block;
		}

BlockItemList:
	Decl
		{
			$$=vector<ASTUnit*>();
			ASTUnit* decl=$1;
			$$.push_back(decl);
		}
|	Stmt
		{
			$$=vector<ASTUnit*>();
			ASTUnit* stmt=$1;
			$$.push_back(stmt);
		}
|	BlockItemList Decl
		{
			vector<ASTUnit*> &blockItemList=$1;
			ASTUnit* unit=$2;
			blockItemList.push_back(unit);
			$$=blockItemList;
		}
|	BlockItemList Stmt
		{
			vector<ASTUnit*> &blockItemList=$1;
			ASTUnit* unit=$2;
			blockItemList.push_back(unit);
			$$=blockItemList;
		}

Stmt:
	Ident T_EQUAL Exp T_SEMICOLON
		{
			Ident* ident=$1;
			Exp* exp=$3;
			auto assignStmt=new AssignStmt(ident,exp,@$);
			$$=assignStmt;
		}
|	T_SEMICOLON
		{
			auto emptyStmt=new EmptyStmt(@$);
			$$=emptyStmt;
		}
|	Exp T_SEMICOLON
		{
			Exp* exp=$1;
			auto expStmt=new ExpStmt(exp,@$);
			$$=expStmt;
		}
|	Block {$$=$1;}
|	T_IF T_LS Exp T_RS Stmt %prec T_LOWER_THEN_ELSE
		{
			Exp* cond=$3;
			Stmt* ifBody=$5;
			IfStmt*  ifStmt=new IfStmt(cond,ifBody,@$);
			$$=ifStmt;
		}
|	T_IF T_LS Exp T_RS Stmt T_ELSE Stmt
		{
			Exp* cond=$3;
			Stmt* ifBody=$5;
			Stmt* elseBody=$7;
			auto ifStmt=new IfStmt(cond,ifBody,elseBody,@$);
			$$=ifStmt;
		}
|	T_WHILE T_LS Exp T_RS Stmt
		{
			Exp* cond=$3;
			Stmt* body=$5;
			auto whileStmt=new WhileStmt(cond,body,@$);
			$$=whileStmt;
		}
|	T_BREAK T_SEMICOLON
		{
			auto breakStmt=new BreakStmt(@$);
			$$=breakStmt;
		}
|	T_CONTINUE T_SEMICOLON
		{
			auto continueStmt=new ContinueStmt(@$);
			$$=continueStmt;
		}
|	T_RETURN Exp T_SEMICOLON
		{
			Exp* exp=$2;
			auto returnStmt=new ReturnStmt(exp,@$);
			$$=returnStmt;
		}
|	T_RETURN T_SEMICOLON
		{
			auto returnStmt=new ReturnStmt(@$);
			$$=returnStmt;
		}

Ident:
	IdentStr
		{
			string identStr=$1;
			auto ident=new Ident(identStr,@$);
			$$=ident;
		}

Number:
	DECIMAL
		{
			int n=$1;
			auto constant=new ConstantInt(ConstantInt::ConstantIntType::Decimal,n,@$);
			$$=constant;
		}
|	OCTAL
		{
			int n=$1;
			auto constant=new ConstantInt(ConstantInt::ConstantIntType::Octal,n,@$);
			$$=constant;
		}
|	HEXADECIMAL
		{
			int n=$1;
			auto constant=new ConstantInt(ConstantInt::ConstantIntType::Hexadecimal,n,@$);
			$$=constant;
		}

FuncallParamList:
	Exp
		{
			$$=vector<Exp*>();
			Exp* exp=$1;
			$$.push_back(exp);
		}
|	FuncallParamList T_COMMA Exp
		{
			Exp* exp=$3;
			vector<Exp*> &funcParamList=$1;
			funcParamList.push_back(exp);
			$$=funcParamList;
		}

Exp:
	Exp T_MUL Exp	{BINARY_EXP($$,$1,$3,Mul,@$);}
|	Exp T_DIV Exp	{BINARY_EXP($$,$1,$3,Div,@$);}
|	Exp T_MOD Exp	{BINARY_EXP($$,$1,$3,Mod,@$);}
|	Exp T_ADD Exp	{BINARY_EXP($$,$1,$3,Add,@$);}
|	Exp T_SUB Exp	{BINARY_EXP($$,$1,$3,Sub,@$);}
|	Exp T_L Exp		{BINARY_EXP($$,$1,$3,L,@$);}
|	Exp T_G Exp		{BINARY_EXP($$,$1,$3,G,@$);}
|	Exp T_LE Exp	{BINARY_EXP($$,$1,$3,Le,@$);}
|	Exp T_GE Exp	{BINARY_EXP($$,$1,$3,Ge,@$);}
|	Exp T_E Exp		{BINARY_EXP($$,$1,$3,E,@$);}
|	Exp T_NE Exp	{BINARY_EXP($$,$1,$3,Ne,@$);}
|	Exp T_AND Exp	{BINARY_EXP($$,$1,$3,And,@$);}
|	Exp T_OR Exp	{BINARY_EXP($$,$1,$3,Or,@$);}
|	T_LS Exp T_RS	{$$=$2;}
|	Ident			{$$=new PrimaryExp($1,@$);}
|	Number			{$$=new PrimaryExp($1,@$);}
|	Ident T_LS T_RS	{$$=new FuncallExp($1,@$);}
|	Ident T_LS FuncallParamList T_RS
	{
		vector<Exp*> &funcallParamList=$3;
		Ident* ident=$1;
		auto funcallExp=new FuncallExp(ident,funcallParamList,@$);
		$$=funcallExp;
	}
|	T_ADD Exp		{$$=new UnaryExp(Exp::ExpType::UnaryAdd,$2,@$);}
|	T_SUB Exp		{$$=new UnaryExp(Exp::ExpType::UnarySub,$2,@$);}
|	T_NOT Exp		{$$=new UnaryExp(Exp::ExpType::Not,$2,@$);}
%%
namespace saltyfish
{
	// Report an error to the user.
	auto Parser::error (const saltyfish::location &loc,const string& msg) -> void
	{
		cerr << msg <<"     location:"<<loc<< '\n';
	}
}