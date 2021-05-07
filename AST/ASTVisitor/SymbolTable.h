#pragma once

namespace saltyfish {
	class SymbolTable
	{

	};

	class SymbolVal
	{
	public:
		enum {
			Func,Var
		} symbolType;
	};
}