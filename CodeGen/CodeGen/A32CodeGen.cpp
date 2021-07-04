#include "A32CodeGen.h"

using namespace std;
using namespace saltyfish;

A32CodeGen::A32CodeGen(CFG cfg)
	:CodeGen(cfg)
{

}

A32CodeGen::~A32CodeGen()
{
	
}

/**
* algrithm for register alloc
* for A:=B op C return a register to store A
* RULES:
* 1.return register holds B
* 2.spare register
* 3.grab occupied register
* 
* 
* 
*/
A32CodeGen::Registers A32CodeGen::getRegister()
{
	return A32CodeGen::Registers();
}
