
/* scanner for a toy Pascal-like language */
%option yylineno noyywrap c++ yyclass="Scanner" prefix="sf" yylineno
/*%option case-insensitive*/

%x LINE_COMMENT
%x BLOCK_COMMENT

%{
    #include <math.h>
    #include "scanner.hpp"
    #include "location.hh"

    #define yyterminate() saltyfish::Parser::make_END(saltyfish::location());
%}

%%

"int"                                   {return saltyfish::Parser::make_T_INT(yytext,saltyfish::location());}
"const"                                 {return saltyfish::Parser::make_T_CONST(yytext,saltyfish::location());}
"void"                                  {return saltyfish::Parser::make_T_VOID(yytext,saltyfish::location());}
"if"                                    {return saltyfish::Parser::make_T_IF(yytext,saltyfish::location());}
"else"                                  {return saltyfish::Parser::make_T_ELSE(yytext,saltyfish::location());}
"while"                                 {return saltyfish::Parser::make_T_WHILE(yytext,saltyfish::location());}
"break"                                 {return saltyfish::Parser::make_T_BREAK(yytext,saltyfish::location());}
"continue"                              {return saltyfish::Parser::make_T_CONTINUE(yytext,saltyfish::location());}
"return"                                {return saltyfish::Parser::make_T_RETURN(yytext,saltyfish::location());}

[_[:alpha:]]([_[:alpha:]]|[[:digit:]])* {return saltyfish::Parser::make_IdentStr(yytext,saltyfish::location());}

([[:digit:]]{-}[0])[[:digit:]]*         {return saltyfish::Parser::make_DECIMAL(atoi(yytext),saltyfish::location());}
0[01234567]*                            {return saltyfish::Parser::make_OCTAL(atoi(yytext),saltyfish::location());}
0[xX][[:xdigit:]]+                      {return saltyfish::Parser::make_HEXADECIMAL(atoi(yytext),saltyfish::location());}

"="                                     {return saltyfish::Parser::make_T_EQUAL(saltyfish::location());}
"+"                                     {return saltyfish::Parser::make_T_ADD(saltyfish::location());}
"-"                                     {return saltyfish::Parser::make_T_SUB(saltyfish::location());}
"*"                                     {return saltyfish::Parser::make_T_MUL(saltyfish::location());}
"/"                                     {return saltyfish::Parser::make_T_DIV(saltyfish::location());}
"%"                                     {return saltyfish::Parser::make_T_MOD(saltyfish::location());}

"<"                                     {return saltyfish::Parser::make_T_B(saltyfish::location());}
">"                                     {return saltyfish::Parser::make_T_A(saltyfish::location());}
"<="                                    {return saltyfish::Parser::make_T_BE(saltyfish::location());}
">="                                    {return saltyfish::Parser::make_T_AE(saltyfish::location());}
"!"                                     {return saltyfish::Parser::make_T_NOT(saltyfish::location());}
"=="                                    {return saltyfish::Parser::make_T_E(saltyfish::location());}
"!="                                    {return saltyfish::Parser::make_T_NE(saltyfish::location());}
"&&"                                    {return saltyfish::Parser::make_T_AND(saltyfish::location());}
"||"                                    {return saltyfish::Parser::make_T_OR(saltyfish::location());}

";"                                     {return saltyfish::Parser::make_T_SEMICOLON(saltyfish::location());}
","                                     {return saltyfish::Parser::make_T_COMMA(saltyfish::location());}
"("                                     {return saltyfish::Parser::make_T_LS(saltyfish::location());}
")"                                     {return saltyfish::Parser::make_T_RS(saltyfish::location());}
"["                                     {return saltyfish::Parser::make_T_LM(saltyfish::location());}
"]"                                     {return saltyfish::Parser::make_T_RM(saltyfish::location());}
"{"                                     {return saltyfish::Parser::make_T_LB(saltyfish::location());}
"}"                                     {return saltyfish::Parser::make_T_RB(saltyfish::location());}

[[:blank:]]+                            {}
\n                                      {}
<<EOF>>                                 {return saltyfish::Parser::make_END(saltyfish::location());}
.                                       

<INITIAL>{
    "//"      BEGIN(LINE_COMMENT);
}
<LINE_COMMENT>{
    "\n"      BEGIN(0);
    [^\n]+    ;
}

<INITIAL>{
    "/*"      BEGIN(BLOCK_COMMENT);
}
<BLOCK_COMMENT>{
    "*/"      BEGIN(0);
    [^*\n]+   ;
    "*"[^/]   ;
    \n        ;
}

%%