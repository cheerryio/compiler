#include "BlockStmt.h"

using namespace std;
using namespace saltyfish;

BlockStmt::BlockStmt() {}

BlockStmt::BlockStmt(std::vector<std::unique_ptr<ASTUnit>> stmts)
	:stmts(std::move(stmts))
{
	
}