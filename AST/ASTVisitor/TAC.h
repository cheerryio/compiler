#pragma once
#include <vector>
#include <string>
#include "SymbolTable.h"
#include "Exp.h"

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
		unsigned instr;	// 数字表示的指令位置（第几条指令）
		Exp::ExpType op;
		TACOpn* opn1, * opn2, * result;
		TACCode* prev, * next;
	public:
		TACCode(Exp::ExpType op, TACOpn* opn1, TACOpn* result);
		TACCode(Exp::ExpType op, TACOpn* opn1, TACOpn* opn2, TACOpn* result);
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
		vector<int> truelist;
		vector<int> falselist;
		string Snext;
	public:
		TAC() {}
		~TAC() {}
	};
}

