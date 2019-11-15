/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "grammar.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "ShowTree.h"
extern int yylineno;

// P : parentese ~~ ()
// S : simply bracket ~~ []
// C : curly bracket ~~ {}
// void print_reshi() {
//     SymEntry *s;
//     for(s=reshi; s != NULL; s=s->hh.next) {        
//         switch(s->tag) {
//           case HFLOAT:
//             printf("<type, Id>: < float ,%s >", s->id);
//             printf("\tVal: %f\n", s->u.fval);
//             break;
//           case HINT:
//             printf("<type, Id>: < int ,%s >", s->id);
//             printf("\tVal: %d\n", s->u.ival); 
//           case HID:
//             break;
//             printf("<type, Id>: < id ,%s >", s->id);            
//             break;
//           case HCHR:
//             printf("<type, Id>: < char ,%s >", s->id);
//             printf("\tVal: %c\n", s->u.cval); 
//             break;
//           case HRES_WORD:
//             printf("<type, Id>: < res-word,%s >", s->id);        
//             break;
//         }
//         printf("\t\tl. %d, c. %d\n", s->local.line, s->local.col);
//     }
// }
int lvl = 0;

#line 105 "grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.tab.h".  */
#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "grammar.y" /* yacc.c:355  */

  #include "Function.h"
  // #include "ShowTree.h"

#line 140 "grammar.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERRU = 258,
    CHAR_TYPE = 259,
    INT_TYPE = 260,
    FLOAT_TYPE = 261,
    MAT_TYPE = 262,
    VOID = 263,
    V_INT = 264,
    V_FLOAT = 265,
    ID = 266,
    AHEAD = 267,
    LP = 268,
    RP = 269,
    LS = 270,
    RS = 271,
    LC = 272,
    RC = 273,
    EQ = 274,
    LT = 275,
    GT = 276,
    LE = 277,
    GE = 278,
    NEQ = 279,
    ADD = 280,
    SUB = 281,
    MUL = 282,
    DIV = 283,
    MAT_MUL = 284,
    MAT_POW = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    ADDR = 289,
    IF = 290,
    ELSE = 291,
    WHILE = 292,
    RETURN = 293,
    COPY = 294,
    PRINT = 295,
    READ = 296,
    V_ASCII = 297,
    SEMI_COLON = 298,
    DOT = 299,
    COMMA = 300,
    ATTR = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "grammar.y" /* yacc.c:355  */

  int ival;
  float fval;
  char cval;
  char* sval;
  Dummy* dummy;
  void* vvv;
  Program* _program;
  GlobalStmtList* _globalStmtList;
  GlobalStmt* _globalStmt;
  DefFun* _defFun;
  DeclFun* _declFun;
  DeclVar* _declVar;
  IdArr* _idArr;
  AttrVar* _attrVar;
  SimpleAttr* _simpleAttr;
  IndexAttr* _indexAttr;
  MatAttr* _matAttr;
  NumListList* _numListList;
  NumList* _numList;
  Stmt* _stmt;
  ParamListVoid* _paramListVoid;
  ParamList* _paramList;
  Param* _param;
  Loop* _loop;
  FlowControl* _flowControl;
  Block* _block;
  StmtList* _stmtList;
  Expr* _expr;
  Relop* _relop;
  AddExpr* _addExpr;
  Addop* _addop;
  Term* _term;
  Mulop* _mulop;
  Bin* _bin;
  BinLogi* _binLogi;
  Unary* _unary;
  UnaryOp* _unaryOp;
  Factor* _factor;
  Aux* _aux;
  NumId* _numId;
  Call* _call;
  ArgList* _argList;
  Arg* _arg;
  MatArg* _matArg;
  Ascii* _ascii;
  BaseType* _baseType;
  Num* _num;
  Id* _id;

#line 250 "grammar.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 281 "grammar.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   172,   172,   176,   179,   182,   186,   190,   194,   197,
     200,   203,   206,   210,   213,   216,   219,   222,   225,   228,
     231,   234,   237,   240,   243,   246,   249,   252,   255,   258,
     261,   264,   267,   271,   275,   278,   281,   284,   287,   290,
     294,   297,   300,   303,   306,   309,   312,   315,   318,   321,
     324,   327,   330,   333,   336,   342,   345,   348,   351,   354,
     357,   360,   363,   366,   369,   372,   375,   378,   381,   384,
     387,   390,   393,   396,   399,   402,   405,   408,   411,   414,
     417,   420,   423,   426,   429,   432,   435,   438,   441,   447,
     450,   453,   456,   459,   462,   465,   468,   471,   474,   477,
     480,   483,   486,   489,   492,   495
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERRU", "CHAR_TYPE", "INT_TYPE",
  "FLOAT_TYPE", "MAT_TYPE", "VOID", "V_INT", "V_FLOAT", "ID", "AHEAD",
  "LP", "RP", "LS", "RS", "LC", "RC", "EQ", "LT", "GT", "LE", "GE", "NEQ",
  "ADD", "SUB", "MUL", "DIV", "MAT_MUL", "MAT_POW", "AND", "OR", "NOT",
  "ADDR", "IF", "ELSE", "WHILE", "RETURN", "COPY", "PRINT", "READ",
  "V_ASCII", "SEMI_COLON", "DOT", "COMMA", "ATTR", "'\\''", "$accept",
  "program", "global-stmt-list", "global-stmt", "def-fun", "decl-fun",
  "decl-var", "id-arr", "attr-var", "simple-attr", "index-attr",
  "mat-attr", "num-list-list", "num-list", "stmt", "param-list-void",
  "param-list", "param", "loop", "flow-control", "block", "stmt-list",
  "expr", "relop", "add-expr", "addop", "term", "mulop", "bin", "bin-logi",
  "unary", "unary-op", "factor", "aux", "num-id", "call", "arg-list",
  "arg", "mat-arg", "ascii", "base-type", "num", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    39
};
# endif

#define YYPACT_NINF -130

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-130)))

#define YYTABLE_NINF -8

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     172,  -130,  -130,  -130,   101,    -8,   101,    86,    37,   172,
    -130,   138,  -130,     4,  -130,  -130,  -130,     5,  -130,    47,
      57,   152,     9,    69,    52,  -130,    61,    72,    68,    83,
      68,    90,    67,    79,  -130,  -130,  -130,   129,   132,   205,
    -130,  -130,  -130,  -130,  -130,  -130,   117,  -130,   167,  -130,
    -130,  -130,   201,  -130,   133,    68,   170,  -130,  -130,   178,
     179,   171,   176,    87,  -130,    73,  -130,  -130,  -130,  -130,
     208,   148,    16,    68,    11,   212,   181,   214,  -130,  -130,
    -130,  -130,  -130,   211,   194,   152,   144,    -2,    68,   213,
     162,   164,  -130,   182,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,    68,    68,  -130,  -130,  -130,  -130,    68,
    -130,  -130,    68,  -130,   194,   216,     6,  -130,    17,  -130,
    -130,   217,    22,   218,  -130,  -130,   222,  -130,   200,   101,
    -130,   220,   203,  -130,   224,   221,   223,   152,    42,   225,
    -130,  -130,    99,  -130,  -130,   162,  -130,   160,   176,    87,
    -130,   226,  -130,   219,  -130,   202,   227,   227,   227,   227,
     228,   193,   152,   232,   227,  -130,  -130,  -130,   230,   231,
     162,   195,   233,  -130,  -130,   119,   206,  -130,  -130,   210,
     215,   229,  -130,   207,  -130,   236,  -130,  -130,   144,   209,
     142,  -130,    68,  -130,  -130,   227,   227,    78,  -130,   204,
     237,    68,  -130,   238,  -130,  -130,  -130,  -130,   234,   152,
    -130,  -130,  -130,  -130,   240,   243,   235,  -130
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   101,   102,   103,     0,     0,     0,     0,     0,     2,
       4,     0,     5,     0,    10,    20,    19,     0,    11,     0,
       0,     0,     0,     0,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    42,    41,     0,     0,     0,
       1,     3,     6,     9,     8,    18,    17,    15,     0,   105,
     104,    92,     0,    91,    92,     0,     0,    82,    83,     0,
       0,    59,    67,    71,    77,     0,    81,    85,    90,    86,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      54,    56,    38,    17,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,    21,    63,    65,    64,    60,    61,
      62,    68,    69,     0,     0,    73,    74,    72,    75,     0,
      78,    79,     0,    80,     0,     0,    92,    98,     0,    96,
      97,     0,     0,     0,    32,    31,     0,    37,     0,     0,
      43,     0,    44,    46,     0,     0,     0,     0,     0,     0,
      84,    30,     0,    29,    23,     0,    87,    58,    66,    70,
      76,     0,    94,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    47,    16,     0,     0,
       0,     0,    89,    27,    28,     0,     0,    99,    95,     0,
       0,     0,    49,     0,    36,     0,    48,    12,     0,     0,
       0,    22,     0,    26,    13,     0,     0,     0,    33,     0,
       0,     0,    24,     0,    52,    53,    50,    51,     0,     0,
      14,    25,    88,    35,     0,     0,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,   249,  -130,  -130,    23,  -130,    50,  -130,
    -130,  -130,  -130,  -129,   239,   145,  -130,   128,  -130,    64,
    -124,  -130,   -27,  -130,   159,  -130,   163,  -130,   154,  -130,
     156,  -130,   199,   -67,   -21,    63,  -130,   111,  -130,  -130,
       2,   -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    13,    47,    14,    15,
      16,    17,    91,   142,    34,   131,   132,   133,    35,    36,
      18,    37,    60,   103,    61,   104,    62,   109,    63,   112,
      64,    65,    66,    67,    68,    69,   118,   119,   120,    93,
     134,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    74,    19,    76,   117,    43,    20,    21,    23,    39,
     136,    19,   124,   137,   143,   153,   175,   121,    49,    50,
      54,    88,    55,   157,    56,    49,    50,    54,    89,    55,
      32,   154,   179,   180,   181,   182,   158,    40,    22,    39,
     187,   190,    57,    58,   138,   122,   123,    44,    45,    57,
      58,    49,    50,    54,   125,    55,    59,    33,    46,   170,
      32,   139,   155,    59,   135,    71,   174,    21,    48,   143,
      38,   204,   205,   207,    72,    57,    58,    49,    50,    54,
      70,    55,    49,    50,    54,    73,    55,    33,   117,    59,
       1,     2,     3,     4,   143,     7,    75,    24,    22,   174,
      38,    57,    58,    77,    25,     1,     2,     3,    49,    50,
      78,   171,   200,    26,   174,    59,   169,   173,   110,   111,
      59,    26,    79,    27,    28,    29,    30,    31,    49,    50,
      84,   163,    85,     1,     2,     3,     4,   193,    -7,    42,
      24,   185,    -7,    -7,    -7,    -7,    71,    80,    88,    -7,
      -7,    49,    50,    49,    50,    -7,   115,    49,    50,   116,
     202,    49,    50,    51,    26,   203,    27,    28,    29,    30,
      31,    49,    50,   141,   211,    82,     1,     2,     3,     4,
     144,   145,    86,     5,     6,   101,   102,    90,   214,     7,
      95,    96,    97,    98,    99,   100,   101,   102,     1,     2,
       3,   129,   130,   105,   106,   107,   108,     1,     2,     3,
     129,    49,    50,   116,   161,   162,    83,    87,   208,   209,
      92,   114,    94,   126,   127,   128,    85,   140,   177,   146,
     152,   156,   159,   160,   164,   166,   184,   167,   191,   168,
     176,   172,   183,   186,     7,   188,   195,   189,   192,   194,
     198,   196,   199,   210,   212,   201,   215,   216,    41,   151,
     165,   206,   147,   149,   113,   197,   178,   148,   150,     0,
       0,     0,     0,     0,     0,     0,    81,   213,   217
};

static const yytype_int16 yycheck[] =
{
      21,    28,     0,    30,    71,     1,     4,    15,     6,     7,
      86,     9,     1,    15,    90,     9,   145,     1,     9,    10,
      11,    15,    13,     1,    15,     9,    10,    11,    55,    13,
       7,    14,   156,   157,   158,   159,    14,     0,    46,    37,
     164,   170,    33,    34,    46,    72,    73,    43,    43,    33,
      34,     9,    10,    11,    43,    13,    47,     7,    11,    17,
      37,    88,    45,    47,    85,    13,   142,    15,    11,   145,
       7,   195,   196,   197,    13,    33,    34,     9,    10,    11,
      11,    13,     9,    10,    11,    13,    13,    37,   155,    47,
       4,     5,     6,     7,   170,    17,    13,    11,    46,   175,
      37,    33,    34,    13,    18,     4,     5,     6,     9,    10,
      43,   138,   188,    35,   190,    47,   137,    18,    31,    32,
      47,    35,    43,    37,    38,    39,    40,    41,     9,    10,
      13,   129,    15,     4,     5,     6,     7,    18,     0,     1,
      11,   162,     4,     5,     6,     7,    13,    18,    15,    11,
      12,     9,    10,     9,    10,    17,     8,     9,    10,    11,
      18,     9,    10,    11,    35,   192,    37,    38,    39,    40,
      41,     9,    10,    11,   201,    43,     4,     5,     6,     7,
      16,    17,    15,    11,    12,    25,    26,    17,   209,    17,
      19,    20,    21,    22,    23,    24,    25,    26,     4,     5,
       6,     7,     8,    27,    28,    29,    30,     4,     5,     6,
       7,     9,    10,    11,    14,    15,    11,    16,    14,    15,
      42,    13,    43,    11,    43,    11,    15,    14,     9,    47,
      14,    14,    14,    11,    14,    11,    43,    16,    43,    16,
      14,    16,    14,    11,    17,    15,    36,    16,    15,    43,
      43,    36,    16,    16,    16,    46,    16,    14,     9,   114,
     132,   197,   103,   109,    65,    36,   155,   104,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    43,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     6,     7,    11,    12,    17,    49,    50,
      51,    52,    53,    54,    56,    57,    58,    59,    68,    88,
      88,    15,    46,    88,    11,    18,    35,    37,    38,    39,
      40,    41,    54,    56,    62,    66,    67,    69,    83,    88,
       0,    51,     1,     1,    43,    43,    11,    55,    11,     9,
      10,    11,    82,    89,    11,    13,    15,    33,    34,    47,
      70,    72,    74,    76,    78,    79,    80,    81,    82,    83,
      11,    13,    13,    13,    70,    13,    70,    13,    43,    43,
      18,    62,    43,    11,    13,    15,    15,    16,    15,    70,
      17,    60,    42,    87,    43,    19,    20,    21,    22,    23,
      24,    25,    26,    71,    73,    27,    28,    29,    30,    75,
      31,    32,    77,    80,    13,     8,    11,    81,    84,    85,
      86,     1,    70,    70,     1,    43,    11,    43,    11,     7,
       8,    63,    64,    65,    88,    82,    89,    15,    46,    70,
      14,    11,    61,    89,    16,    17,    47,    72,    74,    76,
      78,    63,    14,     9,    14,    45,    14,     1,    14,    14,
      11,    14,    15,    88,    14,    65,    11,    16,    16,    82,
      17,    70,    16,    18,    89,    61,    14,     9,    85,    68,
      68,    68,    68,    14,    43,    82,    11,    68,    15,    16,
      61,    43,    15,    18,    43,    36,    36,    36,    43,    16,
      89,    46,    18,    70,    68,    68,    67,    68,    14,    15,
      16,    70,    16,    43,    82,    16,    14,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    54,    54,    55,    55,    56,    56,
      56,    57,    58,    59,    59,    59,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    71,    71,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    80,    80,    81,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      87,    88,    88,    88,    89,    89
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     2,     2,
       1,     1,     6,     7,     9,     2,     4,     1,     2,     1,
       1,     4,     7,     5,     8,     9,     4,     3,     2,     1,
       1,     3,     3,     6,    11,     8,     5,     3,     2,     2,
       2,     1,     1,     1,     1,     2,     1,     2,     3,     5,
       7,     7,     7,     7,     3,     2,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       2,     1,     1,     1,     3,     1,     1,     3,     7,     4,
       1,     1,     1,     4,     4,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 172 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._program) = make_Program_op0((yyvsp[0]._globalStmtList));
    printf("\tArvore de parsing implicitamente gerada!\n");
  }
#line 1619 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 176 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmtList) = make_GlobalStmtList_op0((yyvsp[-1]._globalStmtList), (yyvsp[0]._globalStmt));
  }
#line 1627 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 179 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmtList) = make_GlobalStmtList_op1((yyvsp[0]._globalStmt));
  }
#line 1635 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 182 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmt) = make_GlobalStmt_op0((yyvsp[0]._declFun));
    printf("GlbStmt TAG : %d\n", (yyval._globalStmt)->tag);
  }
#line 1644 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 186 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmt) = make_GlobalStmt_op1((yyvsp[-1]._defFun), NULL);
    printf("[def-fun; 1] GlbStmt TAG : %d\n", (yyval._globalStmt)->tag);
  }
#line 1653 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 190 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmt) = make_GlobalStmt_op2((yyvsp[0]._defFun));
    printf("[def-fun; 2] GlbStmt TAG : %d\n", (yyval._globalStmt)->tag);
  }
#line 1662 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 194 "grammar.y" /* yacc.c:1646  */
    {
  (yyval._globalStmt) = make_GlobalStmt_op3((yyvsp[-1]._declVar));
  }
#line 1670 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 197 "grammar.y" /* yacc.c:1646  */
    {
  (yyval._globalStmt) = make_GlobalStmt_op4((yyvsp[-1]._declVar), NULL);
  }
#line 1678 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 200 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmt) = make_GlobalStmt_op5((yyvsp[0]._attrVar));
  }
#line 1686 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 203 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._globalStmt) = make_GlobalStmt_op6((yyvsp[0]._block));
  }
#line 1694 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 206 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._defFun) = make_DefFun_op0((yyvsp[-5]._baseType), (yyvsp[-4]._id), (yyvsp[-2]._paramListVoid), (yyvsp[0]._block));
    printf("[def-fun; 0] DefFun TAG : %d\n", (yyval._defFun)->tag);
  }
#line 1703 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 210 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._declFun) = make_DeclFun_op0((yyvsp[-5]._baseType), (yyvsp[-4]._id), (yyvsp[-2]._paramListVoid)); 
  }
#line 1711 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 213 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._declVar) = make_DeclVar_op0((yyvsp[-7]._baseType), (yyvsp[-6]._id), (yyvsp[-4]._num), (yyvsp[-1]._num) ); 
  }
#line 1719 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 216 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._declVar) = make_DeclVar_op1((yyvsp[-1]._baseType), (yyvsp[0]._idArr)); 
  }
#line 1727 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 219 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._idArr) = make_IdArr_op0((yyvsp[-3]._id), (yyvsp[-1]._numId)); 
  }
#line 1735 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 222 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._idArr) = make_IdArr_op1((yyvsp[0]._id)); 
  }
#line 1743 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 225 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._attrVar) = make_AttrVar_op0((yyvsp[-1]._matAttr)); 
  }
#line 1751 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 228 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._attrVar) = make_AttrVar_op1((yyvsp[0]._indexAttr)); 
  }
#line 1759 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 231 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._attrVar) = make_AttrVar_op2((yyvsp[0]._simpleAttr)); 
  }
#line 1767 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 234 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._simpleAttr) = make_SimpleAttr_op0((yyvsp[-3]._id), (yyvsp[-1]._expr)); 
  }
#line 1775 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 237 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._indexAttr) = make_IndexAttr_op0((yyvsp[-6]._id), (yyvsp[-4]._numId), (yyvsp[-1]._expr)); 
  }
#line 1783 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 240 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._matAttr) = make_MatAttr_op0((yyvsp[-4]._id), (yyvsp[-1]._numListList)); 
  }
#line 1791 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 243 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._matAttr) = make_MatAttr_op1((yyvsp[-7]._id), (yyvsp[-5]._numId), (yyvsp[-1]._numList)); 
  }
#line 1799 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 246 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._matAttr) = make_MatAttr_op2((yyvsp[-8]._id), (yyvsp[-6]._numId), (yyvsp[-3]._numId), (yyvsp[0]._expr)); 
  }
#line 1807 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 249 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numListList) = make_NumListList_op0((yyvsp[-3]._numListList), (yyvsp[-1]._numList)); 
  }
#line 1815 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 252 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numListList) = make_NumListList_op1((yyvsp[-1]._numList)); 
  }
#line 1823 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 255 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numList) = make_NumList_op0((yyvsp[-1]._numList), (yyvsp[0]._num)); 
  }
#line 1831 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 258 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numList) = make_NumList_op1((yyvsp[0]._num)); 
  }
#line 1839 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 261 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numList) = make_NumList_op2((yyvsp[0]._id)); 
  }
#line 1847 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 264 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op0((yyvsp[-1]._expr)); 
  }
#line 1855 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 267 "grammar.y" /* yacc.c:1646  */
    {
    printf("Missing ;\n");
    (yyval._stmt) = make_Stmt_op0((yyvsp[-1]._expr)); 
  }
#line 1864 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 271 "grammar.y" /* yacc.c:1646  */
    {
  (yyval._stmt) = make_Stmt_op1((yyvsp[-3]._id), (yyvsp[-2]._id));
  // printf("%s %s!\n", $3, $4);
  }
#line 1873 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 275 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op2((yyvsp[-8]._id), (yyvsp[-6]._numId), (yyvsp[-3]._numId)); 
  }
#line 1881 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 278 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op3((yyvsp[-5]._id), (yyvsp[-3]._numId)); 
  }
#line 1889 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 281 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op4((yyvsp[-2]._id)); 
  }
#line 1897 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 284 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op5((yyvsp[-1]._expr)); 
  }
#line 1905 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 287 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op6((yyvsp[-1]._call)); 
  }
#line 1913 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 290 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op7((yyvsp[-1]._declVar));
    printf("\tCHECK : decl-var SEMI_COLON\n");
  }
#line 1922 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 294 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op8((yyvsp[-1]._attrVar)); 
  }
#line 1930 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 297 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op9((yyvsp[0]._flowControl)); 
  }
#line 1938 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 300 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmt) = make_Stmt_op10((yyvsp[0]._loop)
  );}
#line 1946 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 303 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._paramListVoid) = make_ParamListVoid_op0(); 
  }
#line 1954 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 306 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._paramListVoid) = make_ParamListVoid_op1((yyvsp[0]._paramList)); 
  }
#line 1962 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 309 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._paramList) = make_ParamList_op0((yyvsp[-1]._paramList), (yyvsp[0]._param)); 
  }
#line 1970 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 312 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._paramList) = make_ParamList_op1((yyvsp[0]._param)); 
  }
#line 1978 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 315 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._param) = make_Param_op0((yyvsp[-1]._baseType), (yyvsp[0]._id)); 
  }
#line 1986 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 318 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._param) = make_Param_op1((yyvsp[-1]._baseType), (yyvsp[0]._id)); 
  }
#line 1994 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 321 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._loop) = make_Loop_op0( (yyvsp[-2]._expr), (yyvsp[0]._block)); 
  }
#line 2002 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 324 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._flowControl) = make_FlowControl_op0( (yyvsp[-4]._expr), (yyvsp[-2]._block), (yyvsp[0]._flowControl)); 
  }
#line 2010 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 327 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._flowControl) = make_FlowControl_op1((yyvsp[-4]._expr), (yyvsp[-2]._block), (yyvsp[0]._block)); 
  }
#line 2018 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 330 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._flowControl) = make_FlowControl_op2( NULL, (yyvsp[-2]._block), (yyvsp[0]._block)); 
  }
#line 2026 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 333 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._flowControl) = make_FlowControl_op3((yyvsp[-4]._expr), NULL, (yyvsp[-2]._block), (yyvsp[0]._block)); 
  }
#line 2034 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 336 "grammar.y" /* yacc.c:1646  */
    {
    printf("Erro : IF LP expr error block ELSE block\n");
    printf("Falta fechar parentese\n");
    (yyval._block) = make_Block_op0((yyvsp[-1]._stmtList));
    // yyerrok;
  }
#line 2045 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 342 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._block) = make_Block_op1(); 
  }
#line 2053 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 345 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmtList) = make_StmtList_op0((yyvsp[-1]._stmtList), (yyvsp[0]._stmt)); 
  }
#line 2061 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 348 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._stmtList) = make_StmtList_op1((yyvsp[0]._stmt)); 
  }
#line 2069 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 351 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._expr) = make_Expr_op0((yyvsp[-2]._addExpr), (yyvsp[-1]._relop), (yyvsp[0]._addExpr)); 
  }
#line 2077 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 354 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._expr) = make_Expr_op1((yyvsp[0]._addExpr)); 
  }
#line 2085 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 357 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op0(); 
  }
#line 2093 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 360 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op1(); 
  }
#line 2101 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 363 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op2(); 
  }
#line 2109 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 366 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op3(); 
  }
#line 2117 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 369 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op4(); 
  }
#line 2125 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 372 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._relop) = make_Relop_op5(); 
  }
#line 2133 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 375 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._addExpr) = make_AddExpr_op0((yyvsp[-2]._addExpr), (yyvsp[-1]._addop), (yyvsp[0]._term)); 
  }
#line 2141 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 378 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._addExpr) = make_AddExpr_op1((yyvsp[0]._term)); 
  }
#line 2149 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 381 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._addop) = make_Addop_op0(); 
  }
#line 2157 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 384 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._addop) = make_Addop_op1(); 
  }
#line 2165 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 387 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._term) = make_Term_op0((yyvsp[-2]._term), (yyvsp[-1]._mulop), (yyvsp[0]._bin)); 
  }
#line 2173 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 390 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._term) = make_Term_op1((yyvsp[0]._bin)); 
  }
#line 2181 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 393 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._mulop) = make_Mulop_op0(); 
  }
#line 2189 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 396 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._mulop) = make_Mulop_op1(); 
  }
#line 2197 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 399 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._mulop) = make_Mulop_op2(); 
  }
#line 2205 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 402 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._mulop) = make_Mulop_op3(); 
  }
#line 2213 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 405 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._bin) = make_Bin_op0((yyvsp[-2]._bin), (yyvsp[-1]._binLogi), (yyvsp[0]._unary)); 
  }
#line 2221 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 408 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._bin) = make_Bin_op1((yyvsp[0]._unary)); 
  }
#line 2229 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 411 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._binLogi) = make_BinLogi_op0(); 
  }
#line 2237 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 414 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._binLogi) = make_BinLogi_op1(); 
  }
#line 2245 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 417 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._unary) = make_Unary_op0((yyvsp[-1]._unaryOp), (yyvsp[0]._factor)); 
  }
#line 2253 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 420 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._unary) = make_Unary_op1((yyvsp[0]._factor)); 
  }
#line 2261 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 423 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._unaryOp) = make_UnaryOp_op0(); 
  }
#line 2269 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 426 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._unaryOp) = make_UnaryOp_op1(); 
  }
#line 2277 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 429 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._factor) = make_Factor_op0((yyvsp[-1]._expr)); 
  }
#line 2285 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 432 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._factor) = make_Factor_op1((yyvsp[0]._aux)); 
  }
#line 2293 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 435 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._factor) = make_Factor_op2((yyvsp[0]._call)); 
  }
#line 2301 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 438 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._factor) = make_Factor_op3((yyvsp[-1]._ascii)); 
  }
#line 2309 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 441 "grammar.y" /* yacc.c:1646  */
    {
    printf("to bolado\n");
    int v;scanf("%d",&v);
    printf("ID PELO SINTATICO : %s\n", (yyvsp[-6]._id));
    (yyval._aux) = make_Aux_op0((yyvsp[-6]._id), (yyvsp[-4]._expr), (yyvsp[-1]._expr));
  }
#line 2320 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 447 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._aux) = make_Aux_op1((yyvsp[-3]._id), (yyvsp[-1]._expr)); 
  }
#line 2328 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 450 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._aux) = make_Aux_op2((yyvsp[0]._numId)); 
  }
#line 2336 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 453 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numId) = make_NumId_op0((yyvsp[0]._num)); 
  }
#line 2344 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 456 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._numId) = make_NumId_op1((yyvsp[0]._id)); 
  }
#line 2352 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 459 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._call) = make_Call_op0((yyvsp[-3]._id), (yyvsp[-1]._argList)); 
  }
#line 2360 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 462 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._call) = make_Call_op1((yyvsp[-3]._id)); 
  }
#line 2368 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 465 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._argList) = make_ArgList_op0((yyvsp[-2]._argList), (yyvsp[0]._arg)); 
  }
#line 2376 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 468 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._argList) = make_ArgList_op1((yyvsp[0]._arg)); 
  }
#line 2384 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 471 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._arg) = make_Arg_op0((yyvsp[0]._matArg)); 
  }
#line 2392 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 474 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._arg) = make_Arg_op1((yyvsp[0]._aux)); 
  }
#line 2400 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 477 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._matArg) = make_MatArg_op0((yyvsp[-2]._id), (yyvsp[-1].ival), (yyvsp[0].ival)); 
  }
#line 2408 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 480 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._ascii) = make_Ascii_op0((yyvsp[0].cval)); 
  }
#line 2416 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 483 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._baseType) = make_BaseType_op0(); 
  }
#line 2424 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 486 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._baseType) = make_BaseType_op1(); 
  }
#line 2432 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 489 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._baseType) = make_BaseType_op2(); 
  }
#line 2440 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 492 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._num) = make_Num_op0((yyvsp[0].fval)); 
  }
#line 2448 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 495 "grammar.y" /* yacc.c:1646  */
    {
    (yyval._num) = make_Num_op1((yyvsp[0].ival)); 
  }
#line 2456 "grammar.tab.c" /* yacc.c:1646  */
    break;


#line 2460 "grammar.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 499 "grammar.y" /* yacc.c:1906  */


// extern void yyerror (char const *s);
void yyerror (char const *s) {
  fprintf (stderr, "%s | Line %d\n", s, yylineno);
}
int main() {
  yyparse();
  // yylex_destroy();
}
