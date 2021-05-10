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
		enum SymbolDeclarer{
			Func,Var,ArrVar,ConstVar,ConstArrVar
		} declarer;
		Type::IdentType specifier;
		times_t referedTimes=0;
		level_t level;
		saltyfish::SymbolAttr* prev;
		saltyfish::SymbolAttr* next;
	public:
		SymbolAttr();
		SymbolAttr(SymbolAttr::SymbolDeclarer declarer, Type::IdentType specifier, unsigned level);
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
		virtual void inScope() = 0;	// ����������
		virtual void outScope() = 0;	// ��������
		/**
		* ������ż����Ӧ����
		*/
		virtual int addSymbol(std::string symbolName,SymbolAttr* symbolAttr) = 0;
		/**
		* ����������ʱ����������������е���ʱ����
		*/
		virtual void clearSymbol() = 0;
		/**
		* ����ű��жϸ÷����Ƿ񱻶����
		* �������������Ĳ㼶
		*/
		virtual SymbolAttr* declared(std::string symbolName) = 0;
		/**
		* �����Ƿ��ڵ�ǰ�������Ѿ�������
		*/
		virtual bool dulplicateDeclared(std::string symbolName) = 0;
	};
}