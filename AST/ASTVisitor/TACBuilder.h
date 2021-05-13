#pragma once
#include <string>
#include "SymbolTableList.h"
#include "CompUnit.h"
#include "Ident.h"
#include "Type.h"
#include "ConstantInt.h"
#include "EmptyStmt.h"
#include "ExpStmt.h"
#include "AssignStmt.h"
#include "BlockStmt.h"
#include "BreakStmt.h"
#include "ContinueStmt.h"
#include "IfStmt.h"
#include "ReturnStmt.h"
#include "WhileStmt.h"
#include "FuncDecl.h"
#include "ValueDecl.h"
#include "FuncParamDecl.h"
#include "ValueDef.h"
#include "FuncDef.h"
#include "BinaryExp.h"
#include "FuncallExp.h"
#include "PrimaryExp.h"
#include "UnaryExp.h"

using namespace std;
namespace saltyfish {

	struct TACOpn {
	public:
		enum class OpnType {
			Int,Var
		} opnType;
		union {
			int intVal;
			string identName;
		};
		unsigned offset;
	public:
		TACOpn() {}
		~TACOpn() {}
	};

	struct TACCode {
	public:
		enum class TACOp {
			Mul,Div,Add,Sub
		} op;
		TACOpn *opn1, *opn2, *result;
		TACCode* prev, *next;
	public:
		TACCode(TACOpn* opn1,TACOpn* opn2,TACOpn* result)
			:opn1(opn1),opn2(opn2),result(result){}
		~TACCode() {}
	};

	struct TAC {
	public:
		SymbolAttr* place;
		Type::IdentType type;
		unsigned offset;
		unsigned width;
		TACCode* code;
		string Etrue;
		string Efalse;
		string Snext;
	public:
		TAC() {}
		~TAC() {}
	};

	class TACBuilder
	{
	public:
		SymbolTableList* table = nullptr;
		unsigned tempIndex = 0;
		unsigned varIndex = 0;

	public:
		SymbolAttr* newTemp();
		TACCode* codeGen(Exp* exp);
		TACOpn* getOpn(Exp* exp);
		TACOpn* getOpn(PrimaryExp* primaryExp);
		TACOpn* getOpn(BinaryExp* binaryExp);
	};
}

