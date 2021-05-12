#pragma once
#include <map>
#include <string>

#include "ASTUnit.h"

namespace saltyfish{
	class ASTVisitor;

	class Type 
		:virtual public ASTUnit
	{
	public:
		enum IdentType {
			Void = 0 , Int
		} type;
		std::string typeStr;
	public:
		static std::map<std::string, IdentType> strTypeMap;
		static std::map<Type::IdentType, std::string> typeMap;
	public:
		Type(IdentType type, location loc);
		static IdentType mapType(std::string& typeStr);
		static std::string mapTypeStr(const Type& type);
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const Type& type);
	};

}