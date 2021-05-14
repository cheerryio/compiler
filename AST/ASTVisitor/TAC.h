#pragma once
#include <string>
#include "SymbolTable.h"

using namespace std;


namespace saltyfish {
	struct TACOpn {
	public:
		enum class OpnType {
			Int, Var
		} opnType;
		union {
			int intVal;
			string identName;
		};
		unsigned offset;
	public:
		TACOpn();
		TACOpn(OpnType opnType,int intVal);
		TACOpn(OpnType opnType, string identName);
		~TACOpn();
	};

	struct TACCode {
	public:
		enum class TACCodeOp {
			Assign,
			Mul, Div, Add, Sub
		} op;
		TACOpn* opn1, * opn2, * result;
		TACCode* prev, * next;
	public:
		TACCode(TACCodeOp op, TACOpn* opn1, TACOpn* result);
		TACCode(TACCodeOp op, TACOpn* opn1, TACOpn* opn2, TACOpn* result);
		~TACCode();
		friend std::ostream& operator<<(std::ostream& o, const TACCode& code);
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
}

