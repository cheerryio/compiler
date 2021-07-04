#include <string>
#include "TAC.h"
#include "TACParser.h"
#include "CFG.h"
#include "A32CodeGen.h"

using namespace std;
using namespace saltyfish;

int main() {
	string filename = "../../output.tac";
	vector<TACCode*> codes = TACParser::loadTAC(filename);
	CFG cfg(codes);
	cfg.buildCFG();
	cfg.optimize();
	cfg.updateActive();
	filename = "../../graph/graph.dot";
	cfg.CFGDot(filename);
	A32CodeGen a32CodeGen(cfg);
	return 0;
}