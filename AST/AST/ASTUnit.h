#pragma once
#include <iostream>
#include "../../location.hh"

using namespace std;

namespace saltyfish {
	class ASTVisitor;
	struct TAC;

	class ASTUnit
	{
	public:
		enum UnitType {
			isASTUnit = 0, isExp, isStmt, isDecl,
			isAssignStmt,isBinaryExp,isBlockStmt,isBreakStmt,isCompUnit,
			isConstantInt,isEmptyStmt,isFuncallExp,isFuncDecl,isFuncDef,
			isFuncParamDecl,isIdent,isIfStmt,isPrimaryExp,isReturnStmt,
			isType,isUnaryExp,isValueDecl,isValueDef,isWhileStmt,isContinueStmt,
			isExpStmt
		} unitType;
		location loc;
		TAC* tac;
	public:
		ASTUnit() {
			this->unitType = ASTUnit::UnitType::isASTUnit;
		}
		ASTUnit(location loc) :loc(loc) {
			this->unitType = ASTUnit::UnitType::isASTUnit;
		}
		virtual UnitType getUnitType() {
			return this->unitType;
		}
		bool isAExp() {
			return unitType == UnitType::isBinaryExp || unitType == UnitType::isUnaryExp || unitType == UnitType::isPrimaryExp;
		}
		location getLoc() {
			return this->loc;
		}
		bool isSameUnitType(ASTUnit* unit) {
			return this->unitType == unit->unitType;
		}
		virtual void accept(ASTVisitor& visitor) = 0;
	};
}
