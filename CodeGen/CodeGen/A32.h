#pragma once
#include <string>

namespace saltyfish {
	class A32
	{
	public:
		enum class Register {
			R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10
		};
	public:
		static std::string ldr(A32::Register reg, std::string name);
		static std::string str(A32::Register reg, std::string name);
	};
}
