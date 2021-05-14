#pragma once
#include <map>
#include <string>

#include "Type.h"

namespace saltyfish {
	class SymbolAttr
	{
	public:
		typedef unsigned level_t;
		typedef unsigned times_t;
	public:
		level_t level;
		Type::IdentType type;
		unsigned isArray : 1;
		unsigned isConst : 1;
		enum class SymbolRole {
			Function, FunctionParam, Value,TempValue
		} role : 3;
		std::string name;
		std::string alias;
		times_t referedTimes=0;
		saltyfish::SymbolAttr* paramNext;
		saltyfish::SymbolAttr* prev;
		saltyfish::SymbolAttr* next;
	public:
		SymbolAttr()
			:level(0),isArray(0),isConst(0) {}
		SymbolAttr(std::string name, std::string alias,Type::IdentType type, SymbolAttr::SymbolRole role)
			:name(name),alias(alias),type(type), role(role) {}
		SymbolAttr(std::string name, std::string alias, Type::IdentType type, SymbolAttr::SymbolRole role, unsigned isArray, unsigned isConst)
			:name(name), alias(alias), type(type), role(role), isArray(isArray), isConst(isConst) {}
		SymbolAttr(Type::IdentType type, SymbolAttr::SymbolRole role)
			:level(0), type(type), role(role), isArray(0),isConst(0) {}
		SymbolAttr(Type::IdentType type, SymbolAttr::SymbolRole role, unsigned isArray, unsigned isConst)
			:level(0), type(type), role(role), isArray(isArray), isConst(isConst) {}
	};

	/**
	* SymbolTable������
	* �����˷��ű�Ļ�������
	*/
	class SymbolTable
	{
	public:
		typedef SymbolAttr::level_t level_t;
		typedef SymbolAttr::times_t times_t;
	public:
		level_t level = 0;	// ��ǰ���������򼶱�
	public:

		virtual level_t getLevel() = 0;

		virtual void inScope() = 0;	// ����������

		virtual void outScope() = 0;	// ��������
		/**
		* ������ż����Ӧ����
		*/
		virtual SymbolAttr* addSymbol(std::string symbolName,SymbolAttr* symbolAttr) = 0;
		/**
		* ����������ʱ����������������е���ʱ����
		*/
		virtual void delSymbols() = 0;

		virtual SymbolAttr* getSymbolinLevel(std::string symbolName, level_t level) = 0;
		/**
		* ����ű��жϸ÷����Ƿ񱻶����
		* ��������ı�����ķ���
		*/
		virtual SymbolAttr* getSymbol(std::string symbolName) = 0;
		/**
		* �����Ƿ��ڵ�ǰ�������Ѿ�������
		*/
		virtual bool dulplicateDeclared(std::string symbolName) = 0;
	};
}