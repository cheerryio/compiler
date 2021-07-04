#pragma once
#include <unordered_map>
#include <string>
#include <assert.h>
#include <vector>

#include "Type.h"

namespace saltyfish {
	class NameAttr
	{
	public:
		typedef unsigned level_t;
	public:
		std::string name;
		std::string alias;
		enum class NameKind {
			Constant, Variable, Type, Function
		} kind;
		level_t level;
		Type::TypeCode type;	// for variable or function, set its type or return type
		bool isParam;
		//ref pointer to ArrTab
		unsigned val;			// For variable(including param) set its offset address. For function, set its entry point address. For type, set its size.
		NameAttr* link;			// pointer to last name in the same level
		std::pair<unsigned, bool> active;	// active info. first for next use instr, second for is active
	public:
		NameAttr(){}
		NameAttr(std::string name,std::string alias,NameAttr::NameKind kind,NameAttr::level_t level,bool isParam)
		:name(name),alias(alias),kind(kind),level(level),isParam(isParam){}
		~NameAttr(){}
	};

	class NameTab
	{
	public:
		typedef NameAttr::level_t level_t;
	public:
		level_t level = 0;
	public:
		virtual level_t getLevel() = 0;
		virtual void inBlock() = 0;							// enter a block, either a function block or a block
		virtual void outBlock() = 0; 						// leave a block, either a function block or a block
		virtual NameAttr* addName(std::string name,NameAttr* nameAttr) = 0;
		virtual void delNames(level_t level) = 0;			// delete all names in level
		virtual NameAttr* getName(std::string name, level_t level) = 0;
		virtual NameAttr* getName(std::string name) = 0;	// search current nameTab and all previous nameTabs
		virtual NameAttr* getLastName(std::string name) = 0;// find last name in current level. If no last name in this wholly new level, return nullptr
		virtual bool dulDeclare(std::string name) = 0;
	};

	class FuncAttr
	{
	public:
		std::string name;
		NameAttr* lastpar;	// pointer to last function param
		NameAttr* last;		// pointer to last function local variable
		size_t psize;		// size of all params
		size_t vsize;		// size of all local variables
	public:
		FuncAttr() {}
		FuncAttr(std::string name, NameAttr* lastpar, NameAttr* last, size_t psize, size_t vsize)
			:name(name), lastpar(lastpar), last(last), psize(psize), vsize(vsize) {}
		~FuncAttr() {}
	};

	class FuncTab
	{
	public:
		FuncAttr* func = nullptr;
	public:
		virtual FuncAttr* addFunc(std::string name, FuncAttr* funcAttr) = 0;
		virtual FuncAttr* delFunc(std::string name) = 0;
		virtual FuncAttr* getFunc() = 0;	// get func which currently processing
	};
}