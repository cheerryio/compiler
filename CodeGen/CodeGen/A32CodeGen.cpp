#include "A32CodeGen.h"

using namespace std;
using namespace saltyfish;

A32CodeGen::A32CodeGen()
{
	this->rvalue = {
		{A32::Register::R0 ,{}},
		{A32::Register::R1 ,{}},
		{A32::Register::R2 ,{}},
		{A32::Register::R3 ,{}},
		{A32::Register::R4 ,{}},
		{A32::Register::R5 ,{}},
		{A32::Register::R6 ,{}},
		{A32::Register::R7 ,{}},
		{A32::Register::R8 ,{}},
		{A32::Register::R9 ,{}},
		{A32::Register::R10,{}},
	};
}

A32CodeGen::A32CodeGen(CFG cfg)
	:CodeGen(cfg)
{
	new (this)A32CodeGen();
}

A32CodeGen::~A32CodeGen()
{
	
}

/**
* algrithm for register alloc
* for A:=B op C return a register to store A
* PRIORITY RULES:
* 1.try to return (register holds only and only if B) && (B,A are the same name || B is not active)
* 2.try spare register
* 3.try to grab occupied register
* 
* 
* 
*/
A32::Register A32CodeGen::getRegister(TACOpn* opn1, TACOpn* opn2, TACOpn* result)
{
	// try rule 1
	if (avalue.find(opn1->identName) != avalue.end()) {
		// some register holds B
		auto& avalueSet_B = avalue[opn1->identName];
		for (auto it = avalueSet_B.begin(); it != avalueSet_B.end(); it++) {
			auto& rvalueSet = this->rvalue.at(*it);
			assert(rvalueSet.find(opn1->identName) != rvalueSet.end());
			if ((rvalueSet.size() == 1) && (opn1->identName == result->identName || opn1->nameAttr->active.second == false))
				return *it;
		}
	}
	
	// try rule 2
	for (auto it = rvalue.begin(); it != rvalue.end(); it++) {
		auto& rvalueSet = it->second;
		if (rvalueSet.empty())
			return it->first;
	}

	// try rule 3
	return A32::Register::R10;
}
