#pragma once
#include <string>

namespace saltyfish {
	class ASTVisitor;

	class Ident {
	public:
		std::string identStr;

	public:
		Ident();
		Ident(std::string identStr);
		virtual void accept(ASTVisitor& visitor);
	};
}