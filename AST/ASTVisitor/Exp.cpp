#include "Exp.h"

using namespace saltyfish;

std::map<Exp::ExpType, std::string> Exp::ExpTypeMap = {
	{Exp::ExpType::Mul,"Mul *"},
	{Exp::ExpType::Div,"Div /"},
	{Exp::ExpType::Mod,"Mod %"},
	{Exp::ExpType::Add,"Add +"},
	{Exp::ExpType::Sub,"Sub -"},
	{Exp::ExpType::L,  "L   <"},
	{Exp::ExpType::G,  "G   >"},
	{Exp::ExpType::Le, "Le <="},
	{Exp::ExpType::Ge, "Ge >="},
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