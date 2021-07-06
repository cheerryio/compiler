#pragma once
#include <vector>
#include "CFG.h"

namespace saltyfish {
	class CodeGen
	{
	public:
		CFG cfg;
	public:
		CodeGen() {}
		CodeGen(CFG cfg) :cfg(cfg) {}
	};
}
