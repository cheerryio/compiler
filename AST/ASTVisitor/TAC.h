#pragma once
#include <vector>
#include <string>
#include "MMNameTab.h"
#include "Exp.h"
#include "Table.h"

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
		NameAttr* nameAttr;
	public:
		TACOpn();
		TACOpn(OpnType opnType);
		TACOpn(OpnType opnType,int intVal);
		TACOpn(OpnType opnType, string identName, NameAttr* nameAttr);
		~TACOpn();
		friend std::ostream& operator<<(std::ostream& o, const TACOpn& opn);
	};

	struct TACCode {
	public:
		unsigned instr;	// order of code
		enum class OpCode {
			Add, Sub, Mul, Div, Mod,
			JLT, JLE, JGT, JGE, JE, JNE,
			UAdd, USub,
			GOTO,
			Assign,
			Imm, Var, Param, Call, Arg, Return, Function,
			Empty
		} op;
		TACOpn* opn1, * opn2, * result;
		TACCode* prev, * next;
	public:
		static std::map<TACCode::OpCode, std::string> OpCodeMap;
	public:
		TACCode(TACCode::OpCode op, TACOpn* opn1, TACOpn* opn2, TACOpn* result);
		~TACCode();
		bool isBinaryOpCode();
		bool isAssignCode();
		friend std::ostream& operator<<(std::ostream& o, const TACCode& code);
	};

	struct TAC {
	public:
		NameAttr* place;
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

