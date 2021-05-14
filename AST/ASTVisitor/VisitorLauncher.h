#pragma once
#include <vector>

#include "MessageVisitor.h"
#include "SemanticVisitor.h"
#include "TACVisitor.h"

namespace saltyfish {
	class VisitorLauncher
	{
	public:
		MessageVisitor* messageVisitor = new MessageVisitor();
		SemanticVisitor* semanticVisitor = new SemanticVisitor();
		TACVisitor* tacVisitor = new TACVisitor();
		std::vector<ASTVisitor*> visitors;
		
	public:
		VisitorLauncher();
		VisitorLauncher(unsigned mode);
		void launch(CompUnit* compUnit);
	};
}

