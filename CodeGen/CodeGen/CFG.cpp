#include "CFG.h"

using namespace std;
using namespace saltyfish;

CFGBasicBlock::CFGBasicBlock(unsigned id, unsigned start)
    :id(id), start(start)
{
}

CFG::CFG(std::vector<TACCode*> codes)
    :codes(codes)
{

}

CFG::~CFG(){

}

unsigned CFG::instrToBasicBlockId(unsigned instr)
{
    for (CFGBasicBlock* bb : this->basicBlocks) {
        if (instr >= bb->start && instr < bb->end) {
            return bb->id;
        }
    }
    return -1;
}

void CFG::buildCFG()
{
    vector<unsigned int> starts; //starts includes what? first code, code after branch, code branch to
    vector<pair<unsigned, unsigned>> instrFlows;
    pair<unsigned, unsigned> flow;
    if (!this->codes.size())
        return;
    // find all blcok starts and instr flow
    starts.push_back(0);    // first code
    for (int i = 1; i < this->codes.size(); i++) {
        TACCode* code = this->codes[i];
        if (code->result != nullptr && code->result->opnType == TACOpn::OpnType::J) {
            unsigned labelInstr=code->result->labelInstr;
            starts.push_back(code->instr + 1);    // code after branch
            starts.push_back(labelInstr); // code branch to
            flow.first = this->codes[i]->instr;
            flow.second=labelInstr;
            instrFlows.push_back(flow);
            if (code->op != TACCode::OpCode::GOTO) {
                flow.second = code->instr + 1;
                instrFlows.push_back(flow);
            }
        }
    }

    // generate each basic block
    int i = 0;
    unsigned id = 0;
    CFGBasicBlock* basicBlock = new CFGBasicBlock(id, i++);
    for (; i < this->codes.size(); i++) {
        if (std::find(starts.begin(), starts.end(), i) == starts.end()) {
            // not find
        }
        else {
            basicBlock->end = i;
            this->basicBlocks.push_back(basicBlock);
            id++;
            basicBlock = new CFGBasicBlock(id, i);
        }
    }
    basicBlock->end = i;
    this->basicBlocks.push_back(basicBlock);

    // find basic block flow
    for (pair<unsigned, unsigned> instrFLow : instrFlows) {
        flow.first = instrToBasicBlockId(instrFLow.first);
        flow.second = instrToBasicBlockId(instrFLow.second);
        this->flows.push_back(flow);
    }
}

void CFG::CFGDot(string &filename){
    ofstream f;
    f.open(filename);
    f << "digraph G{" << endl;
    for (int i = 0; i < this->basicBlocks.size();i++) {
        CFGBasicBlock* bb = this->basicBlocks[i];
        f << "bb" << i << "[shape=\"square\" "
            << "label=\"" << endl;
        for (int m = bb->start; m < bb->end; m++) {
            f << *(this->codes[m]);
            f << "\\n";
            f << endl;
        }
        f << "\"]" << endl;
    }
    for (pair<unsigned, unsigned> flow : this->flows) {
        f << "bb" << flow.first << " -> " << "bb" << flow.second << endl;
    }
    f << "}";
}
