#include "WhileStmt.h"

#include <memory>
#include <vector>

using namespace std;
using namespace saltyfish;

WhileStmt::WhileStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> body)
	:cond(std::move(cond)), body(std::move(body))
{
	
}
