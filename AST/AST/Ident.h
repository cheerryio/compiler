#pragma once
#include <string>

namespace saltyfish {
	class Ident {
	public:
		std::string identStr;

	public:
		Ident();
		Ident(std::string identStr);
	};
}