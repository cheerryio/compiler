#pragma once
#include <string>

#include "../ASTVisitor/ASTVisitor.h"

namespace saltyfish {
	class Ident {
	public:
		std::string identStr;

	public:
		Ident();
		Ident(std::string identStr);
		virtual void accept(ASTVisitor& visitor);
	};
}