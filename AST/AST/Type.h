#pragma once
#include <map>
#include <string>
namespace saltyfish{
	class ASTVisitor;

	class Type {
	public:
		enum IdentType {
			Int, String, Void
		} type;
		std::string typeStr;
		std::map<std::string, IdentType> strTypeMap = {
			{"int",Int},
			{"void",Void},
			{"string",String}
		};
	public:
		Type();
		Type(std::string &typeStr);
		virtual void accept(ASTVisitor& visitor);
	};

}