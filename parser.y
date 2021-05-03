%require "3.5"
%language "c++"
%output "parser.cpp"
%defines
%locations
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
		#include "AST/AST/ConstantInt.h"
		#include "AST/AST/Ident.h"
		#include "AST/AST/Type.h"
		#include "AST/AST/ValueDef.h"
		#include "AST/AST/Decl.h"
		#include "AST/AST/ValueDecl.h"
		#include "AST/AST/FuncDecl.h"
		#include "AST/AST/FuncParamDecl.h"
		#include "AST/AST/Exp.h"
		#include "AST/AST/BinaryExp.h"
		#include "AST/AST/UnaryExp.h"
		#include "AST/AST/PrimaryExp.h"
		#include "AST/AST/FuncallExp.h"
		using namespace std;

		namespace saltyfish {
			class Driver;
			class Scanner;
		}

		#define BINARY_EXP(a,b,c,binaryExpType) {	\
			unique_ptr<Exp> Lexp=std::move((b));unique_ptr<Exp> Rexp=std::move((c));	\
			auto e=make_unique<BinaryExp>(BinaryExp::BinaryExpType::binaryExpType,std::move(Lexp),std::move(Rexp));	\
			(a)=std::move(e);	\
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

%token <std::string> T_CONST "const关键字";
%token <std::string> T_INT   "int关键字"
%token <std::string> T_VOID "void关键字"

%token <std::string> T_IF "if关键字"
%token <std::string> T_ELSE "else关键字"
%token <std::string> T_WHILE "while关键字"
%token <std::string> T_BREAK "break关键字"
%token <std::string> T_CONTINUE "continue关键字"
%token <std::string> T_RETURN "return关键字"

%token T_ADD "加号"
%token T_SUB "减号"
%token T_MUL "乘号"
%token T_DIV "除号"
%token T_MOD "余号"
%token T_NOT "感叹号"
%token T_B "小于号"
%token T_A "大于号"
%token T_BE "小于等于号"
%token T_AE "大于等于号"
%token T_E "等于等于号"
%token T_NE "不等于号"
%token T_AND "与号"
%token T_OR "或号"

%left T_EQUAL
%left T_OR
%left  T_AND
%left T_B T_A T_BE T_AE
%left T_E T_NE
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
%right T_NOT

%token <std::string> IdentStr "标识符"
%token <int> DECIMAL "十进制常数"
%token <int> OCTAL "八进制常数"
%token <int> HEXADECIMAL "十六进制常数"

%token END 0 "文件结尾"

%nonassoc T_LOWER_THEN_ELSE
%nonassoc T_ELSE

%type < unique_ptr<ConstantInt> > Number
%type < unique_ptr<Ident> >       Ident
%type < unique_ptr<Type> >        BType
%type < unique_ptr<ValueDef> >      ValueDef
%type < std::vector<unique_ptr<ValueDef>> > ValueDefList
%type < unique_ptr<Exp> >         Exp
%type < unique_ptr<ValueDecl> >    VarDecl
%type < unique_ptr<FuncParamDecl> > FuncParamDecl
%type < std::vector<unique_ptr<FuncParamDecl>> > FuncParamDeclList
%type < std::vector<unique_ptr<Exp>> >  FuncallParamList
%type < std::vector<unique_ptr<Exp>> >			ArrayDimSubList ArrayDimList 

%start CompUnit

%%

CompUnit:
	%empty
|	CompUnit Decl
|	CompUnit FuncDef

ArrayDimList:
	%empty
		{
			std::vector<unique_ptr<Exp>> arrayDimList;
			$$=std::move(arrayDimList);
		}
|	ArrayDimSubList
		{
			std::vector<unique_ptr<Exp>> &arrayDimList=$1;
			$$=std::move(arrayDimList);
		}
|	T_LM T_RM ArrayDimSubList
		{
			std::vector<unique_ptr<Exp>> &arrayDimList=$3;
			unique_ptr<Exp> f(nullptr);
			arrayDimList.insert(arrayDimList.begin(),std::move(f));
			$$=std::move(arrayDimList);
		}

ArrayDimSubList:
	T_LM Exp T_RM
		{
			std::vector<unique_ptr<Exp>> arrayDimSubList;
			unique_ptr<Exp> exp=std::move($2);
			arrayDimSubList.push_back(std::move(exp));
			$$=std::move(arrayDimSubList);
		}
|	T_LM Exp T_RM ArrayDimSubList
		{
			std::vector<unique_ptr<Exp>> &arrayDimSubList=$4;
			unique_ptr<Exp> exp=std::move($2);
			arrayDimSubList.push_back(std::move(exp));
			$$=std::move(arrayDimSubList);
		}

BType:
	T_INT 
		{
			std:string &typeStr=$1;
			$$=make_unique<Type>(typeStr);
		}

Decl:
	ConstDecl | VarDecl

ConstDecl:
	T_CONST BType ValueDefList T_SEMICOLON {cout<<"常量声明"<<endl;}

VarDecl:
	BType ValueDefList T_SEMICOLON
		{
			unique_ptr<Type> type=std::move($1);
			std::vector<unique_ptr<ValueDef>> &varDefList=$2;
			auto v=make_unique<ValueDecl>(std::move(type),std::move(varDefList));
			$$=std::move(v);
		}

ValueDefList:
	ValueDef
		{
			unique_ptr<ValueDef> valueDef=std::move($1);
			$$=std::vector<unique_ptr<ValueDef>>();
			$$.push_back(std::move(valueDef));
		}
|	ValueDefList T_COMMA ValueDef
		{
			unique_ptr<ValueDef> &valueDef=$3;
			std::vector<unique_ptr<ValueDef>> &varDefList=$1;
			varDefList.push_back(std::move(valueDef));
			$$=std::move(varDefList);
		}

ValueDef:
	Ident ArrayDimList
		{
			unique_ptr<Ident> ident=std::move($1);
			std::vector<unique_ptr<Exp>> &arrayDimList=$2;
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			$$=std::move(valueDef);
		}
|	Ident ArrayDimList T_EQUAL InitVal
		{
			unique_ptr<Ident> ident=std::move($1);
			std::vector<unique_ptr<Exp>> &arrayDimList=$2;
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			$$=std::move(valueDef);
		}

InitVal:
	Exp
|	T_LB T_RB
|	T_LB exp_comma_list T_RB

exp_comma_list:
	InitVal
|	exp_comma_list T_COMMA InitVal

FuncDef:
	BType Ident T_LS T_RS Block {cout<<"函数无参声明"<<endl;}
	T_VOID Ident T_LS T_RS Block {cout<<"函数无参声明"<<endl;}
|	BType Ident T_LS FuncParamDeclList T_RS Block {cout<<"函数有参声明"<<endl;}
|	T_VOID Ident T_LS FuncParamDeclList T_RS Block {cout<<"函数有参声明"<<endl;}

FuncParamDeclList:
	FuncParamDecl
		{
			$$=std::vector<unique_ptr<FuncParamDecl>>();
			unique_ptr<FuncParamDecl> funcParamDecl=std::move($1);
			$$.push_back(std::move(funcParamDecl));
		}
|	FuncParamDecl T_COMMA FuncParamDeclList
		{
			std::vector<unique_ptr<FuncParamDecl>> &funcParamDeclList=$3;
			unique_ptr<FuncParamDecl> funcParamDecl=std::move($1);
			funcParamDeclList.push_back(std::move(funcParamDecl));
			$$=std::move(funcParamDeclList);
		}

FuncParamDecl:
	BType Ident
		{
			unique_ptr<Type> type=std::move($1);
			unique_ptr<Ident> ident=std::move($2);
			unique_ptr<FuncParamDecl> funcParamDecl=make_unique<FuncParamDecl>(std::move(type),std::move(ident));
			$$=std::move(funcParamDecl);
		}

Block:
	T_LB T_RB {cout<<"空块"<<endl;}
|	T_LB BlockItem T_RB

BlockItem:
	Decl
|	Stmt
|	BlockItem Decl
|	BlockItem Stmt

Stmt:
	Ident T_EQUAL Exp T_SEMICOLON
|	T_SEMICOLON
|	Exp T_SEMICOLON
|	Block
|	T_IF T_LS Exp T_RS Stmt %prec T_LOWER_THEN_ELSE  {cout<<"if语句"<<endl;}
|	T_IF T_LS Exp T_RS Stmt T_ELSE Stmt              {cout<<"if else语句"<<endl;}
|	T_WHILE T_LS Exp T_RS Stmt                       {cout<<"while语句"<<endl;}
|	T_BREAK T_SEMICOLON                               {cout<<"break语句"<<endl;}
|	T_CONTINUE T_SEMICOLON                            {cout<<"continue语句"<<endl;}
|	T_RETURN Exp T_SEMICOLON                         {cout<<"return sth.语句"<<endl;}
|	T_RETURN T_SEMICOLON                              {cout<<"return语句"<<endl;}

Ident:
	IdentStr
		{
			std::string identStr=$1;
			auto ident=make_unique<Ident>(identStr);
			$$=std::move(ident);
		}

Number:
	DECIMAL
	{
		unique_ptr<ConstantInt> constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Decimal,$1);
		$$=std::move(constant);
	}
|	OCTAL
	{
		unique_ptr<ConstantInt> constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Octal,$1);
		$$=std::move(constant);
	}
|	HEXADECIMAL
	{
		unique_ptr<ConstantInt> constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Hexadecimal,$1);
		$$=std::move(constant);
	}

FuncallParamList:
	Exp
		{
			$$=std::vector<unique_ptr<Exp>>();
			unique_ptr<Exp> exp=std::move($1);
			$$.push_back(std::move(exp));
		}
|	FuncallParamList T_COMMA Exp
		{
			unique_ptr<Exp> exp=std::move($3);
			std::vector<unique_ptr<Exp>> &funcParamList=$1;
			funcParamList.push_back(std::move(exp));
			$$=std::move(funcParamList);
		}

Exp:
	Exp T_MUL Exp	{BINARY_EXP($$,$1,$3,Mul);}
|	Exp T_DIV Exp	{BINARY_EXP($$,$1,$3,Div);}
|	Exp T_MOD Exp	{BINARY_EXP($$,$1,$3,Mod);}
|	Exp T_ADD Exp	{BINARY_EXP($$,$1,$3,Add);}
|	Exp T_SUB Exp	{BINARY_EXP($$,$1,$3,Sub);}
|	Exp T_B Exp		{BINARY_EXP($$,$1,$3,B);}
|	Exp T_A Exp		{BINARY_EXP($$,$1,$3,A);}
|	Exp T_BE Exp	{BINARY_EXP($$,$1,$3,Be);}
|	Exp T_AE Exp	{BINARY_EXP($$,$1,$3,Ae);}
|	Exp T_E Exp		{BINARY_EXP($$,$1,$3,E);}
|	Exp T_NE Exp	{BINARY_EXP($$,$1,$3,Ne);}
|	Exp T_AND Exp	{BINARY_EXP($$,$1,$3,And);}
|	Exp T_OR Exp	{BINARY_EXP($$,$1,$3,Or);}
|	Exp T_EQUAL Exp	{BINARY_EXP($$,$1,$3,Equal);}
|	T_LS Exp T_RS	{$$=std::move($1);}
|	Ident			{$$=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::Ident,std::move($1)));}
|	Number			{$$=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::ConstantInt,std::move($1)));}
|	Ident T_LS T_RS	{$$=std::move(make_unique<FuncallExp>(std::move($1)));}
|	Ident T_LS FuncallParamList T_RS
	{
		std::vector<unique_ptr<FuncallParam> &funcallParamList=$3;
		unique_ptr<Ident> &ident=$1;
		auto funcallExp=make_unique<FuncallExp>(std::move(ident),std::move(funcallParamList));
		$$=std::move(funcallExp);
	}
|	T_ADD Exp		{$$=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Add,std::move($1)));}
|	T_SUB Exp		{$$=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Sub,std::move($1)));}
|	T_NOT Exp		{$$=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Not,std::move($1)));}
%%
namespace saltyfish
{
	// Report an error to the user.
	auto Parser::error (const saltyfish::location &loc,const std::string& msg) -> void
	{
		std::cerr << msg <<"     location:"<<loc<< '\n';
	}
}