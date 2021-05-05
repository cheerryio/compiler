// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

// "%code top" blocks.
#line 65 "parser.y"

		#include <iostream>
		#include "scanner.hpp"
		#include "parser.hpp"
		#include "location.hh"
		#include "driver.hpp"
		using namespace saltyfish;

#line 47 "parser.cpp"




#include "parser.hpp"


// Unqualified %code blocks.
#line 75 "parser.y"

	#define yylex scanner.get_next_token

#line 60 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "parser.y"
namespace  saltyfish  {
#line 152 "parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 55: // Block
        value.YY_MOVE_OR_COPY<  std::unique_ptr<BlockStmt>  > (YY_MOVE (that.value));
        break;

      case 41: // CompUnit
        value.YY_MOVE_OR_COPY<  std::unique_ptr<CompUnit>  > (YY_MOVE (that.value));
        break;

      case 46: // Decl
        value.YY_MOVE_OR_COPY<  std::unique_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 52: // FuncDef
        value.YY_MOVE_OR_COPY<  std::unique_ptr<FuncDef>  > (YY_MOVE (that.value));
        break;

      case 57: // Stmt
        value.YY_MOVE_OR_COPY<  std::unique_ptr<Stmt>  > (YY_MOVE (that.value));
        break;

      case 42: // CompUnitList
      case 56: // BlockItemList
        value.YY_MOVE_OR_COPY<  std::vector<std::unique_ptr<ASTUnit>>  > (YY_MOVE (that.value));
        break;

      case 43: // ArrayDimList
      case 44: // ArrayDimSubList
      case 60: // FuncallParamList
        value.YY_MOVE_OR_COPY<  std::vector<unique_ptr<Exp>>  > (YY_MOVE (that.value));
        break;

      case 53: // FuncParamDeclList
        value.YY_MOVE_OR_COPY<  std::vector<unique_ptr<FuncParamDecl>>  > (YY_MOVE (that.value));
        break;

      case 48: // ValueDefList
        value.YY_MOVE_OR_COPY<  std::vector<unique_ptr<ValueDef>>  > (YY_MOVE (that.value));
        break;

      case 59: // Number
        value.YY_MOVE_OR_COPY<  unique_ptr<ConstantInt>  > (YY_MOVE (that.value));
        break;

      case 61: // Exp
        value.YY_MOVE_OR_COPY<  unique_ptr<Exp>  > (YY_MOVE (that.value));
        break;

      case 54: // FuncParamDecl
        value.YY_MOVE_OR_COPY<  unique_ptr<FuncParamDecl>  > (YY_MOVE (that.value));
        break;

      case 58: // Ident
        value.YY_MOVE_OR_COPY<  unique_ptr<Ident>  > (YY_MOVE (that.value));
        break;

      case 45: // BType
        value.YY_MOVE_OR_COPY<  unique_ptr<Type>  > (YY_MOVE (that.value));
        break;

      case 47: // ValueDecl
        value.YY_MOVE_OR_COPY<  unique_ptr<ValueDecl>  > (YY_MOVE (that.value));
        break;

      case 49: // ValueDef
        value.YY_MOVE_OR_COPY<  unique_ptr<ValueDef>  > (YY_MOVE (that.value));
        break;

      case 36: // "十进制常数"
      case 37: // "八进制常数"
      case 38: // "十六进制常数"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 12: // "const关键字"
      case 13: // "int关键字"
      case 14: // "void关键字"
      case 15: // "if关键字"
      case 16: // "else关键字"
      case 17: // "while关键字"
      case 18: // "break关键字"
      case 19: // "continue关键字"
      case 20: // "return关键字"
      case 35: // "标识符"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 55: // Block
        value.move<  std::unique_ptr<BlockStmt>  > (YY_MOVE (that.value));
        break;

      case 41: // CompUnit
        value.move<  std::unique_ptr<CompUnit>  > (YY_MOVE (that.value));
        break;

      case 46: // Decl
        value.move<  std::unique_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 52: // FuncDef
        value.move<  std::unique_ptr<FuncDef>  > (YY_MOVE (that.value));
        break;

      case 57: // Stmt
        value.move<  std::unique_ptr<Stmt>  > (YY_MOVE (that.value));
        break;

      case 42: // CompUnitList
      case 56: // BlockItemList
        value.move<  std::vector<std::unique_ptr<ASTUnit>>  > (YY_MOVE (that.value));
        break;

      case 43: // ArrayDimList
      case 44: // ArrayDimSubList
      case 60: // FuncallParamList
        value.move<  std::vector<unique_ptr<Exp>>  > (YY_MOVE (that.value));
        break;

      case 53: // FuncParamDeclList
        value.move<  std::vector<unique_ptr<FuncParamDecl>>  > (YY_MOVE (that.value));
        break;

      case 48: // ValueDefList
        value.move<  std::vector<unique_ptr<ValueDef>>  > (YY_MOVE (that.value));
        break;

      case 59: // Number
        value.move<  unique_ptr<ConstantInt>  > (YY_MOVE (that.value));
        break;

      case 61: // Exp
        value.move<  unique_ptr<Exp>  > (YY_MOVE (that.value));
        break;

      case 54: // FuncParamDecl
        value.move<  unique_ptr<FuncParamDecl>  > (YY_MOVE (that.value));
        break;

      case 58: // Ident
        value.move<  unique_ptr<Ident>  > (YY_MOVE (that.value));
        break;

      case 45: // BType
        value.move<  unique_ptr<Type>  > (YY_MOVE (that.value));
        break;

      case 47: // ValueDecl
        value.move<  unique_ptr<ValueDecl>  > (YY_MOVE (that.value));
        break;

      case 49: // ValueDef
        value.move<  unique_ptr<ValueDef>  > (YY_MOVE (that.value));
        break;

      case 36: // "十进制常数"
      case 37: // "八进制常数"
      case 38: // "十六进制常数"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 12: // "const关键字"
      case 13: // "int关键字"
      case 14: // "void关键字"
      case 15: // "if关键字"
      case 16: // "else关键字"
      case 17: // "while关键字"
      case 18: // "break关键字"
      case 19: // "continue关键字"
      case 20: // "return关键字"
      case 35: // "标识符"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 55: // Block
        value.copy<  std::unique_ptr<BlockStmt>  > (that.value);
        break;

      case 41: // CompUnit
        value.copy<  std::unique_ptr<CompUnit>  > (that.value);
        break;

      case 46: // Decl
        value.copy<  std::unique_ptr<Decl> > (that.value);
        break;

      case 52: // FuncDef
        value.copy<  std::unique_ptr<FuncDef>  > (that.value);
        break;

      case 57: // Stmt
        value.copy<  std::unique_ptr<Stmt>  > (that.value);
        break;

      case 42: // CompUnitList
      case 56: // BlockItemList
        value.copy<  std::vector<std::unique_ptr<ASTUnit>>  > (that.value);
        break;

      case 43: // ArrayDimList
      case 44: // ArrayDimSubList
      case 60: // FuncallParamList
        value.copy<  std::vector<unique_ptr<Exp>>  > (that.value);
        break;

      case 53: // FuncParamDeclList
        value.copy<  std::vector<unique_ptr<FuncParamDecl>>  > (that.value);
        break;

      case 48: // ValueDefList
        value.copy<  std::vector<unique_ptr<ValueDef>>  > (that.value);
        break;

      case 59: // Number
        value.copy<  unique_ptr<ConstantInt>  > (that.value);
        break;

      case 61: // Exp
        value.copy<  unique_ptr<Exp>  > (that.value);
        break;

      case 54: // FuncParamDecl
        value.copy<  unique_ptr<FuncParamDecl>  > (that.value);
        break;

      case 58: // Ident
        value.copy<  unique_ptr<Ident>  > (that.value);
        break;

      case 45: // BType
        value.copy<  unique_ptr<Type>  > (that.value);
        break;

      case 47: // ValueDecl
        value.copy<  unique_ptr<ValueDecl>  > (that.value);
        break;

      case 49: // ValueDef
        value.copy<  unique_ptr<ValueDef>  > (that.value);
        break;

      case 36: // "十进制常数"
      case 37: // "八进制常数"
      case 38: // "十六进制常数"
        value.copy< int > (that.value);
        break;

      case 12: // "const关键字"
      case 13: // "int关键字"
      case 14: // "void关键字"
      case 15: // "if关键字"
      case 16: // "else关键字"
      case 17: // "while关键字"
      case 18: // "break关键字"
      case 19: // "continue关键字"
      case 20: // "return关键字"
      case 35: // "标识符"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 55: // Block
        value.move<  std::unique_ptr<BlockStmt>  > (that.value);
        break;

      case 41: // CompUnit
        value.move<  std::unique_ptr<CompUnit>  > (that.value);
        break;

      case 46: // Decl
        value.move<  std::unique_ptr<Decl> > (that.value);
        break;

      case 52: // FuncDef
        value.move<  std::unique_ptr<FuncDef>  > (that.value);
        break;

      case 57: // Stmt
        value.move<  std::unique_ptr<Stmt>  > (that.value);
        break;

      case 42: // CompUnitList
      case 56: // BlockItemList
        value.move<  std::vector<std::unique_ptr<ASTUnit>>  > (that.value);
        break;

      case 43: // ArrayDimList
      case 44: // ArrayDimSubList
      case 60: // FuncallParamList
        value.move<  std::vector<unique_ptr<Exp>>  > (that.value);
        break;

      case 53: // FuncParamDeclList
        value.move<  std::vector<unique_ptr<FuncParamDecl>>  > (that.value);
        break;

      case 48: // ValueDefList
        value.move<  std::vector<unique_ptr<ValueDef>>  > (that.value);
        break;

      case 59: // Number
        value.move<  unique_ptr<ConstantInt>  > (that.value);
        break;

      case 61: // Exp
        value.move<  unique_ptr<Exp>  > (that.value);
        break;

      case 54: // FuncParamDecl
        value.move<  unique_ptr<FuncParamDecl>  > (that.value);
        break;

      case 58: // Ident
        value.move<  unique_ptr<Ident>  > (that.value);
        break;

      case 45: // BType
        value.move<  unique_ptr<Type>  > (that.value);
        break;

      case 47: // ValueDecl
        value.move<  unique_ptr<ValueDecl>  > (that.value);
        break;

      case 49: // ValueDef
        value.move<  unique_ptr<ValueDef>  > (that.value);
        break;

      case 36: // "十进制常数"
      case 37: // "八进制常数"
      case 38: // "十六进制常数"
        value.move< int > (that.value);
        break;

      case 12: // "const关键字"
      case 13: // "int关键字"
      case 14: // "void关键字"
      case 15: // "if关键字"
      case 16: // "else关键字"
      case 17: // "while关键字"
      case 18: // "break关键字"
      case 19: // "continue关键字"
      case 20: // "return关键字"
      case 35: // "标识符"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 55: // Block
        yylhs.value.emplace<  std::unique_ptr<BlockStmt>  > ();
        break;

      case 41: // CompUnit
        yylhs.value.emplace<  std::unique_ptr<CompUnit>  > ();
        break;

      case 46: // Decl
        yylhs.value.emplace<  std::unique_ptr<Decl> > ();
        break;

      case 52: // FuncDef
        yylhs.value.emplace<  std::unique_ptr<FuncDef>  > ();
        break;

      case 57: // Stmt
        yylhs.value.emplace<  std::unique_ptr<Stmt>  > ();
        break;

      case 42: // CompUnitList
      case 56: // BlockItemList
        yylhs.value.emplace<  std::vector<std::unique_ptr<ASTUnit>>  > ();
        break;

      case 43: // ArrayDimList
      case 44: // ArrayDimSubList
      case 60: // FuncallParamList
        yylhs.value.emplace<  std::vector<unique_ptr<Exp>>  > ();
        break;

      case 53: // FuncParamDeclList
        yylhs.value.emplace<  std::vector<unique_ptr<FuncParamDecl>>  > ();
        break;

      case 48: // ValueDefList
        yylhs.value.emplace<  std::vector<unique_ptr<ValueDef>>  > ();
        break;

      case 59: // Number
        yylhs.value.emplace<  unique_ptr<ConstantInt>  > ();
        break;

      case 61: // Exp
        yylhs.value.emplace<  unique_ptr<Exp>  > ();
        break;

      case 54: // FuncParamDecl
        yylhs.value.emplace<  unique_ptr<FuncParamDecl>  > ();
        break;

      case 58: // Ident
        yylhs.value.emplace<  unique_ptr<Ident>  > ();
        break;

      case 45: // BType
        yylhs.value.emplace<  unique_ptr<Type>  > ();
        break;

      case 47: // ValueDecl
        yylhs.value.emplace<  unique_ptr<ValueDecl>  > ();
        break;

      case 49: // ValueDef
        yylhs.value.emplace<  unique_ptr<ValueDef>  > ();
        break;

      case 36: // "十进制常数"
      case 37: // "八进制常数"
      case 38: // "十六进制常数"
        yylhs.value.emplace< int > ();
        break;

      case 12: // "const关键字"
      case 13: // "int关键字"
      case 14: // "void关键字"
      case 15: // "if关键字"
      case 16: // "else关键字"
      case 17: // "while关键字"
      case 18: // "break关键字"
      case 19: // "continue关键字"
      case 20: // "return关键字"
      case 35: // "标识符"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 160 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &compUnitList=yystack_[0].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			auto compUnit=std::make_unique<CompUnit>(std::move(compUnitList));
			MessageVisitor visitor;
			compUnit->accept(visitor);
			yylhs.value.as <  std::unique_ptr<CompUnit>  > ()=std::move(compUnit);
		}
#line 1016 "parser.cpp"
    break;

  case 3:
#line 170 "parser.y"
                {
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::vector<std::unique_ptr<ASTUnit>>();
		}
#line 1024 "parser.cpp"
    break;

  case 4:
#line 174 "parser.y"
                {
			std::unique_ptr<ASTUnit> decl=std::move(yystack_[0].value.as <  std::unique_ptr<Decl> > ());
			std::vector<std::unique_ptr<ASTUnit>> &compUnitList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			compUnitList.push_back(std::move(decl));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(compUnitList);
		}
#line 1035 "parser.cpp"
    break;

  case 5:
#line 181 "parser.y"
                {
			std::unique_ptr<ASTUnit> funcDef=std::move(yystack_[0].value.as <  std::unique_ptr<FuncDef>  > ());
			std::vector<std::unique_ptr<ASTUnit>> &compUnitList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			compUnitList.push_back(std::move(funcDef));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(compUnitList);
		}
#line 1046 "parser.cpp"
    break;

  case 6:
#line 190 "parser.y"
                {
			std::vector<unique_ptr<Exp>> arrayDimList;
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 1055 "parser.cpp"
    break;

  case 7:
#line 195 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 1064 "parser.cpp"
    break;

  case 8:
#line 200 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			arrayDimList.insert(arrayDimList.begin(),nullptr);
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 1074 "parser.cpp"
    break;

  case 9:
#line 208 "parser.y"
                {
			std::vector<unique_ptr<Exp>> arrayDimSubList;
			unique_ptr<Exp> exp=std::move(yystack_[1].value.as <  unique_ptr<Exp>  > ());
			arrayDimSubList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimSubList);
		}
#line 1085 "parser.cpp"
    break;

  case 10:
#line 215 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimSubList=yystack_[3].value.as <  std::vector<unique_ptr<Exp>>  > ();
			unique_ptr<Exp> exp=std::move(yystack_[1].value.as <  unique_ptr<Exp>  > ());
			arrayDimSubList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimSubList);
		}
#line 1096 "parser.cpp"
    break;

  case 11:
#line 223 "parser.y"
              {yylhs.value.as <  unique_ptr<Type>  > ()=std::make_unique<Type>(yystack_[0].value.as < std::string > ());}
#line 1102 "parser.cpp"
    break;

  case 12:
#line 224 "parser.y"
               {yylhs.value.as <  unique_ptr<Type>  > ()=std::make_unique<Type>(yystack_[0].value.as < std::string > ());}
#line 1108 "parser.cpp"
    break;

  case 13:
#line 227 "parser.y"
                        {yylhs.value.as <  std::unique_ptr<Decl> > ()=std::move(yystack_[0].value.as <  unique_ptr<ValueDecl>  > ());}
#line 1114 "parser.cpp"
    break;

  case 14:
#line 231 "parser.y"
                {

		}
#line 1122 "parser.cpp"
    break;

  case 15:
#line 235 "parser.y"
                {
			unique_ptr<Type> type=std::move(yystack_[2].value.as <  unique_ptr<Type>  > ());
			std::vector<unique_ptr<ValueDef>> &valueDefList=yystack_[1].value.as <  std::vector<unique_ptr<ValueDef>>  > ();
			auto v=make_unique<ValueDecl>(std::move(type),std::move(valueDefList));
			yylhs.value.as <  unique_ptr<ValueDecl>  > ()=std::move(v);
		}
#line 1133 "parser.cpp"
    break;

  case 16:
#line 244 "parser.y"
                {
			unique_ptr<ValueDef> valueDef=std::move(yystack_[0].value.as <  unique_ptr<ValueDef>  > ());
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ()=std::vector<unique_ptr<ValueDef>>();
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ().push_back(std::move(valueDef));
		}
#line 1143 "parser.cpp"
    break;

  case 17:
#line 250 "parser.y"
                {
			unique_ptr<ValueDef> &valueDef=yystack_[0].value.as <  unique_ptr<ValueDef>  > ();
			std::vector<unique_ptr<ValueDef>> &varDefList=yystack_[2].value.as <  std::vector<unique_ptr<ValueDef>>  > ();
			varDefList.push_back(std::move(valueDef));
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ()=std::move(varDefList);
		}
#line 1154 "parser.cpp"
    break;

  case 18:
#line 259 "parser.y"
                {
			unique_ptr<Ident> &ident=yystack_[1].value.as <  unique_ptr<Ident>  > ();
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			yylhs.value.as <  unique_ptr<ValueDef>  > ()=std::move(valueDef);
		}
#line 1165 "parser.cpp"
    break;

  case 19:
#line 266 "parser.y"
                {
			unique_ptr<Ident> ident=std::move(yystack_[3].value.as <  unique_ptr<Ident>  > ());
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[2].value.as <  std::vector<unique_ptr<Exp>>  > ();
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			yylhs.value.as <  unique_ptr<ValueDef>  > ()=std::move(valueDef);
		}
#line 1176 "parser.cpp"
    break;

  case 20:
#line 273 "parser.y"
                {

		}
#line 1184 "parser.cpp"
    break;

  case 21:
#line 278 "parser.y"
                  {}
#line 1190 "parser.cpp"
    break;

  case 22:
#line 279 "parser.y"
                                     {}
#line 1196 "parser.cpp"
    break;

  case 23:
#line 283 "parser.y"
                {
		}
#line 1203 "parser.cpp"
    break;

  case 24:
#line 286 "parser.y"
                {
		}
#line 1210 "parser.cpp"
    break;

  case 25:
#line 289 "parser.y"
                {
		}
#line 1217 "parser.cpp"
    break;

  case 26:
#line 294 "parser.y"
        {
		std::unique_ptr<Type> &type=yystack_[4].value.as <  unique_ptr<Type>  > ();
		std::unique_ptr<Ident> &ident=yystack_[3].value.as <  unique_ptr<Ident>  > ();
		std::unique_ptr<BlockStmt> &block=yystack_[0].value.as <  std::unique_ptr<BlockStmt>  > ();
		auto funcDef=std::make_unique<FuncDef>(std::move(type),std::move(ident),std::move(block));
		yylhs.value.as <  std::unique_ptr<FuncDef>  > ()=std::move(funcDef);
	}
#line 1229 "parser.cpp"
    break;

  case 27:
#line 302 "parser.y"
                {
			std::unique_ptr<Type> &type=yystack_[5].value.as <  unique_ptr<Type>  > ();
			std::unique_ptr<Ident> &ident=yystack_[4].value.as <  unique_ptr<Ident>  > ();
			std::vector<std::unique_ptr<FuncParamDecl>> &funcParamDeclList=yystack_[2].value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ();
			std::unique_ptr<BlockStmt> &block=yystack_[0].value.as <  std::unique_ptr<BlockStmt>  > ();
			auto funcDef=std::make_unique<FuncDef>(std::move(type),std::move(ident),std::move(funcParamDeclList),std::move(block));
			yylhs.value.as <  std::unique_ptr<FuncDef>  > ()=std::move(funcDef);
		}
#line 1242 "parser.cpp"
    break;

  case 28:
#line 313 "parser.y"
                {
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ()=std::vector<unique_ptr<FuncParamDecl>>();
			unique_ptr<FuncParamDecl> funcParamDecl=std::move(yystack_[0].value.as <  unique_ptr<FuncParamDecl>  > ());
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ().push_back(std::move(funcParamDecl));
		}
#line 1252 "parser.cpp"
    break;

  case 29:
#line 319 "parser.y"
                {
			std::vector<unique_ptr<FuncParamDecl>> &funcParamDeclList=yystack_[2].value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ();
			unique_ptr<FuncParamDecl> funcParamDecl=std::move(yystack_[0].value.as <  unique_ptr<FuncParamDecl>  > ());
			funcParamDeclList.push_back(std::move(funcParamDecl));
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ()=std::move(funcParamDeclList);
		}
#line 1263 "parser.cpp"
    break;

  case 30:
#line 328 "parser.y"
                {
			unique_ptr<Type> type=std::move(yystack_[1].value.as <  unique_ptr<Type>  > ());
			unique_ptr<Ident> ident=std::move(yystack_[0].value.as <  unique_ptr<Ident>  > ());
			unique_ptr<FuncParamDecl> funcParamDecl=make_unique<FuncParamDecl>(std::move(type),std::move(ident));
			yylhs.value.as <  unique_ptr<FuncParamDecl>  > ()=std::move(funcParamDecl);
		}
#line 1274 "parser.cpp"
    break;

  case 31:
#line 336 "parser.y"
                  {yylhs.value.as <  std::unique_ptr<BlockStmt>  > ()=std::move(std::make_unique<BlockStmt>());}
#line 1280 "parser.cpp"
    break;

  case 32:
#line 338 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			auto block=std::make_unique<BlockStmt>(std::move(blockItemList));
			yylhs.value.as <  std::unique_ptr<BlockStmt>  > ()=std::move(block);
		}
#line 1290 "parser.cpp"
    break;

  case 33:
#line 346 "parser.y"
                {
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::vector<std::unique_ptr<ASTUnit>>();
			std::unique_ptr<ASTUnit> decl=std::move(yystack_[0].value.as <  std::unique_ptr<Decl> > ());
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ().push_back(std::move(decl));
		}
#line 1300 "parser.cpp"
    break;

  case 34:
#line 352 "parser.y"
                {
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::vector<std::unique_ptr<ASTUnit>>();
			std::unique_ptr<ASTUnit> stmt=std::move(yystack_[0].value.as <  std::unique_ptr<Stmt>  > ());
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ().push_back(std::move(stmt));
		}
#line 1310 "parser.cpp"
    break;

  case 35:
#line 358 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			std::unique_ptr<ASTUnit> unit=std::move(yystack_[0].value.as <  std::unique_ptr<Decl> > ());
			blockItemList.push_back(std::move(unit));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(blockItemList);
		}
#line 1321 "parser.cpp"
    break;

  case 36:
#line 365 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			std::unique_ptr<ASTUnit> unit=std::move(yystack_[0].value.as <  std::unique_ptr<Stmt>  > ());
			blockItemList.push_back(std::move(unit));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(blockItemList);
		}
#line 1332 "parser.cpp"
    break;

  case 37:
#line 374 "parser.y"
                {
			std::unique_ptr<Ident> &ident=yystack_[3].value.as <  unique_ptr<Ident>  > ();
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto assignStmt=std::make_unique<AssignStmt>(std::move(ident),std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(assignStmt);
		}
#line 1343 "parser.cpp"
    break;

  case 38:
#line 381 "parser.y"
                {
			auto emptyStmt=std::make_unique<EmptyStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(emptyStmt);
		}
#line 1352 "parser.cpp"
    break;

  case 39:
#line 386 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto expStmt=std::make_unique<ExpStmt>(std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(expStmt);
		}
#line 1362 "parser.cpp"
    break;

  case 40:
#line 391 "parser.y"
              {yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(yystack_[0].value.as <  std::unique_ptr<BlockStmt>  > ());}
#line 1368 "parser.cpp"
    break;

  case 41:
#line 393 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[2].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &ifBody=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			std::unique_ptr<IfStmt> ifStmt=std::make_unique<IfStmt>(std::move(cond),std::move(ifBody));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(ifStmt);
		}
#line 1379 "parser.cpp"
    break;

  case 42:
#line 400 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[4].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &ifBody=yystack_[2].value.as <  std::unique_ptr<Stmt>  > ();
			std::unique_ptr<Stmt> &elseBody=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			auto ifStmt=std::make_unique<IfStmt>(std::move(cond),std::move(ifBody),std::move(elseBody));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(ifStmt);
		}
#line 1391 "parser.cpp"
    break;

  case 43:
#line 408 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[2].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &body=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			auto whileStmt=std::make_unique<WhileStmt>(std::move(cond),std::move(body));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(whileStmt);
		}
#line 1402 "parser.cpp"
    break;

  case 44:
#line 415 "parser.y"
                {
			auto breakStmt=std::make_unique<BreakStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(breakStmt);
		}
#line 1411 "parser.cpp"
    break;

  case 45:
#line 420 "parser.y"
                {
			auto continueStmt=std::make_unique<ContinueStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(continueStmt);
		}
#line 1420 "parser.cpp"
    break;

  case 46:
#line 425 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto returnStmt=std::make_unique<ReturnStmt>(std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(returnStmt);
		}
#line 1430 "parser.cpp"
    break;

  case 47:
#line 431 "parser.y"
                {
			auto returnStmt=std::make_unique<ReturnStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(returnStmt);
		}
#line 1439 "parser.cpp"
    break;

  case 48:
#line 438 "parser.y"
                {
			std::string identStr=yystack_[0].value.as < std::string > ();
			auto ident=std::make_unique<Ident>(identStr);
			yylhs.value.as <  unique_ptr<Ident>  > ()=std::move(ident);
		}
#line 1449 "parser.cpp"
    break;

  case 49:
#line 446 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=std::make_unique<ConstantInt>(ConstantInt::ConstantIntType::Decimal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1459 "parser.cpp"
    break;

  case 50:
#line 452 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Octal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1469 "parser.cpp"
    break;

  case 51:
#line 458 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Hexadecimal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1479 "parser.cpp"
    break;

  case 52:
#line 466 "parser.y"
                {
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::vector<unique_ptr<Exp>>();
			std::unique_ptr<Exp> &exp=yystack_[0].value.as <  unique_ptr<Exp>  > ();
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ().push_back(std::move(exp));
		}
#line 1489 "parser.cpp"
    break;

  case 53:
#line 472 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[0].value.as <  unique_ptr<Exp>  > ();
			std::vector<std::unique_ptr<Exp>> &funcParamList=yystack_[2].value.as <  std::vector<unique_ptr<Exp>>  > ();
			funcParamList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(funcParamList);
		}
#line 1500 "parser.cpp"
    break;

  case 54:
#line 480 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Mul);}
#line 1506 "parser.cpp"
    break;

  case 55:
#line 481 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Div);}
#line 1512 "parser.cpp"
    break;

  case 56:
#line 482 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Mod);}
#line 1518 "parser.cpp"
    break;

  case 57:
#line 483 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Add);}
#line 1524 "parser.cpp"
    break;

  case 58:
#line 484 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Sub);}
#line 1530 "parser.cpp"
    break;

  case 59:
#line 485 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),B);}
#line 1536 "parser.cpp"
    break;

  case 60:
#line 486 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),A);}
#line 1542 "parser.cpp"
    break;

  case 61:
#line 487 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Be);}
#line 1548 "parser.cpp"
    break;

  case 62:
#line 488 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Ae);}
#line 1554 "parser.cpp"
    break;

  case 63:
#line 489 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),E);}
#line 1560 "parser.cpp"
    break;

  case 64:
#line 490 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Ne);}
#line 1566 "parser.cpp"
    break;

  case 65:
#line 491 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),And);}
#line 1572 "parser.cpp"
    break;

  case 66:
#line 492 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Or);}
#line 1578 "parser.cpp"
    break;

  case 67:
#line 493 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Equal);}
#line 1584 "parser.cpp"
    break;

  case 68:
#line 494 "parser.y"
                        {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(yystack_[1].value.as <  unique_ptr<Exp>  > ());}
#line 1590 "parser.cpp"
    break;

  case 69:
#line 495 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::Ident,std::move(yystack_[0].value.as <  unique_ptr<Ident>  > ())));}
#line 1596 "parser.cpp"
    break;

  case 70:
#line 496 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::ConstantInt,std::move(yystack_[0].value.as <  unique_ptr<ConstantInt>  > ())));}
#line 1602 "parser.cpp"
    break;

  case 71:
#line 497 "parser.y"
                        {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<FuncallExp>(std::move(yystack_[2].value.as <  unique_ptr<Ident>  > ())));}
#line 1608 "parser.cpp"
    break;

  case 72:
#line 499 "parser.y"
        {
		std::vector<std::unique_ptr<Exp>> &funcallParamList=yystack_[1].value.as <  std::vector<unique_ptr<Exp>>  > ();
		std::unique_ptr<Ident> &ident=yystack_[3].value.as <  unique_ptr<Ident>  > ();
		auto funcallExp=make_unique<FuncallExp>(std::move(ident),std::move(funcallParamList));
		yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(funcallExp);
	}
#line 1619 "parser.cpp"
    break;

  case 73:
#line 505 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Add,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1625 "parser.cpp"
    break;

  case 74:
#line 506 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Sub,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1631 "parser.cpp"
    break;

  case 75:
#line 507 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Not,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1637 "parser.cpp"
    break;


#line 1641 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -84;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -84,     2,   136,   -84,    -6,   -84,   -84,   -14,   -84,   -84,
     -84,   -14,   -84,    71,   -84,    23,    74,    18,   -14,   -84,
     270,    10,    43,    50,   -84,   -84,    84,   294,   294,   294,
     294,   -84,   -84,   -84,    87,   -84,   313,   104,   -14,     7,
     -84,    85,   294,   294,    50,   365,   132,   132,   -84,   276,
     -84,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,    67,   -84,   -84,    -6,   104,
     174,   -84,   430,   340,   -84,   -84,    19,   430,   228,   132,
     132,   -84,   -84,   -84,    93,    93,    93,    93,   259,   259,
      38,   444,   -84,   -84,    89,   103,   109,   115,   168,   -14,
     -84,   -84,   125,   -84,    24,   197,   -84,   -84,   -84,     3,
     430,   -84,   294,   -84,   294,   294,   -84,   -84,   -84,   212,
     -84,   -84,   -84,   294,   -84,    85,   -84,   430,   390,   415,
     -84,   243,   -84,   430,   149,   149,   -84,   110,   -84,   149,
     -84
  };

  const signed char
  Parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,    11,    12,     0,     4,    13,
       5,     0,    48,     0,    16,     6,     0,     6,     0,    15,
       0,     0,    18,     7,    14,    17,     0,     0,     0,     0,
       0,    49,    50,    51,    69,    70,     0,     0,     0,     0,
      28,     0,     0,     0,     8,     0,    73,    74,    75,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    30,     0,     0,
       0,    20,    19,     0,    68,    71,     0,    52,    67,    57,
      58,    54,    55,    56,    59,    60,    61,    62,    63,    64,
      65,    66,    38,    31,     0,     0,     0,     0,     0,     0,
      33,    40,     0,    34,    69,     0,    29,    27,    21,     0,
      23,    10,     0,    72,     0,     0,    44,    45,    47,     0,
      32,    35,    36,     0,    39,     0,    22,    53,     0,     0,
      46,     0,    25,    24,     0,     0,    37,    41,    43,     0,
      42
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -84,   -84,   -84,   -84,   107,    -1,   -49,   -84,   124,   118,
      16,   -84,   -84,   -84,    91,   -19,   -84,   -83,    -7,   -84,
     -84,   -15
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,     2,    22,    23,    38,     8,     9,    13,    14,
      71,   109,    10,    39,    40,   101,   102,   103,    34,    35,
      76,   105
  };

  const unsigned char
  Parser::yytable_[] =
  {
      15,     7,     3,    11,    17,    36,   125,     5,     6,   126,
      68,    17,    45,    46,    47,    48,   100,    69,    66,   122,
      37,    12,   112,     5,     6,    20,    72,    73,    36,   113,
      20,    67,    21,    49,    77,   123,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
     107,   137,   138,   121,    41,   110,   140,    42,   104,    52,
      53,    54,    55,    56,    99,    57,    58,    59,    60,    61,
      62,    92,    65,    93,    18,    19,    27,    18,    24,     4,
       5,     6,    94,   119,    95,    96,    97,    98,    28,    29,
      70,    43,    17,    30,    27,   104,    49,   127,   114,   128,
     129,    99,    12,    31,    32,    33,    28,    29,   131,    65,
     133,    30,   115,   116,    52,    53,    54,    55,    56,   117,
      12,    31,    32,    33,    61,    62,   139,   104,   104,    92,
      65,   120,   104,    44,    27,    16,    25,     4,     5,     6,
      94,   132,    95,    96,    97,    98,    28,    29,     4,     5,
       6,    30,     0,    92,    65,    54,    55,    56,    27,   106,
      12,    31,    32,    33,    94,     0,    95,    96,    97,    98,
      28,    29,   118,     0,     0,    30,     0,    27,     0,     0,
     108,     0,     0,    27,    12,    31,    32,    33,     0,    28,
      29,     0,     0,     0,    30,    28,    29,     0,     0,     0,
      30,   124,     0,    12,    31,    32,    33,     0,    51,    12,
      31,    32,    33,     0,     0,     0,   130,     0,    52,    53,
      54,    55,    56,    51,    57,    58,    59,    60,    61,    62,
      63,    64,     0,    52,    53,    54,    55,    56,     0,    57,
      58,    59,    60,    61,    62,    63,    64,   136,     0,    52,
      53,    54,    55,    56,    51,    57,    58,    59,    60,    61,
      62,    63,    64,     0,    52,    53,    54,    55,    56,     0,
      57,    58,    59,    60,    61,    62,    63,    64,    26,    27,
      52,    53,    54,    55,    56,    27,    75,     0,     0,     0,
       0,    28,    29,     0,     0,     0,    30,    28,    29,     0,
       0,     0,    30,    27,     0,    12,    31,    32,    33,     0,
       0,    12,    31,    32,    33,    28,    29,     0,     0,     0,
      30,    50,     0,     0,    51,     0,     0,     0,     0,    12,
      31,    32,    33,     0,    52,    53,    54,    55,    56,     0,
      57,    58,    59,    60,    61,    62,    63,    64,   111,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    53,    54,    55,    56,     0,    57,    58,    59,
      60,    61,    62,    63,    64,    74,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,     0,    57,    58,    59,    60,    61,    62,    63,    64,
     134,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    53,    54,    55,    56,     0,    57,    58,    59,
      60,    61,    62,    63,    64,   135,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,    51,    57,    58,    59,    60,    61,    62,    63,    64,
       0,    52,    53,    54,    55,    56,     0,    57,    58,    59,
      60,    61,    62,    63,    64,    52,    53,    54,    55,    56,
       0,    57,    58,    59,    60,    61,    62,    63
  };

  const short
  Parser::yycheck_[] =
  {
       7,     2,     0,     4,    11,    20,     3,    13,    14,     6,
       3,    18,    27,    28,    29,    30,    65,    10,    37,   102,
      10,    35,     3,    13,    14,     7,    41,    42,    43,    10,
       7,    38,     9,     9,    49,    11,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      69,   134,   135,   102,    11,    70,   139,     7,    65,    21,
      22,    23,    24,    25,    65,    27,    28,    29,    30,    31,
      32,     4,     5,     6,     3,     4,     9,     3,     4,    12,
      13,    14,    15,    98,    17,    18,    19,    20,    21,    22,
       5,     7,    99,    26,     9,   102,     9,   112,     9,   114,
     115,   102,    35,    36,    37,    38,    21,    22,   123,     5,
     125,    26,     9,     4,    21,    22,    23,    24,    25,     4,
      35,    36,    37,    38,    31,    32,    16,   134,   135,     4,
       5,     6,   139,    26,     9,    11,    18,    12,    13,    14,
      15,   125,    17,    18,    19,    20,    21,    22,    12,    13,
      14,    26,    -1,     4,     5,    23,    24,    25,     9,    68,
      35,    36,    37,    38,    15,    -1,    17,    18,    19,    20,
      21,    22,     4,    -1,    -1,    26,    -1,     9,    -1,    -1,
       6,    -1,    -1,     9,    35,    36,    37,    38,    -1,    21,
      22,    -1,    -1,    -1,    26,    21,    22,    -1,    -1,    -1,
      26,     4,    -1,    35,    36,    37,    38,    -1,    11,    35,
      36,    37,    38,    -1,    -1,    -1,     4,    -1,    21,    22,
      23,    24,    25,    11,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,     4,    -1,    21,
      22,    23,    24,    25,    11,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,     8,     9,
      21,    22,    23,    24,    25,     9,    10,    -1,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    26,    21,    22,    -1,
      -1,    -1,    26,     9,    -1,    35,    36,    37,    38,    -1,
      -1,    35,    36,    37,    38,    21,    22,    -1,    -1,    -1,
      26,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    11,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    31,    32,    33
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    41,    42,     0,    12,    13,    14,    45,    46,    47,
      52,    45,    35,    48,    49,    58,    48,    58,     3,     4,
       7,     9,    43,    44,     4,    49,     8,     9,    21,    22,
      26,    36,    37,    38,    58,    59,    61,    10,    45,    53,
      54,    11,     7,     7,    44,    61,    61,    61,    61,     9,
       8,    11,    21,    22,    23,    24,    25,    27,    28,    29,
      30,    31,    32,    33,    34,     5,    55,    58,     3,    10,
       5,    50,    61,    61,    10,    10,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,     4,     6,    15,    17,    18,    19,    20,    45,
      46,    55,    56,    57,    58,    61,    54,    55,     6,    51,
      61,     8,     3,    10,     9,     9,     4,     4,     4,    61,
       6,    46,    57,    11,     4,     3,     6,    61,    61,    61,
       4,    61,    50,    61,    10,    10,     4,    57,    57,    16,
      57
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    40,    41,    42,    42,    42,    43,    43,    43,    44,
      44,    45,    45,    46,    47,    47,    48,    48,    49,    49,
      49,    50,    50,    51,    51,    51,    52,    52,    53,    53,
      54,    55,    55,    56,    56,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    59,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     0,     1,     3,     3,
       4,     1,     1,     1,     4,     3,     1,     3,     2,     4,
       4,     2,     3,     1,     3,     3,     5,     6,     1,     3,
       2,     2,     3,     1,     1,     2,     2,     4,     1,     2,
       1,     5,     7,     5,     2,     2,     3,     2,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     4,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"文件结尾\"", "error", "$undefined", "\"逗号\"", "\"分号\"",
  "\"左大括号\"", "\"右大括号\"", "\"左中括号\"",
  "\"右中括号\"", "\"左小括号\"", "\"右小括号\"", "\"等号\"",
  "\"const关键字\"", "\"int关键字\"", "\"void关键字\"",
  "\"if关键字\"", "\"else关键字\"", "\"while关键字\"",
  "\"break关键字\"", "\"continue关键字\"", "\"return关键字\"",
  "\"加号\"", "\"减号\"", "\"乘号\"", "\"除号\"", "\"余号\"",
  "\"感叹号\"", "\"小于号\"", "\"大于号\"", "\"小于等于号\"",
  "\"大于等于号\"", "\"等于等于号\"", "\"不等于号\"",
  "\"与号\"", "\"或号\"", "\"标识符\"", "\"十进制常数\"",
  "\"八进制常数\"", "\"十六进制常数\"", "T_LOWER_THEN_ELSE",
  "$accept", "CompUnit", "CompUnitList", "ArrayDimList", "ArrayDimSubList",
  "BType", "Decl", "ValueDecl", "ValueDefList", "ValueDef",
  "ArrayAssignList", "ArrayAssignSubList", "FuncDef", "FuncParamDeclList",
  "FuncParamDecl", "Block", "BlockItemList", "Stmt", "Ident", "Number",
  "FuncallParamList", "Exp", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   159,   159,   169,   173,   180,   189,   194,   199,   207,
     214,   223,   224,   227,   230,   234,   243,   249,   258,   265,
     272,   278,   279,   282,   285,   288,   293,   301,   312,   318,
     327,   336,   337,   345,   351,   357,   364,   373,   380,   385,
     391,   392,   399,   407,   414,   419,   424,   430,   437,   445,
     451,   457,   465,   471,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   505,   506,   507
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 14 "parser.y"
} //  saltyfish 
#line 2195 "parser.cpp"

#line 508 "parser.y"

namespace saltyfish
{
	// Report an error to the user.
	auto Parser::error (const saltyfish::location &loc,const std::string& msg) -> void
	{
		std::cerr << msg <<"     location:"<<loc<< '\n';
	}
}
