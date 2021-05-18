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
			Int, Var, J
		} opnType;
			int intVal;
			unsigned labelInstr;
			string identName;
		unsigned offset;
	public:
		TACOpn();
		TACOpn(OpnType opnType);
		TACOpn(OpnType opnType,int intVal);
		TACOpn(OpnType opnType, string identName);
		~TACOpn();
		friend std::ostream& operator<<(std::ostream& o, const TACOpn& opn);
	};

	struct TACCode {
	public:
		unsigned instr;	// 数字表示的指令位置（第几条指令）
		enum class OpCode {
			Add, Sub, Mul, Div, Mod,
			JLT, JLE, JGT, JGE, JE, JNE,
			UAdd, USub,
			GOTO,
			Assign,
			Imm, Var, Param, Call, Arg, Return, Function
		} op;
		TACOpn* opn1, * opn2, * result;
		TACCode* prev, * next;
	public:
		static std::map<TACCode::OpCode, std::string> OpCodeMap;
	public:
		TACCode(TACCode::OpCode op, TACOpn* result);
		TACCode(TACCode::OpCode op, TACOpn* opn1, TACOpn* result);
		TACCode(TACCode::OpCode op, TACOpn* opn1, TACOpn* opn2, TACOpn* result);
		~TACCode();
		friend std::ostream& operator<<(std::ostream& o, const TACCode& code);
	};

	struct TAC {
	public:
		SymbolAttr* place;
		Type::TypeCode type;
		unsigned offset;
		unsigned width;
		TACCode* code;
		vector<int> truelist;
		vector<int> falselist;
		vector<int> nextlist;
		vector<int> continuelist;
	public:
		TAC() {}
		~TAC() {}
	};
}

