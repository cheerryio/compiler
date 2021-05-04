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
#line 61 "parser.y"

		#include <iostream>
		#include "scanner.hpp"
		#include "parser.hpp"
		#include "location.hh"
		#include "driver.hpp"
		using namespace saltyfish;

#line 47 "parser.cpp"




#include "parser.hpp"


// Unqualified %code blocks.
#line 71 "parser.y"

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

      case 45: // Decl
        value.YY_MOVE_OR_COPY<  std::unique_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 57: // Stmt
        value.YY_MOVE_OR_COPY<  std::unique_ptr<Stmt>  > (YY_MOVE (that.value));
        break;

      case 56: // BlockItemList
        value.YY_MOVE_OR_COPY<  std::vector<std::unique_ptr<ASTUnit>>  > (YY_MOVE (that.value));
        break;

      case 42: // ArrayDimList
      case 43: // ArrayDimSubList
      case 60: // FuncallParamList
        value.YY_MOVE_OR_COPY<  std::vector<unique_ptr<Exp>>  > (YY_MOVE (that.value));
        break;

      case 53: // FuncParamDeclList
        value.YY_MOVE_OR_COPY<  std::vector<unique_ptr<FuncParamDecl>>  > (YY_MOVE (that.value));
        break;

      case 47: // ValueDefList
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

      case 44: // BType
        value.YY_MOVE_OR_COPY<  unique_ptr<Type>  > (YY_MOVE (that.value));
        break;

      case 46: // ValueDecl
        value.YY_MOVE_OR_COPY<  unique_ptr<ValueDecl>  > (YY_MOVE (that.value));
        break;

      case 48: // ValueDef
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

      case 45: // Decl
        value.move<  std::unique_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 57: // Stmt
        value.move<  std::unique_ptr<Stmt>  > (YY_MOVE (that.value));
        break;

      case 56: // BlockItemList
        value.move<  std::vector<std::unique_ptr<ASTUnit>>  > (YY_MOVE (that.value));
        break;

      case 42: // ArrayDimList
      case 43: // ArrayDimSubList
      case 60: // FuncallParamList
        value.move<  std::vector<unique_ptr<Exp>>  > (YY_MOVE (that.value));
        break;

      case 53: // FuncParamDeclList
        value.move<  std::vector<unique_ptr<FuncParamDecl>>  > (YY_MOVE (that.value));
        break;

      case 47: // ValueDefList
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

      case 44: // BType
        value.move<  unique_ptr<Type>  > (YY_MOVE (that.value));
        break;

      case 46: // ValueDecl
        value.move<  unique_ptr<ValueDecl>  > (YY_MOVE (that.value));
        break;

      case 48: // ValueDef
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

      case 45: // Decl
        value.copy<  std::unique_ptr<Decl> > (that.value);
        break;

      case 57: // Stmt
        value.copy<  std::unique_ptr<Stmt>  > (that.value);
        break;

      case 56: // BlockItemList
        value.copy<  std::vector<std::unique_ptr<ASTUnit>>  > (that.value);
        break;

      case 42: // ArrayDimList
      case 43: // ArrayDimSubList
      case 60: // FuncallParamList
        value.copy<  std::vector<unique_ptr<Exp>>  > (that.value);
        break;

      case 53: // FuncParamDeclList
        value.copy<  std::vector<unique_ptr<FuncParamDecl>>  > (that.value);
        break;

      case 47: // ValueDefList
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

      case 44: // BType
        value.copy<  unique_ptr<Type>  > (that.value);
        break;

      case 46: // ValueDecl
        value.copy<  unique_ptr<ValueDecl>  > (that.value);
        break;

      case 48: // ValueDef
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

      case 45: // Decl
        value.move<  std::unique_ptr<Decl> > (that.value);
        break;

      case 57: // Stmt
        value.move<  std::unique_ptr<Stmt>  > (that.value);
        break;

      case 56: // BlockItemList
        value.move<  std::vector<std::unique_ptr<ASTUnit>>  > (that.value);
        break;

      case 42: // ArrayDimList
      case 43: // ArrayDimSubList
      case 60: // FuncallParamList
        value.move<  std::vector<unique_ptr<Exp>>  > (that.value);
        break;

      case 53: // FuncParamDeclList
        value.move<  std::vector<unique_ptr<FuncParamDecl>>  > (that.value);
        break;

      case 47: // ValueDefList
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

      case 44: // BType
        value.move<  unique_ptr<Type>  > (that.value);
        break;

      case 46: // ValueDecl
        value.move<  unique_ptr<ValueDecl>  > (that.value);
        break;

      case 48: // ValueDef
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

      case 45: // Decl
        yylhs.value.emplace<  std::unique_ptr<Decl> > ();
        break;

      case 57: // Stmt
        yylhs.value.emplace<  std::unique_ptr<Stmt>  > ();
        break;

      case 56: // BlockItemList
        yylhs.value.emplace<  std::vector<std::unique_ptr<ASTUnit>>  > ();
        break;

      case 42: // ArrayDimList
      case 43: // ArrayDimSubList
      case 60: // FuncallParamList
        yylhs.value.emplace<  std::vector<unique_ptr<Exp>>  > ();
        break;

      case 53: // FuncParamDeclList
        yylhs.value.emplace<  std::vector<unique_ptr<FuncParamDecl>>  > ();
        break;

      case 47: // ValueDefList
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

      case 44: // BType
        yylhs.value.emplace<  unique_ptr<Type>  > ();
        break;

      case 46: // ValueDecl
        yylhs.value.emplace<  unique_ptr<ValueDecl>  > ();
        break;

      case 48: // ValueDef
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
  case 5:
#line 157 "parser.y"
                {
			std::vector<unique_ptr<Exp>> arrayDimList;
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 968 "parser.cpp"
    break;

  case 6:
#line 162 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 977 "parser.cpp"
    break;

  case 7:
#line 167 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			unique_ptr<Exp> f(nullptr);
			arrayDimList.insert(arrayDimList.begin(),std::move(f));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimList);
		}
#line 988 "parser.cpp"
    break;

  case 8:
#line 176 "parser.y"
                {
			std::vector<unique_ptr<Exp>> arrayDimSubList;
			unique_ptr<Exp> exp=std::move(yystack_[1].value.as <  unique_ptr<Exp>  > ());
			arrayDimSubList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimSubList);
		}
#line 999 "parser.cpp"
    break;

  case 9:
#line 183 "parser.y"
                {
			std::vector<unique_ptr<Exp>> &arrayDimSubList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			unique_ptr<Exp> exp=std::move(yystack_[2].value.as <  unique_ptr<Exp>  > ());
			arrayDimSubList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(arrayDimSubList);
		}
#line 1010 "parser.cpp"
    break;

  case 10:
#line 192 "parser.y"
                {
			std:string &typeStr=yystack_[0].value.as < std::string > ();
			yylhs.value.as <  unique_ptr<Type>  > ()=make_unique<Type>(typeStr);
		}
#line 1019 "parser.cpp"
    break;

  case 11:
#line 198 "parser.y"
                        {yylhs.value.as <  std::unique_ptr<Decl> > ()=std::move(yystack_[0].value.as <  unique_ptr<ValueDecl>  > ());}
#line 1025 "parser.cpp"
    break;

  case 12:
#line 202 "parser.y"
                {

		}
#line 1033 "parser.cpp"
    break;

  case 13:
#line 206 "parser.y"
                {
			unique_ptr<Type> type=std::move(yystack_[2].value.as <  unique_ptr<Type>  > ());
			std::vector<unique_ptr<ValueDef>> &valueDefList=yystack_[1].value.as <  std::vector<unique_ptr<ValueDef>>  > ();
			auto v=make_unique<ValueDecl>(std::move(type),std::move(valueDefList));
			yylhs.value.as <  unique_ptr<ValueDecl>  > ()=std::move(v);
		}
#line 1044 "parser.cpp"
    break;

  case 14:
#line 215 "parser.y"
                {
			unique_ptr<ValueDef> valueDef=std::move(yystack_[0].value.as <  unique_ptr<ValueDef>  > ());
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ()=std::vector<unique_ptr<ValueDef>>();
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ().push_back(std::move(valueDef));
		}
#line 1054 "parser.cpp"
    break;

  case 15:
#line 221 "parser.y"
                {
			unique_ptr<ValueDef> &valueDef=yystack_[0].value.as <  unique_ptr<ValueDef>  > ();
			std::vector<unique_ptr<ValueDef>> &varDefList=yystack_[2].value.as <  std::vector<unique_ptr<ValueDef>>  > ();
			varDefList.push_back(std::move(valueDef));
			yylhs.value.as <  std::vector<unique_ptr<ValueDef>>  > ()=std::move(varDefList);
		}
#line 1065 "parser.cpp"
    break;

  case 16:
#line 230 "parser.y"
                {
			unique_ptr<Ident> ident=std::move(yystack_[1].value.as <  unique_ptr<Ident>  > ());
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[0].value.as <  std::vector<unique_ptr<Exp>>  > ();
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			yylhs.value.as <  unique_ptr<ValueDef>  > ()=std::move(valueDef);
		}
#line 1076 "parser.cpp"
    break;

  case 17:
#line 237 "parser.y"
                {
			unique_ptr<Ident> ident=std::move(yystack_[3].value.as <  unique_ptr<Ident>  > ());
			std::vector<unique_ptr<Exp>> &arrayDimList=yystack_[2].value.as <  std::vector<unique_ptr<Exp>>  > ();
			auto valueDef=make_unique<ValueDef>(std::move(ident),std::move(arrayDimList));
			yylhs.value.as <  unique_ptr<ValueDef>  > ()=std::move(valueDef);
		}
#line 1087 "parser.cpp"
    break;

  case 23:
#line 254 "parser.y"
                                    {cout<<"函数无参声明"<<endl;}
#line 1093 "parser.cpp"
    break;

  case 24:
#line 255 "parser.y"
                                     {cout<<"函数无参声明"<<endl;}
#line 1099 "parser.cpp"
    break;

  case 25:
#line 256 "parser.y"
                                                      {cout<<"函数有参声明"<<endl;}
#line 1105 "parser.cpp"
    break;

  case 26:
#line 257 "parser.y"
                                                       {cout<<"函数有参声明"<<endl;}
#line 1111 "parser.cpp"
    break;

  case 27:
#line 261 "parser.y"
                {
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ()=std::vector<unique_ptr<FuncParamDecl>>();
			unique_ptr<FuncParamDecl> funcParamDecl=std::move(yystack_[0].value.as <  unique_ptr<FuncParamDecl>  > ());
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ().push_back(std::move(funcParamDecl));
		}
#line 1121 "parser.cpp"
    break;

  case 28:
#line 267 "parser.y"
                {
			std::vector<unique_ptr<FuncParamDecl>> &funcParamDeclList=yystack_[0].value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ();
			unique_ptr<FuncParamDecl> funcParamDecl=std::move(yystack_[2].value.as <  unique_ptr<FuncParamDecl>  > ());
			funcParamDeclList.push_back(std::move(funcParamDecl));
			yylhs.value.as <  std::vector<unique_ptr<FuncParamDecl>>  > ()=std::move(funcParamDeclList);
		}
#line 1132 "parser.cpp"
    break;

  case 29:
#line 276 "parser.y"
                {
			unique_ptr<Type> type=std::move(yystack_[1].value.as <  unique_ptr<Type>  > ());
			unique_ptr<Ident> ident=std::move(yystack_[0].value.as <  unique_ptr<Ident>  > ());
			unique_ptr<FuncParamDecl> funcParamDecl=make_unique<FuncParamDecl>(std::move(type),std::move(ident));
			yylhs.value.as <  unique_ptr<FuncParamDecl>  > ()=std::move(funcParamDecl);
		}
#line 1143 "parser.cpp"
    break;

  case 30:
#line 284 "parser.y"
                  {yylhs.value.as <  std::unique_ptr<BlockStmt>  > ()=std::move(std::make_unique<BlockStmt>());}
#line 1149 "parser.cpp"
    break;

  case 31:
#line 286 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			auto block=std::make_unique<BlockStmt>(std::move(blockItemList));
			yylhs.value.as <  std::unique_ptr<BlockStmt>  > ()=std::move(block);
		}
#line 1159 "parser.cpp"
    break;

  case 32:
#line 294 "parser.y"
                {
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::vector<std::unique_ptr<ASTUnit>>();
		}
#line 1167 "parser.cpp"
    break;

  case 33:
#line 298 "parser.y"
                {
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::vector<std::unique_ptr<ASTUnit>>();
		}
#line 1175 "parser.cpp"
    break;

  case 34:
#line 302 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			std::unique_ptr<ASTUnit> unit=std::move(yystack_[0].value.as <  std::unique_ptr<Decl> > ());
			blockItemList.push_back(std::move(unit));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(blockItemList);
		}
#line 1186 "parser.cpp"
    break;

  case 35:
#line 309 "parser.y"
                {
			std::vector<std::unique_ptr<ASTUnit>> &blockItemList=yystack_[1].value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ();
			std::unique_ptr<ASTUnit> unit=std::move(yystack_[0].value.as <  std::unique_ptr<Stmt>  > ());
			blockItemList.push_back(std::move(unit));
			yylhs.value.as <  std::vector<std::unique_ptr<ASTUnit>>  > ()=std::move(blockItemList);
		}
#line 1197 "parser.cpp"
    break;

  case 36:
#line 318 "parser.y"
                {
			std::unique_ptr<Ident> &ident=yystack_[3].value.as <  unique_ptr<Ident>  > ();
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto assignStmt=std::make_unique<AssignStmt>(std::move(ident),std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(assignStmt);
		}
#line 1208 "parser.cpp"
    break;

  case 37:
#line 325 "parser.y"
                {
			auto emptyStmt=std::make_unique<EmptyStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(emptyStmt);
		}
#line 1217 "parser.cpp"
    break;

  case 38:
#line 330 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto expStmt=std::make_unique<ExpStmt>(std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(expStmt);
		}
#line 1227 "parser.cpp"
    break;

  case 39:
#line 335 "parser.y"
              {yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(yystack_[0].value.as <  std::unique_ptr<BlockStmt>  > ());}
#line 1233 "parser.cpp"
    break;

  case 40:
#line 337 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[2].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &ifBody=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			std::unique_ptr<IfStmt> ifStmt=std::make_unique<IfStmt>(std::move(cond),std::move(ifBody));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(ifStmt);
		}
#line 1244 "parser.cpp"
    break;

  case 41:
#line 344 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[4].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &ifBody=yystack_[2].value.as <  std::unique_ptr<Stmt>  > ();
			std::unique_ptr<Stmt> &elseBody=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			auto ifStmt=std::make_unique<IfStmt>(std::move(cond),std::move(ifBody),std::move(elseBody));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(ifStmt);
		}
#line 1256 "parser.cpp"
    break;

  case 42:
#line 352 "parser.y"
                {
			std::unique_ptr<Exp> &cond=yystack_[2].value.as <  unique_ptr<Exp>  > ();
			std::unique_ptr<Stmt> &body=yystack_[0].value.as <  std::unique_ptr<Stmt>  > ();
			auto whileStmt=std::make_unique<WhileStmt>(std::move(cond),std::move(body));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(whileStmt);
		}
#line 1267 "parser.cpp"
    break;

  case 43:
#line 359 "parser.y"
                {
			auto breakStmt=std::make_unique<BreakStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(breakStmt);
		}
#line 1276 "parser.cpp"
    break;

  case 44:
#line 364 "parser.y"
                {
			auto continueStmt=std::make_unique<ContinueStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(continueStmt);
		}
#line 1285 "parser.cpp"
    break;

  case 45:
#line 369 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[1].value.as <  unique_ptr<Exp>  > ();
			auto returnStmt=std::make_unique<ReturnStmt>(std::move(exp));
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(returnStmt);
		}
#line 1295 "parser.cpp"
    break;

  case 46:
#line 375 "parser.y"
                {
			auto returnStmt=std::make_unique<ReturnStmt>();
			yylhs.value.as <  std::unique_ptr<Stmt>  > ()=std::move(returnStmt);
		}
#line 1304 "parser.cpp"
    break;

  case 47:
#line 382 "parser.y"
                {
			std::string identStr=yystack_[0].value.as < std::string > ();
			auto ident=std::make_unique<Ident>(identStr);
			yylhs.value.as <  unique_ptr<Ident>  > ()=std::move(ident);
		}
#line 1314 "parser.cpp"
    break;

  case 48:
#line 390 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=std::make_unique<ConstantInt>(ConstantInt::ConstantIntType::Decimal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1324 "parser.cpp"
    break;

  case 49:
#line 396 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Octal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1334 "parser.cpp"
    break;

  case 50:
#line 402 "parser.y"
                {
			int n=yystack_[0].value.as < int > ();
			auto constant=make_unique<ConstantInt>(ConstantInt::ConstantIntType::Hexadecimal,n);
			yylhs.value.as <  unique_ptr<ConstantInt>  > ()=std::move(constant);
		}
#line 1344 "parser.cpp"
    break;

  case 51:
#line 410 "parser.y"
                {
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::vector<unique_ptr<Exp>>();

			std::unique_ptr<Exp> &exp=yystack_[0].value.as <  unique_ptr<Exp>  > ();
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ().push_back(std::move(exp));
		}
#line 1355 "parser.cpp"
    break;

  case 52:
#line 417 "parser.y"
                {
			std::unique_ptr<Exp> &exp=yystack_[0].value.as <  unique_ptr<Exp>  > ();
			std::vector<std::unique_ptr<Exp>> &funcParamList=yystack_[2].value.as <  std::vector<unique_ptr<Exp>>  > ();
			funcParamList.push_back(std::move(exp));
			yylhs.value.as <  std::vector<unique_ptr<Exp>>  > ()=std::move(funcParamList);
		}
#line 1366 "parser.cpp"
    break;

  case 53:
#line 425 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Mul);}
#line 1372 "parser.cpp"
    break;

  case 54:
#line 426 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Div);}
#line 1378 "parser.cpp"
    break;

  case 55:
#line 427 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Mod);}
#line 1384 "parser.cpp"
    break;

  case 56:
#line 428 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Add);}
#line 1390 "parser.cpp"
    break;

  case 57:
#line 429 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Sub);}
#line 1396 "parser.cpp"
    break;

  case 58:
#line 430 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),B);}
#line 1402 "parser.cpp"
    break;

  case 59:
#line 431 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),A);}
#line 1408 "parser.cpp"
    break;

  case 60:
#line 432 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Be);}
#line 1414 "parser.cpp"
    break;

  case 61:
#line 433 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Ae);}
#line 1420 "parser.cpp"
    break;

  case 62:
#line 434 "parser.y"
                                {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),E);}
#line 1426 "parser.cpp"
    break;

  case 63:
#line 435 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Ne);}
#line 1432 "parser.cpp"
    break;

  case 64:
#line 436 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),And);}
#line 1438 "parser.cpp"
    break;

  case 65:
#line 437 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Or);}
#line 1444 "parser.cpp"
    break;

  case 66:
#line 438 "parser.y"
                        {BINARY_EXP(yylhs.value.as <  unique_ptr<Exp>  > (),yystack_[2].value.as <  unique_ptr<Exp>  > (),yystack_[0].value.as <  unique_ptr<Exp>  > (),Equal);}
#line 1450 "parser.cpp"
    break;

  case 67:
#line 439 "parser.y"
                        {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(yystack_[1].value.as <  unique_ptr<Exp>  > ());}
#line 1456 "parser.cpp"
    break;

  case 68:
#line 440 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::Ident,std::move(yystack_[0].value.as <  unique_ptr<Ident>  > ())));}
#line 1462 "parser.cpp"
    break;

  case 69:
#line 441 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<PrimaryExp>(PrimaryExp::PrimaryExpType::ConstantInt,std::move(yystack_[0].value.as <  unique_ptr<ConstantInt>  > ())));}
#line 1468 "parser.cpp"
    break;

  case 70:
#line 442 "parser.y"
                        {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<FuncallExp>(std::move(yystack_[2].value.as <  unique_ptr<Ident>  > ())));}
#line 1474 "parser.cpp"
    break;

  case 71:
#line 444 "parser.y"
        {
		std::vector<std::unique_ptr<Exp>> &funcallParamList=yystack_[1].value.as <  std::vector<unique_ptr<Exp>>  > ();
		std::unique_ptr<Ident> &ident=yystack_[3].value.as <  unique_ptr<Ident>  > ();
		auto funcallExp=make_unique<FuncallExp>(std::move(ident),std::move(funcallParamList));
		yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(funcallExp);
	}
#line 1485 "parser.cpp"
    break;

  case 72:
#line 450 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Add,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1491 "parser.cpp"
    break;

  case 73:
#line 451 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Sub,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1497 "parser.cpp"
    break;

  case 74:
#line 452 "parser.y"
                                {yylhs.value.as <  unique_ptr<Exp>  > ()=std::move(make_unique<UnaryExp>(UnaryExp::UnaryExpType::Not,std::move(yystack_[0].value.as <  unique_ptr<Exp>  > ())));}
#line 1503 "parser.cpp"
    break;


#line 1507 "parser.cpp"

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


  const signed char Parser::yypact_ninf_ = -85;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -85,    12,   -85,    -4,   -85,     2,     2,   -85,   -85,   -85,
       2,   -85,     6,    90,   -85,    22,    92,    49,    -4,     2,
     -85,   296,    17,    51,   -85,   -85,     2,    76,    75,   -85,
      81,   320,   320,   320,   320,   -85,   -85,   -85,    88,   -85,
     339,    94,    95,   204,   -85,    94,    -4,   320,   -85,   364,
      43,    43,   -85,   302,    81,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   126,
     -85,    94,   186,   -85,   429,   -85,   -85,   -85,   -85,    10,
     429,   -85,   443,    43,    43,   -85,   -85,   -85,   457,   457,
     457,   457,    60,    60,    97,   239,   -85,   -85,    99,   100,
     106,   108,   168,     2,   -85,   -85,   161,   -85,    68,   223,
     101,   -85,   -85,   -85,    33,   320,   -85,   320,   320,   -85,
     -85,   -85,   254,   -85,   -85,   -85,   320,   -85,     2,   204,
     -85,   429,   389,   414,   -85,   269,   104,   -85,    54,    54,
     -85,   107,   120,   -85,    94,    54,   -85,   -85
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,     0,     1,     0,    10,     0,     0,     3,    11,     4,
       0,    47,     0,     0,    14,     5,     0,     5,     0,     0,
      13,     0,     0,    16,     6,    12,     0,     0,    27,    15,
       0,     0,     0,     0,     0,    48,    49,    50,    68,    69,
       0,     0,     0,     0,    29,     0,     0,     0,     7,     0,
      72,    73,    74,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,    17,    18,    26,    28,    67,    70,     0,
      51,     9,    66,    56,    57,    53,    54,    55,    58,    59,
      60,    61,    62,    63,    64,    65,    37,    30,     0,     0,
       0,     0,     0,     0,    32,    39,     0,    33,    68,     0,
       0,    25,    19,    21,     0,     0,    71,     0,     0,    43,
      44,    46,     0,    31,    34,    35,     0,    38,     0,     0,
      20,    52,     0,     0,    45,     0,     0,    22,     0,     0,
      36,     0,    40,    42,     0,     0,    24,    41
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -85,   -85,   -85,   -20,     1,   -46,   -85,   127,    85,   -64,
     -85,   -85,   -85,   -11,   -85,   -38,   -85,   -84,    -5,   -85,
     -85,   -15
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,    23,    24,    26,     7,     8,    13,    14,    73,
     114,     9,   110,    27,    28,   105,   106,   107,    38,    39,
      79,   109
  };

  const unsigned char
  Parser::yytable_[] =
  {
      12,    15,     6,    70,    10,    17,    40,    75,   113,     4,
      48,    42,     2,   115,    17,    18,    49,    50,    51,    52,
     116,    44,   125,   104,     3,     4,     5,    41,    74,    21,
       4,    22,    40,   111,    81,    76,   129,    11,    80,   130,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,   142,   143,    21,    74,    96,    69,
     124,   147,    43,    31,   108,   137,    58,    59,    60,    98,
     103,    99,   100,   101,   102,    32,    33,    53,    46,   126,
      34,    56,    57,    58,    59,    60,    45,   122,    47,    11,
      35,    36,    37,    19,    20,    19,    25,    53,    17,    69,
     131,   108,   132,   133,    29,    71,   146,   103,   117,   118,
     119,   135,   120,   141,    74,   128,     0,   144,    56,    57,
      58,    59,    60,   136,    61,    62,    63,    64,    65,    66,
      96,    69,    97,   108,   108,    31,   145,    16,     3,     4,
     108,    98,     0,    99,   100,   101,   102,    32,    33,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,    11,    35,    36,    37,    96,    69,   123,     0,     0,
      31,     0,   121,     3,     4,     0,    98,    31,    99,   100,
     101,   102,    32,    33,     0,     0,     0,    34,     0,    32,
      33,    72,   112,     0,    34,    31,    11,    35,    36,    37,
       0,     0,     0,    11,    35,    36,    37,    32,    33,    72,
       0,     0,    34,    31,     0,     0,     0,     0,     0,     0,
       0,    11,    35,    36,    37,    32,    33,   127,     0,     0,
      34,     0,     0,     0,    55,     0,     0,     0,     0,    11,
      35,    36,    37,     0,    56,    57,    58,    59,    60,     0,
      61,    62,    63,    64,    65,    66,    67,    68,   134,     0,
      56,    57,    58,    59,    60,    55,    61,    62,    63,    64,
      65,    66,    67,   140,     0,    56,    57,    58,    59,    60,
      55,    61,    62,    63,    64,    65,    66,    67,    68,     0,
      56,    57,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    30,    31,     0,     0,     0,     0,
       0,    31,    78,     0,     0,     0,     0,    32,    33,     0,
       0,     0,    34,    32,    33,     0,     0,     0,    34,    31,
       0,    11,    35,    36,    37,     0,     0,    11,    35,    36,
      37,    32,    33,     0,     0,     0,    34,    54,     0,     0,
      55,     0,     0,     0,     0,    11,    35,    36,    37,     0,
      56,    57,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    77,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    58,    59,    60,
       0,    61,    62,    63,    64,    65,    66,    67,    68,   138,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,   139,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    58,    59,    60,
      55,    61,    62,    63,    64,    65,    66,    67,    68,     0,
      56,    57,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    56,    57,    58,    59,    60,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,    65,    66
  };

  const short
  Parser::yycheck_[] =
  {
       5,     6,     1,    41,     3,    10,    21,    45,    72,    13,
      30,    22,     0,     3,    19,     9,    31,    32,    33,    34,
      10,    26,   106,    69,    12,    13,    14,    10,    43,     7,
      13,     9,    47,    71,    54,    46,     3,    35,    53,     6,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   138,   139,     7,    72,     4,     5,
     106,   145,    11,     9,    69,   129,    23,    24,    25,    15,
      69,    17,    18,    19,    20,    21,    22,     9,     3,    11,
      26,    21,    22,    23,    24,    25,    10,   102,     7,    35,
      36,    37,    38,     3,     4,     3,     4,     9,   103,     5,
     115,   106,   117,   118,    19,    10,   144,   106,     9,     9,
       4,   126,     4,     9,   129,    14,    -1,    10,    21,    22,
      23,    24,    25,   128,    27,    28,    29,    30,    31,    32,
       4,     5,     6,   138,   139,     9,    16,    10,    12,    13,
     145,    15,    -1,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,     4,     5,     6,    -1,    -1,
       9,    -1,     4,    12,    13,    -1,    15,     9,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    26,    -1,    21,
      22,     5,     6,    -1,    26,     9,    35,    36,    37,    38,
      -1,    -1,    -1,    35,    36,    37,    38,    21,    22,     5,
      -1,    -1,    26,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    21,    22,     4,    -1,    -1,
      26,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,     4,    -1,
      21,    22,    23,    24,    25,    11,    27,    28,    29,    30,
      31,    32,    33,     4,    -1,    21,    22,    23,    24,    25,
      11,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      21,    22,    23,    24,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,     8,     9,    -1,    -1,    -1,    -1,
      -1,     9,    10,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    26,    21,    22,    -1,    -1,    -1,    26,     9,
      -1,    35,    36,    37,    38,    -1,    -1,    35,    36,    37,
      38,    21,    22,    -1,    -1,    -1,    26,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      21,    22,    23,    24,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      11,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      21,    22,    23,    24,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    31,    32
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    41,     0,    12,    13,    14,    44,    45,    46,    51,
      44,    35,    58,    47,    48,    58,    47,    58,     9,     3,
       4,     7,     9,    42,    43,     4,    44,    53,    54,    48,
       8,     9,    21,    22,    26,    36,    37,    38,    58,    59,
      61,    10,    53,    11,    58,    10,     3,     7,    43,    61,
      61,    61,    61,     9,     8,    11,    21,    22,    23,    24,
      25,    27,    28,    29,    30,    31,    32,    33,    34,     5,
      55,    10,     5,    49,    61,    55,    53,    10,    10,    60,
      61,    43,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,     4,     6,    15,    17,
      18,    19,    20,    44,    45,    55,    56,    57,    58,    61,
      52,    55,     6,    49,    50,     3,    10,     9,     9,     4,
       4,     4,    61,     6,    45,    57,    11,     4,    14,     3,
       6,    61,    61,    61,     4,    61,    58,    49,    10,    10,
       4,     9,    57,    57,    10,    16,    55,    57
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    40,    41,    41,    41,    42,    42,    42,    43,    43,
      44,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      49,    50,    50,    52,    51,    51,    51,    53,    53,    54,
      55,    55,    56,    56,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    59,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     0,     1,     3,     3,     4,
       1,     1,     4,     3,     1,     3,     2,     4,     1,     2,
       3,     1,     3,     0,    11,     6,     6,     1,     3,     2,
       2,     3,     1,     1,     2,     2,     4,     1,     2,     1,
       5,     7,     5,     2,     2,     3,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     4,     2,     2,     2
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
  "$accept", "CompUnit", "ArrayDimList", "ArrayDimSubList", "BType",
  "Decl", "ValueDecl", "ValueDefList", "ValueDef", "InitVal",
  "exp_comma_list", "FuncDef", "$@1", "FuncParamDeclList", "FuncParamDecl",
  "Block", "BlockItemList", "Stmt", "Ident", "Number", "FuncallParamList",
  "Exp", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   151,   151,   152,   153,   156,   161,   166,   175,   182,
     191,   198,   201,   205,   214,   220,   229,   236,   245,   246,
     247,   250,   251,   254,   254,   256,   257,   260,   266,   275,
     284,   285,   293,   297,   301,   308,   317,   324,   329,   335,
     336,   343,   351,   358,   363,   368,   374,   381,   389,   395,
     401,   409,   416,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   450,   451,   452
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
#line 2063 "parser.cpp"

#line 453 "parser.y"

namespace saltyfish
{
	// Report an error to the user.
	auto Parser::error (const saltyfish::location &loc,const std::string& msg) -> void
	{
		std::cerr << msg <<"     location:"<<loc<< '\n';
	}
}
