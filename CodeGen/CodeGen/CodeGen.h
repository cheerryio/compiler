#pragma once
#include <vector>
#include "CFG.h"

namespace saltyfish {
	class CodeGen
	{
	public:
		CFG cfg;
	public:
		CodeGen(CFG& cfg):cfg(cfg) {}
		~CodeGen() {}
	};
}
