#include <vector>
#include <memory>

#include "CompUnit.h"
#include "../ASTVisitor/ASTVisitor.h"

using namespace std;
using namespace saltyfish;

CompUnit::CompUnit(std::vector<std::unique_ptr<ASTUnit>> compUnitList,location loc)
	:ASTUnit(loc), compUnitList(std::move(compUnitList))
{
	this->unitType = ASTUnit::UnitType::isCompUnit;
}

void CompUnit::accept(ASTVisitor& visitor) {
	visitor.visit(this);
}