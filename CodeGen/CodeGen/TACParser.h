#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "TAC.h"
#include "Table.h"

namespace saltyfish {
	class TACParser
	{
	public:
		static void ltrim(std::string& s);
		static void rtrim(std::string& s);
		static void trim(std::string& s);
		static bool isNumber(std::string& s);
		static TACCode::OpCode findOpCode(string &opString);
		static TACOpn::OpnType findOpnType(string& opnString, bool isResult);
		static std::vector<TACCode*> loadTAC(std::string &filename);
	};
}

