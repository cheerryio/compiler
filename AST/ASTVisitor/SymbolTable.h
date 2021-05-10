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
	* SymbolTable抽象类
	* 定义了符号表的基本方法
	*/
	class SymbolTable
	{
	public:
		typedef SymbolAttr::level_t level_t;
		typedef SymbolAttr::times_t times_t;
	public:
		level_t level = 0;	// 当前所处作用域级别
	public:
		virtual void inScope() = 0;	// 进入作用域
		virtual void outScope() = 0;	// 出作用域
		/**
		* 插入符号及其对应属性
		*/
		virtual int addSymbol(std::string symbolName,SymbolAttr* symbolAttr) = 0;
		/**
		* 当出作用域时，清楚该作用域所有的临时变量
		*/
		virtual void clearSymbol() = 0;
		/**
		* 查符号表，判断该符号是否被定义过
		* 返回最近被定义的层级
		*/
		virtual SymbolAttr* declared(std::string symbolName) = 0;
		/**
		* 符号是否在当前作用域已经被定义
		*/
		virtual bool dulplicateDeclared(std::string symbolName) = 0;
	};
}