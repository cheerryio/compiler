#pragma once

namespace saltyfish {
	class ASTVisitor;

	class ASTUnit
	{
	public:
		virtual void accept(ASTVisitor& visitor) = 0;
	};
}
