#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <assert.h>
#include "TAC.h"

namespace saltyfish {
	class CFGBasicBlock
	{
	public:
		unsigned id;
		unsigned start, end;	// left close, right open
		std::vector<TACCode*> codes;
	public:
		CFGBasicBlock();
		CFGBasicBlock(unsigned id, unsigned start);
		~CFGBasicBlock();
	};

	class CFG
	{
	public:
		std::vector<TACCode*> codes;
		std::vector<CFGBasicBlock*> basicBlocks;
		std::vector<std::pair<unsigned, unsigned>> flows;
	public:
		CFG();
		CFG(std::vector<TACCode*> codes);
		~CFG();
		unsigned instrToBasicBlockId(unsigned instr);
		void buildCFG();
		void optimize();
		void updateActive();
		void CFGDot(string &filename);
	};
}
