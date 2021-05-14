#include "Exp.h"

using namespace saltyfish;

std::map<Exp::ExpType, std::string> Exp::ExpTypeMap = {
	{Exp::ExpType::Mul,"Mul *"},
	{Exp::ExpType::Div,"Div /"},
	{Exp::ExpType::Mod,"Mod %"},
	{Exp::ExpType::Add,"Add +"},
	{Exp::ExpType::Sub,"Sub -"},
	{Exp::ExpType::B,  "B   <"},
	{Exp::ExpType::A,  "A   >"},
	{Exp::ExpType::Be, "Be <="},
	{Exp::ExpType::Ae, "Ae >="},
	{Exp::ExpType::E,  "E  =="},
	{Exp::ExpType::Ne, "Ne !="},
	{Exp::ExpType::And,"And&&"},
	{Exp::ExpType::Or, "Or ||"},
	{Exp::ExpType::Equal,"Equal=="},
	{Exp::ExpType::Not,"Not !"},
	{Exp::ExpType::UnaryAdd,"UAdd +"},
	{Exp::ExpType::UnarySub,"USub -"},
	{Exp::ExpType::Assign,"Assign ="}
};

bool Exp::isCondExp()
{
	if (this->expType <= Exp::ExpType::Not && this->expType >= Exp::ExpType::B)
		return true;
	return false;
}