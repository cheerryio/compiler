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
		enum TypeCode {
			Void = 0 , Int
		} type;
		std::string typeStr;
	public:
		static std::map<std::string, TypeCode> strTypeMap;
		static std::map<Type::TypeCode, std::string> typeMap;
	public:
		Type(TypeCode type, location loc);
		static TypeCode mapType(std::string& typeStr);
		static std::string mapTypeStr(const Type& type);
		virtual void accept(ASTVisitor& visitor);
		friend std::ostream& operator<<(std::ostream& o, const Type& type);
	};

}