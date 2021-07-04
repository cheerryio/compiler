#include "TACParser.h"

using namespace std;
using namespace saltyfish;

// trim from start (in place)
void TACParser::ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
void TACParser::rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
void TACParser::trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

bool TACParser::isNumber(std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

TACCode::OpCode TACParser::findOpCode(string &opString)
{
	for (map<TACCode::OpCode, string>::iterator it = TACCode::OpCodeMap.begin(); it != TACCode::OpCodeMap.end(); it++) {
		if (it->second == opString) {
			return it->first;
		}
	}
	return TACCode::OpCode::Empty;
}

TACOpn::OpnType TACParser::findOpnType(string& opnString,bool isResult)
{
	if (TACParser::isNumber(opnString)) {
		if (isResult)
			return TACOpn::OpnType::J;
		else
			return TACOpn::OpnType::Int;
	}
	else
		return TACOpn::OpnType::Var;
}

vector<TACCode*> TACParser::loadTAC(string &filename)
{
	ifstream f;
	string line;
	unsigned instr;
	string token;
	char c;
	TACCode* code = NULL;
	TACOpn* opn1 = NULL, * opn2 = NULL, * result = NULL;
	TACOpn::OpnType opnType;
	vector<TACCode*> codes;
	f.open(filename);
#define GET_OPN(opn,isResult)	\
	if (token != "NULL") {	\
		opnType = TACParser::findOpnType(token,isResult);	\
		if (TACParser::isNumber(token))	\
			opn = new TACOpn(opnType, stoi(token));	\
		else \
			opn = new TACOpn(opnType, token,new NameAttr());	\
	}	\
	else{	\
		opn = nullptr;	\
	}

	if (f.is_open()) {
		while (getline(f, line)) {
			stringstream s(line);
			s >> instr;
			s >> c;
			getline(s, token, ',');
			TACParser::trim(token);
			TACCode::OpCode op = TACParser::findOpCode(token);	// find op
			getline(s, token, ',');
			trim(token);
			GET_OPN(opn1,false);
			getline(s, token, ',');
			trim(token);
			GET_OPN(opn2,false);
			getline(s, token, ',');
			trim(token);
			if (token != "NULL") {
				opnType = TACParser::findOpnType(token, true);
				if (TACParser::isNumber(token)) {
					result = new TACOpn(opnType, stoi(token));
					result->labelInstr = stoi(token);
				}
				else
					result = new TACOpn(opnType, token,new NameAttr());
			}else{
				result=nullptr;
			}
			code = new TACCode(op, opn1, opn2, result);
			code->instr = instr;
			codes.push_back(code);
		}
	}
	f.close();
	return codes;
}
