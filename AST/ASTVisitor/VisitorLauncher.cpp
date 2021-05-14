#include "VisitorLauncher.h"

using namespace std;
using namespace saltyfish;

VisitorLauncher::VisitorLauncher()
{
	unsigned mode = 0x00000111;
	new (this)VisitorLauncher(mode);
}

VisitorLauncher::VisitorLauncher(unsigned mode)
{
	if (mode & 0x00000001)		this->visitors.push_back(messageVisitor);
	if (mode & 0x00000010)		this->visitors.push_back(semanticVisitor);
	if (mode & 0x00000100)		this->visitors.push_back(tacVisitor);
}

void VisitorLauncher::launch(CompUnit* compUnit)
{
	for (ASTVisitor* visitor : this->visitors) {
		visitor->visit(compUnit);
	}
}
