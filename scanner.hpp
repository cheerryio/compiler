#ifndef SCANNER_HPP
#define SCANNER_HPP


/**
 * Generated Flex class name is yyFlexLexer by default. If we want to use more flex-generated
 * classes we should name them differently. See scanner.l prefix option.
 * 
 * Unfortunately the implementation relies on this trick with redefining class name
 * with a preprocessor macro. See GNU Flex manual, "Generating C++ Scanners" section
 */
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer sfFlexLexer
#include <FlexLexer.h>
#endif

// Scanner method signature is defined by this macro. Original yylex() returns int.
// Sinice Bison 3 uses symbol_type, we must change returned type. We also rename it
// to something sane, since you cannot overload return type.
#include "parser.hpp" // this is needed for symbol_type
#include "location.hh"

#undef YY_DECL
#define YY_DECL saltyfish::Parser::symbol_type saltyfish::Scanner::get_next_token()


namespace saltyfish {    
class Scanner : public yyFlexLexer {
public:
	Scanner(){}
    Scanner(std::istream *in):yyFlexLexer(in){}
	virtual ~Scanner() {}
	virtual saltyfish::Parser::symbol_type get_next_token();
	using yyFlexLexer::yylex;
private:

};

}

#endif