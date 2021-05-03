#include "FuncDecl.h"

using namespace std;
using namespace saltyfish;

FuncDecl::FuncDecl(unique_ptr<Ident> ident)
	:ident(std::move(ident))
{

}