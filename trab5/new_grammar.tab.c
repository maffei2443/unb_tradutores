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
#line 12 "new_grammar.y" /* yacc.c:339  */


#define STR(x) #x
#define INITNODE(x) \
  {yyval.no = No_New(nodeCounter++);\
  if(!yyval.no) abort();\
  yyval.no->tname =  x  ;}
#define MAKE_NODE(x) INITNODE(STR(x))
#define PARAM_RPT_NAME_CHECK(__baseType, __id) \
  if(!neoEntry) {\
    neoEntry = last_decl(&reshi, yyvsp[__id]._id);    \
    printf("[Semantico] Parametros de mesmo nome! Arvore vai ficar inconsistente..\n");\
  }\
  else {\
    neoEntry->type = yyvsp[__baseType].type;\
    yyval.no->type = yyvsp[__baseType].type;\
    neoEntry->tag = TYPE_PARAM;\
  }

#include "Tree.h" // importante
#include "SemanticChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);

extern void yylex_destroy();
// 
unsigned nodeCounter;

extern int gambs_tam;
extern int gambs_qtd;
char* GLOBAL_SCOPE = "0global";

SymEntry* reshi;

char* currScope = NULL;
int check_signature = 0;
int decl_fun_rule = 0;
int def_fun_rule = 0;
int declared_curr_fun = 0;
int check_parameters = 0;
int err = 0;
int aborta = 0;

#line 117 "new_grammar.tab.c" /* yacc.c:339  */

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
   by #include "new_grammar.tab.h".  */
#ifndef YY_YY_NEW_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_NEW_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "new_grammar.y" /* yacc.c:355  */

  #include "Tree.h"
  No* root;
  struct {
    int ival;
    float fval;
    char* sval;
    int allocated;
  } _;

#line 158 "new_grammar.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EQ = 258,
    NEQ = 259,
    GE = 260,
    LE = 261,
    AND = 262,
    OR = 263,
    MAT_POW = 264,
    BASE_TYPE = 265,
    WHILE = 266,
    V_INT = 267,
    V_FLOAT = 268,
    V_ASCII = 269,
    AHEAD = 270,
    MAT_TYPE = 271,
    IF = 272,
    ID = 273,
    ICAST = 274,
    FCAST = 275,
    ELSE = 276,
    RETURN = 277,
    PRINT = 278,
    IREAD = 279,
    FREAD = 280,
    COPY = 281,
    ERRU = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "new_grammar.y" /* yacc.c:355  */

  char* _id;
  int ival;
  float fval;
  char cval;
  No* no;
  Type type;

#line 207 "new_grammar.tab.c" /* yacc.c:355  */
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

#endif /* !YY_YY_NEW_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "new_grammar.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   471

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,     2,     2,     2,    13,    19,     2,
      39,    40,    14,    11,    44,    12,     2,    15,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
       9,    43,    10,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
       5,     6,     7,     8,    17,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   118,   121,   131,   132,   133,   134,   136,
     136,   182,   217,   237,   262,   263,   268,   270,   278,   280,
     293,   295,   314,   331,   349,   354,   359,   363,   372,   376,
     380,   385,   386,   395,   404,   410,   415,   422,   427,   435,
     443,   449,   454,   459,   465,   472,   472,   562,   567,   572,
     577,   583,   588,   593,   597,   608,   617,   628,   637,   646,
     655,   664,   673,   682,   691,   700,   709,   718,   727,   736,
     743,   753,   754,   765,   776,   777,   778,   780,   808,   836,
     849,   851,   852,   878,   885,   894,   920,   928,   938,   939,
     942
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "NEQ", "GE", "LE", "AND", "OR",
  "'<'", "'>'", "'+'", "'-'", "'%'", "'*'", "'/'", "'@'", "MAT_POW", "'!'",
  "'&'", "BASE_TYPE", "WHILE", "V_INT", "V_FLOAT", "V_ASCII", "AHEAD",
  "MAT_TYPE", "IF", "ID", "ICAST", "FCAST", "ELSE", "RETURN", "PRINT",
  "IREAD", "FREAD", "COPY", "ERRU", "';'", "'('", "')'", "'['", "']'",
  "'='", "','", "'{'", "'}'", "$accept", "program", "globalStmtList",
  "globalStmt", "declFun", "$@1", "typeAndNameSign", "declOrdeclInitVar",
  "paramListVoid", "paramList", "param", "localStmtList", "localStmt",
  "flowControl", "loop", "defFun", "$@2", "numListList", "numList",
  "block", "declList", "expr", "call", "argList", "arg", "num", "lvalue",
  "rvalue", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    60,
      62,    43,    45,    37,    42,    47,    64,   264,    33,    38,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    59,    40,
      41,    91,    93,    61,    44,   123,   125
};
# endif

#define YYPACT_NINF -173

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-173)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -173,     3,    -2,  -173,     5,     6,   104,  -173,    49,    70,
    -173,  -173,    94,    62,   128,  -173,  -173,  -173,   366,  -173,
      -8,  -173,    73,   417,   417,  -173,  -173,   136,   137,   140,
     417,    -8,   454,  -173,  -173,  -173,    88,    -4,   150,   154,
      -8,  -173,  -173,   -23,   417,   417,   417,   192,    61,   234,
    -173,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   417,  -173,  -173,   255,   266,
     247,   244,  -173,  -173,    -4,   248,   240,  -173,   134,  -173,
    -173,    68,   207,   245,  -173,    -8,  -173,    -8,  -173,   174,
     174,   174,   174,   225,    86,   214,   214,   114,   114,   229,
     120,   120,   120,   272,   250,   264,   249,    -4,   253,   254,
     417,  -173,   268,   256,  -173,  -173,   238,  -173,   257,  -173,
    -173,  -173,  -173,    -8,   260,  -173,   417,  -173,  -173,    -1,
     289,   259,   138,   304,  -173,   380,  -173,   417,  -173,   292,
     295,    66,   417,   296,   297,   300,   301,  -173,  -173,  -173,
    -173,  -173,   299,   302,   298,   417,   417,    93,   156,   353,
     314,   314,   314,  -173,   366,  -173,   313,   351,   303,    48,
    -173,  -173,   306,   307,   308,   310,   311,   314,   331,   325,
     325,   325,   325,   325,   335,   336,   340,   341,   312,  -173,
    -173,  -173,   317,  -173,   349,   355,  -173,  -173,  -173,  -173,
     352,   396,   325,   325,   -25,  -173,  -173,  -173,  -173,  -173,
    -173
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     4,     0,     0,
       7,     5,    11,     0,     0,     8,     6,    14,     0,    45,
       0,     9,     0,     0,     0,    83,    84,    85,     0,     0,
       0,    48,    88,    75,    76,    74,     0,    18,     0,     0,
       0,    69,    70,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    15,     0,     0,
       0,    17,    20,    12,    18,     0,    85,    78,     0,    80,
      81,     0,     0,     0,    71,     0,    90,     0,    89,    61,
      62,    63,    64,    67,    68,    66,    65,    54,    55,    58,
      56,    57,    59,    60,    21,     0,     0,     0,     0,     0,
       0,    77,     0,    86,    72,    73,     0,    49,     0,    23,
      53,    19,    10,     0,     0,    79,     0,    47,    22,    25,
       0,     0,     0,     0,    52,     0,    13,     0,    87,    11,
       0,     0,     0,     0,     0,     0,     0,    37,    46,    24,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,    82,     0,     0,     0,     0,
      31,    30,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      25,    44,     0,    43,     0,    40,    35,    34,    32,    33,
       0,     0,     0,     0,     0,    36,    51,    42,    41,    38,
      39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,  -173,  -173,  -173,  -173,   212,   270,  -173,
     280,   203,  -173,   193,  -173,  -173,  -173,  -173,   315,  -172,
    -173,   -17,  -131,  -173,   287,   -19,   -43,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    39,     9,    10,    70,    71,
      72,   135,   149,   150,   151,    11,    37,    48,    49,   191,
     129,    32,    33,    78,    79,    34,    35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      80,    38,   141,     3,   152,    76,    41,    42,   192,   193,
     194,   195,    50,    47,    25,    26,    68,    77,     4,   133,
     190,    75,    69,     5,     6,     6,    13,    81,    82,    83,
     207,   208,   210,    12,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   182,
      15,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    50,   156,   117,    80,
     152,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   173,    16,   183,    66,
      21,   178,   153,   124,   168,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   130,   157,    85,    86,    17,   132,
     113,    23,    24,    18,    40,    25,    26,   175,   176,   177,
     154,    27,    28,    29,    14,   158,    67,    61,    62,    63,
      64,    65,    30,    19,   188,    20,    64,    65,   166,   167,
     169,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    22,   170,   153,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   111,    43,    45,    44,   112,    46,
     138,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    73,    74,   171,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    59,    60,    61,    62,    63,
      64,    65,    84,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    62,    63,    64,    65,   114,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    87,   110,
      88,    44,    87,   104,   127,   115,   105,   106,   107,    65,
     109,   118,   119,   122,   120,   123,    76,   126,   137,   128,
     131,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   136,   139,    20,   155,   159,   160,   163,   165,   161,
     162,   134,   174,   181,   108,   164,   184,   185,   202,    44,
     186,   187,   200,   179,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,   189,
     190,    23,    24,   196,   197,    25,    26,   172,   198,   199,
     203,    27,    28,    29,    23,    24,   204,   121,    25,    26,
     205,   180,    30,   201,    27,    28,    29,   209,    31,   125,
     116,   140,     0,     0,     0,    30,     0,   141,    27,     0,
       0,    31,   142,   143,   144,   145,   146,   140,   147,     0,
       0,     0,     0,   141,    27,     0,   148,     0,   142,   143,
     144,   145,   146,     0,   147,    23,    24,     0,     0,    25,
      26,     0,   206,     0,     0,    27,    28,    29,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65
};

static const yytype_int16 yycheck[] =
{
      43,    20,    27,     0,   135,    28,    23,    24,   180,   181,
     182,   183,    31,    30,    22,    23,    20,    40,    20,    20,
      45,    40,    26,    25,    26,    26,    20,    44,    45,    46,
     202,   203,   204,    28,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     1,
       1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    85,     1,    87,   112,
     201,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,   159,    38,    40,     1,
      28,   164,   135,   110,     1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,   123,    39,    45,    46,    38,   126,
      42,    18,    19,    43,    41,    22,    23,   160,   161,   162,
     137,    28,    29,    30,    20,   142,    38,    13,    14,    15,
      16,    17,    39,    39,   177,    41,    16,    17,   155,   156,
     157,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    28,     1,   201,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    40,    39,    39,    41,    44,    39,
      42,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    42,    39,    38,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    11,    12,    13,    14,    15,
      16,    17,    40,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    14,    15,    16,    17,    40,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    44,    39,
      46,    41,    44,    28,    46,    40,    20,    40,    44,    17,
      42,    41,    28,    40,    45,    41,    28,    41,    39,    42,
      40,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    42,    28,    41,    39,    39,    39,    38,    40,    39,
      39,   129,    28,    40,    74,    43,    40,    40,    31,    41,
      40,    40,    40,    40,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    38,
      45,    18,    19,    38,    38,    22,    23,    24,    38,    38,
      31,    28,    29,    30,    18,    19,    31,   107,    22,    23,
      38,    40,    39,   190,    28,    29,    30,   204,    45,   112,
      85,    21,    -1,    -1,    -1,    39,    -1,    27,    28,    -1,
      -1,    45,    32,    33,    34,    35,    36,    21,    38,    -1,
      -1,    -1,    -1,    27,    28,    -1,    46,    -1,    32,    33,
      34,    35,    36,    -1,    38,    18,    19,    -1,    -1,    22,
      23,    -1,    46,    -1,    -1,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,    20,    25,    26,    50,    51,    53,
      54,    62,    28,    20,    20,     1,    38,    38,    43,    39,
      41,    28,    28,    18,    19,    22,    23,    28,    29,    30,
      39,    45,    68,    69,    72,    73,    74,    63,    72,    52,
      41,    68,    68,    39,    41,    39,    39,    68,    64,    65,
      72,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     1,    38,    20,    26,
      55,    56,    57,    42,    39,    72,    28,    40,    70,    71,
      73,    68,    68,    68,    40,    45,    46,    44,    46,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    28,    20,    40,    44,    55,    42,
      39,    40,    44,    42,    40,    40,    65,    72,    41,    28,
      45,    57,    40,    41,    68,    71,    41,    46,    42,    67,
      72,    40,    68,    20,    54,    58,    42,    39,    42,    28,
      21,    27,    32,    33,    34,    35,    36,    38,    46,    59,
      60,    61,    69,    73,    68,    39,     1,    39,    68,    39,
      39,    39,    39,    38,    43,    40,    68,    68,     1,    68,
       1,    38,    24,    74,    28,    73,    73,    73,    74,    40,
      40,    40,     1,    40,    40,    40,    40,    40,    73,    38,
      45,    66,    66,    66,    66,    66,    38,    38,    38,    38,
      40,    58,    31,    31,    31,    38,    46,    66,    66,    60,
      66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    52,
      51,    53,    53,    53,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    61,    63,    62,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    73,    73,    74,    74,
      74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     2,     0,
       7,     2,     5,     9,     2,     4,     4,     1,     0,     3,
       1,     2,     4,     3,     2,     0,     2,     4,     1,     1,
       3,     3,     5,     5,     5,     5,     6,     1,     7,     7,
       5,     7,     7,     5,     5,     0,    10,     4,     0,     3,
       1,     3,     2,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     4,     1,     1,     1,     4,     3,     3,
       1,     1,     7,     1,     1,     1,     4,     7,     1,     3,
       3
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
#line 111 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = (yyvsp[0].no);
  root = (yyval.no);
  printf("Derivacao foi concluida.\n");
}
#line 1606 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 118 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = NULL;
}
#line 1614 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 121 "new_grammar.y" /* yacc.c:1646  */
    {
  if((yyvsp[-1].no)){
    MAKE_NODE(globalStmtList);
    add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
    add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  }
  else
    (yyval.no) = (yyvsp[0].no);
}
#line 1628 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 136 "new_grammar.y" /* yacc.c:1646  */
    {
  decl_fun_rule = 1;
  SymEntry* tmp = last_decl(&reshi, (yyvsp[0]._id));
  if( !tmp ) {
    printf("DEVE ADICIONAR %s como declaracao de funcao\n", (yyvsp[0]._id));
    add_entry(&reshi, (yyvsp[0]._id), TYPE_DECL_FUN);
    err = 0;    
  }
  else {
    printf("[Semantico] |%s| nao pode ser declarado pois jah o foi em l.%d, c.%d\n", tmp->id, tmp->local.line, tmp->local.col);
  }
  currScope = (yyvsp[0]._id);
}
#line 1646 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 148 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(declFun);
  SymEntry* tmp;
  HASH_FIND_STR(reshi, (yyvsp[-4]._id), tmp);

  if(!tmp) {
    printf("tmp is NULL\n");
  }
  else if(!err) {
    link_symentry_no(&tmp, &(yyval.no));
    err = 0;
  }
  if(tmp) {
    tmp->tag = TYPE_DECL_FUN;
    tmp->type = (yyvsp[-5].type);
  }
  
  add_Node_Child_If_Not_Null((yyval.no), Token_New("BASE_TYPE", type2string((yyvsp[-5].type))));
  add_Node_Child_If_Not_Null((yyval.no), Token_New(STR(ID), (yyvsp[-4]._id)));
  printf("[%s] pre-declarou-se!\n", (yyvsp[-4]._id));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  
  (yyval.no)->param = (yyvsp[-1].no);
  link_symentry_no(&tmp, &(yyval.no));
  
  // if ($$->param) {
  //   printf("primeiro parametro de %s: %s\n", $ID, $$->param->sval);
  // }
  free((yyvsp[-4]._id)), (yyvsp[-4]._id) = NULL;
  currScope = GLOBAL_SCOPE;
  decl_fun_rule = 0;
}
#line 1683 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 182 "new_grammar.y" /* yacc.c:1646  */
    {
  SymEntry* oldEntry = last_decl(&reshi, (yyvsp[0]._id));
  printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id);
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    SymEntry* neoEntry = add_entry(&reshi, (yyvsp[0]._id), (yyvsp[-1].type));
    if(neoEntry) {  //TODO: trtar esse caso
      neoEntry->type = neoEntry->tag;
      // printf("[typeAndNameSign : BASE_TYPE ID] neoEntry->tag: %s\n", type2string(neoEntry->tag));
      // printf("[typeAndNameSign : BASE_TYPE ID] neoEntry->type: %s\n", type2string(neoEntry->type));
      MAKE_NODE(typeAndNameSign);
      link_symentry_no(&neoEntry, &(yyval.no));      
      add_Node_Child_If_Not_Null((yyval.no), Token_New("BASE_TYPE", type2string((yyvsp[-1].type))));
      add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[0]._id)));
      free((yyvsp[0]._id));(yyvsp[0]._id) = NULL;  
    }
    else {
      printf("ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neoEntry->escopo, (yyvsp[0]._id));
    }
  }
  else {
    (yyval.no) = NULL;
  }
}
#line 1722 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 217 "new_grammar.y" /* yacc.c:1646  */
    {
  SymEntry* neoEntry = add_entry(&reshi, (yyvsp[-3]._id), (yyvsp[-4].type) == TYPE_INT ? TYPE_ARRAY_INT : TYPE_ARRAY_FLOAT);
  if(neoEntry)
    neoEntry->type = neoEntry->tag;
  else 
    printf("[Semantico] %s nao foi declarado!\n", (yyvsp[-3]._id));
  
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(&neoEntry, &(yyval.no));

  add_Node_Child_If_Not_Null((yyval.no), Token_New("BASE_TYPE", type2string((yyvsp[-4].type))));
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-3]._id)));
  // SEMANTICO!
  if((yyvsp[-1].no)->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", (yyvsp[-1].no)->fval);
  }
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  free((yyvsp[-3]._id));(yyvsp[-3]._id) = NULL;
  // $$->childLast->ival = $V_INT;
}
#line 1747 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 237 "new_grammar.y" /* yacc.c:1646  */
    {
  SymEntry* neoEntry = add_entry(&reshi, (yyvsp[-6]._id), (yyvsp[-7].type) == TYPE_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT);
  if(neoEntry)
    neoEntry->type = neoEntry->tag;
  else 
    printf("[Semantico] %s nao foi declarado!\n", (yyvsp[-6]._id));
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(&neoEntry, &(yyval.no));

  MAKE_NODE(typeAndNameSign);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("MAT_TYPE", "mat"));
  if((yyvsp[-4].no)->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", (yyvsp[-4].no)->fval);
  }
  if((yyvsp[-1].no)->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", (yyvsp[-1].no)->fval);
  }

  add_Node_Child_If_Not_Null((yyval.no), Token_New("BASE_TYPE", type2string((yyvsp[-7].type))));
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-6]._id)));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-4].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  free((yyvsp[-6]._id)); (yyvsp[-6]._id) = NULL;
}
#line 1776 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 263 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-3].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 1786 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 270 "new_grammar.y" /* yacc.c:1646  */
    {
  // childLast eh usado como auxiliar para criar a lista na ordem correta ;)
  (yyvsp[0].no)->childLast = NULL;
  (yyval.no) = (yyvsp[0].no);
  printf("[paramListVoid] %p\n", (yyval.no));
  printf("[paramListVoid->type] %s\n", type2string((yyval.no)->type));

}
#line 1799 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 278 "new_grammar.y" /* yacc.c:1646  */
    {(yyval.no) = NULL;}
#line 1805 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 280 "new_grammar.y" /* yacc.c:1646  */
    {
  // Para mantes a ordem correta dos parametros
  if(!(yyvsp[-2].no)->hasAux) {
    (yyvsp[-2].no)->hasAux = 1;
    (yyvsp[-2].no)->nextAux = (yyvsp[0].no);
    (yyvsp[-2].no)->childLast = (yyvsp[0].no);
  }
  else {
    (yyvsp[-2].no)->childLast->nextAux = (yyvsp[0].no);
    (yyvsp[-2].no)->childLast = (yyvsp[0].no);
  }
  (yyval.no) = (yyvsp[-2].no);
}
#line 1823 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 295 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = Token_New(STR(param), (yyvsp[0]._id));
  SymEntry* funEntry = last_decl(&reshi, (yyvsp[0]._id));
  printf("!!! %p, %s: param @@@\n", funEntry, (yyvsp[0]._id));
  if(!declared_curr_fun) {
    SymEntry* neoEntry = add_entry(&reshi, (yyvsp[0]._id), TYPE_PARAM);
    if(neoEntry) {
      neoEntry->type =  (yyvsp[-1].type);
      (yyval.no)->type =  (yyvsp[-1].type);
      PARAM_RPT_NAME_CHECK(-1, 0);
      link_symentry_no(&neoEntry, &(yyval.no));
    }
  }
  else {
    // printf("1296 !!!\n");
  }
  (yyval.no)->type = (yyvsp[-1].type);
  free((yyvsp[0]._id)), (yyvsp[0]._id) = NULL;
}
#line 1847 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 314 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = Token_New(STR(param), (yyvsp[-2]._id));
  SymEntry* neoEntry = add_entry(&reshi, (yyvsp[-2]._id), TYPE_PARAM );
  // SEMANTICO
  PARAM_RPT_NAME_CHECK(-3, -2);
  
  if((yyvsp[-3].type) == TYPE_INT)    neoEntry->type = TYPE_MAT_INT;
  else if ((yyvsp[-3].type) == TYPE_FLOAT) neoEntry->type = TYPE_ARRAY_FLOAT;
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  (yyval.no)->type = (yyvsp[-3].type);
  link_symentry_no(&neoEntry, &(yyval.no));
  free((yyvsp[-2]._id)), (yyvsp[-2]._id) = NULL;
}
#line 1868 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 331 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = Token_New(STR(param), (yyvsp[0]._id));
  SymEntry* neoEntry = add_entry(&reshi, (yyvsp[0]._id), TYPE_PARAM);
  // Semantico
  PARAM_RPT_NAME_CHECK(-1, 0);

  if((yyvsp[-1].type) == TYPE_INT) neoEntry->type = TYPE_MAT_INT;  
  else if ((yyvsp[-1].type) == TYPE_FLOAT) neoEntry->type = TYPE_MAT_FLOAT;
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  if(neoEntry)
    link_symentry_no(&neoEntry, &(yyval.no));  
  free((yyvsp[0]._id)), (yyvsp[0]._id) = NULL;
}
#line 1889 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 349 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmtList);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 1899 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 354 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = NULL;
  // MAKE_NODE(localStmtList);
}
#line 1908 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 359 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 1917 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 363 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  if((yyvsp[-3].no)->type != (yyvsp[-1].no)->type ||
    (yyvsp[-3].no)->type == (yyvsp[-1].no)->type && (yyvsp[-3].no)->type == TYPE_UNDEFINED) {
    printf("[Semantico] Warning de tipo em atribuicao: <%s> = <%s>\n", type2string((yyvsp[-3].no)->type), type2string((yyvsp[-1].no)->type));
  }
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-3].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 1931 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 372 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 1940 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 376 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 1949 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 380 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("RETURN", "return"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 1959 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 385 "new_grammar.y" /* yacc.c:1646  */
    {(yyval.no)=NULL;}
#line 1965 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 386 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  No* iread_no = Token_New("IREAD","IREAD");
  add_Node_Child_If_Not_Null((yyval.no), iread_no);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  if((yyvsp[-2].no)->type != TYPE_INT) {
    printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string((yyvsp[-2].no)->type));
  }
}
#line 1979 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 395 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child_If_Not_Null((yyval.no), fread_no);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  if((yyvsp[-2].no)->type != TYPE_FLOAT) {
    printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string((yyvsp[-2].no)->type));
  }  
}
#line 1993 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 404 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  No* print_no = Token_New("PRINT","PRINT");
  add_Node_Child_If_Not_Null((yyval.no), print_no);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
}
#line 2004 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 410 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  (yyval.no)->ival = (yyvsp[-2].cval);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("PRINT","PRINT"));
}
#line 2014 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 415 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(localStmt);
  No* copy_no = Token_New("COPY","COPY");
  add_Node_Child_If_Not_Null( (yyval.no), copy_no );
  add_Node_Child_If_Not_Null( (yyval.no), (yyvsp[-3].no) );
  add_Node_Child_If_Not_Null( (yyval.no), (yyvsp[-2].no) );
}
#line 2026 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 422 "new_grammar.y" /* yacc.c:1646  */
    {
  // Nao faz mal, mas nao eh util!
  (yyval.no) = NULL;
}
#line 2035 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 427 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("IF","if"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-4].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ELSE","else"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2048 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 435 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("IF","if"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-4].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ELSE","else"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2061 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 443 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("IF","if"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2072 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 449 "new_grammar.y" /* yacc.c:1646  */
    {
  printf("Erro : IF ( expr error block ELSE block\n");
  printf("Falta FECHAR parentese\n");  
  (yyval.no) = NULL;
}
#line 2082 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 454 "new_grammar.y" /* yacc.c:1646  */
    {
  printf("Erro : IF ( expr error block ELSE block\n");
  printf("Falta ABRIR parentese\n");  
  (yyval.no) = NULL;  
}
#line 2092 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 459 "new_grammar.y" /* yacc.c:1646  */
    {
  printf("Erro : IF ( error ) block ELSE block\n");
  printf("Expressao mal formada\n");  
  (yyval.no) = NULL;  
}
#line 2102 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 465 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(loop);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("WHILE","while"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2113 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 472 "new_grammar.y" /* yacc.c:1646  */
    {
  def_fun_rule = 1;
  SymEntry* old = last_decl(&reshi, (yyvsp[-1]._id));
  // CHECAGEM DE REDECLARACAO FEITA AQUI. CHECAGEM DE PARAMETROS,
  // NAO PODE SER FEITA AQUI
  printf("lastDecl: (%p)\n", old);
  if(old) {
    if(old->def_fun) {
      printf("[defFun-Semantico] Funcao %s jah foi definida em l.%d, c.%d\n",
      old->id, old->local.line, old->local.col);
    }
    else if(old->tag == TYPE_DECL_FUN) {
      fprintf(stderr, "Funcao %s foi pre-declarada\n", old->id);
      check_signature = 1;
      declared_curr_fun = 1;
    }
    else {
      fprintf(stderr,"Jah tem variavel com esse (%s) nome :/\n", old->id);
      aborta = 1;
    }
  }
  else {
    printf("definindo funcao %s\n", (yyvsp[-1]._id)); fflush(stdout);
    SymEntry* neoEntry = add_entry(&reshi, (yyvsp[-1]._id), TYPE_DEF_FUN);
    if(!neoEntry) {
      printf("Erro na definicao de funcao %s [bug]\n", (yyvsp[-1]._id));
    }
    else {
      neoEntry->type = (yyvsp[-2].type);
      neoEntry->def_fun = 1;
    }
  }
  currScope = (yyvsp[-1]._id);
}
#line 2152 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 505 "new_grammar.y" /* yacc.c:1646  */
    {
  if(check_signature) {   
    fprintf(stderr,"Checando assinatura de %s\n", (yyvsp[-8]._id));
    currScope = GLOBAL_SCOPE;
    SymEntry* entry = last_decl(&reshi, (yyvsp[-8]._id));
    // assert(entry != NULL);  // se der NULL, algo deu errado pois a funcao jah era pra estar na symTable
    if(entry) {
      if(entry->def_fun) {
        mensagem_redeclaracao(entry);
        (yyval.no) = NULL;
      }
      else {
        fprintf(stderr,"entry->astNode: %p, $paramListVoid: %p \n", entry->astNode, (yyvsp[-5].no));
        int match = match_paramList(entry->astNode->param, (yyvsp[-5].no));
        if(match > 0){
          printf("DEFINICAO de %s BATE COM DECLARACAO!\n", (yyvsp[-8]._id));
          // SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_DEF_FUN);
          // neoEntry->type = $BASE_TYPE;
        }
        else {
          printf("Lista de parametros de %s incompativel com sua declaracao!\n", (yyvsp[-8]._id));
        }
      }
    }
    currScope = GLOBAL_SCOPE;
    check_signature = 0;
    declared_curr_fun = 0;
    // $$ = NULL;
  }
  
  MAKE_NODE(defFun);

  SymEntry* tmp;
  HASH_FIND_STR(reshi, (yyvsp[-8]._id), tmp);
  if(!tmp) {
    printf("FDP\n"); fflush(stdout);
  }
  if (!aborta) {  // nao modificar a entrada jah existente da tabela de simbolos
    tmp->tag = TYPE_DEF_FUN;
    tmp->type = (yyvsp[-9].type);
    (yyval.no)->param = (yyvsp[-5].no);
    link_symentry_no(&tmp, &(yyval.no));
  }
  else
    aborta = 0;
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), type2string((yyvsp[-9].type)));
  No* _ID = Token_New(STR(ID), (yyvsp[-8]._id));
  add_Node_Child_If_Not_Null((yyval.no), _BASE_TYPE);
  add_Node_Child_If_Not_Null((yyval.no), _ID);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-5].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));  
  def_fun_rule = 0;
  currScope = GLOBAL_SCOPE;
  free((yyvsp[-8]._id));(yyvsp[-8]._id) = NULL;
}
#line 2213 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 562 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(numListList);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-3].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 2223 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 567 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = NULL;
  // MAKE_NODE(numListList);
}
#line 2232 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 572 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(numList);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2242 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 577 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(numList);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2251 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 583 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(block);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
}
#line 2260 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 588 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(declList);
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2270 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 593 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = NULL;
}
#line 2278 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 597 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);
  printf("addExpr\n");
  (yyval.no)->ival = '+';
  
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '+');
  printf("tipoResultante: %s\n", type2string((yyval.no)->type));
}
#line 2294 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 608 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '-';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '-');
}
#line 2308 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 617 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '*';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '*');
  printf("tipoResultante: %s\n", type2string((yyval.no)->type));

}
#line 2324 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 628 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '/';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '/');
}
#line 2338 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 637 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '%';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '%');
}
#line 2352 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 646 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '@';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '@');
}
#line 2366 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 655 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = MAT_POW;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, MAT_POW);
}
#line 2380 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 664 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = EQ;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, EQ);
}
#line 2394 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 673 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = NEQ;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, NEQ);
}
#line 2408 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 682 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = GE;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, GE);
}
#line 2422 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 691 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = LE;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, LE);
}
#line 2436 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 700 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '>';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '>');
}
#line 2450 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 709 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = '<';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, '<');
}
#line 2464 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 718 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = AND;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, AND);
}
#line 2478 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 727 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);

  (yyval.no)->ival = OR;
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-2].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
  // SEMANTICO
  (yyval.no)->type = bin_expr_type( (yyvsp[-2].no)->type, (yyvsp[0].no)->type, OR);
}
#line 2492 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 736 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);
  // TODO: RECLAMAR SE NAO "BOOL"
  (yyval.no)->type = TYPE_INT;
  (yyval.no)->ival = '!';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2504 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 743 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);
  // CHECAR SE EH LVAL; SE NAO FOR, TEM QUE DAR ERRO
  if(strcmp((yyvsp[0].no)->tname, "lvalue")) {
    printf("[Semantico] Erro: operando de & deve ser lvalue.\n");
  }
  (yyval.no)->type = TYPE_POINTER;
  (yyval.no)->ival = '&';
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[0].no));
}
#line 2519 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 753 "new_grammar.y" /* yacc.c:1646  */
    {(yyval.no) = (yyvsp[-1].no);}
#line 2525 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 754 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  (yyval.no)->type = TYPE_INT;
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ICAST", "ICAST"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  if(Type_Class((yyvsp[-1].no)->type) != TYPE_SCALAR) {
    printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n",
      type2string((yyvsp[-1].no)->type));
  }
}
#line 2541 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 765 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  (yyval.no)->type = TYPE_FLOAT;  
  add_Node_Child_If_Not_Null((yyval.no), Token_New("FCAST", "FCAST"));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  if(Type_Class((yyvsp[-1].no)->type) != TYPE_SCALAR) {
    printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n",
      type2string((yyvsp[-1].no)->type));
  }  
}
#line 2557 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 780 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-3]._id)));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  // SEMANTICO  
  // TODO: checar se ID eh mesmo funcao. Depois, checar os PARAMETROS, ver se os tipos batem
  SymEntry* aux = last_decl(&reshi, (yyvsp[-3]._id));
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", (yyvsp[-3]._id), numlines, currCol - (strlen((yyvsp[-3]._id)) + 2));
  }
  else{
    (yyval.no)->type = aux->type;
    if(is_fun (aux->tag)) {
      printf("%s eh uma funcao!.\n", aux->id);
      printf("\t astNode: %p!.\n", aux->astNode);
      // Ver se assinatura bate com a declaracao!
      int match = match_paramList(aux->astNode->param, (yyvsp[-1].no));
      if(match > 0) 
        printf("[++++Semantico++++] Argumentos de %s corretos\n", (yyvsp[-3]._id));
      else
        printf("[----Semantico----] Uso indevido de %s\n", (yyvsp[-3]._id)); 
    }
    else {
      printf("%s nao eh funcao para ser chamada\n", aux->id);
    }    
  }
  free((yyvsp[-3]._id)); (yyvsp[-3]._id) = NULL;
}
#line 2590 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 808 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-2]._id)));
  // SEMANTICO  
  SymEntry* aux = last_decl(&reshi, (yyvsp[-2]._id));
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", (yyvsp[-2]._id), numlines, currCol - (strlen((yyvsp[-2]._id)) + 2));
  }
  else{
    (yyval.no)->type = aux->type;
    if(is_fun (aux->tag)) {
      printf("%s eh uma funcao!.\n", aux->id);
      printf("\t astNode: %p!.\n", aux->astNode);
      // Ver se assinatura bate com a declaracao!
      int match = match_paramList(aux->astNode->param, NULL);
      if(match > 0) 
        printf("[++++Semantico++++] Argumentos de %s corretos\n", (yyvsp[-2]._id));
      else
        printf("[----Semantico----] Uso indevido de %s\n", (yyvsp[-2]._id));
      
    }
    else {
      printf("%s nao eh funcao para ser chamada\n", aux->id);
    }    
  }
  free((yyvsp[-2]._id)); (yyvsp[-2]._id) = NULL;
}
#line 2622 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 836 "new_grammar.y" /* yacc.c:1646  */
    {
  // Mesmo esquema da lista de parametros
  if(!(yyvsp[-2].no)->hasAux) {
    (yyvsp[-2].no)->hasAux = 1;
    (yyvsp[-2].no)->nextAux = (yyvsp[0].no);
    (yyvsp[-2].no)->childLast = (yyvsp[0].no);
  }
  else {
    (yyvsp[-2].no)->childLast->nextAux = (yyvsp[0].no);
    (yyvsp[-2].no)->childLast = (yyvsp[0].no);
  }
  (yyval.no) = (yyvsp[-2].no);
}
#line 2640 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 852 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-6]._id)));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-4].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  // SEMANTICO    
  SymEntry* entry = last_decl(&reshi, (yyvsp[-6]._id));
  if(!entry) {  // var na odeclarada
    printf("[Semantico] Erro: Variavel %s, l.%d nao declarada\n", (yyvsp[-6]._id), numlines);    
  }
  else {
    if(is_fun(entry->tag)) {
      printf("[Semantico] Erro: Uso inadequado de funcao %s, l.%d\n", (yyvsp[-6]._id), numlines);
    }
    else if(Type_Class(entry->type) != TYPE_MAT ) {
      printf("[Semantico] Erro: Variavel %s, l.%d nao eh matriz\n", (yyvsp[-6]._id), numlines);    
    }
    else {
      (yyval.no)->type = entry->type;
      printf("argType: %s\n", type2string((yyval.no)->type));
      // TODO: checar dimensoes, mas isso eh em tempo de excucao
    }
  }
  free((yyvsp[-6]._id)); (yyvsp[-6]._id) = NULL;
}
#line 2670 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 878 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(num);
  (yyval.no)->ival = (yyvsp[0].ival);
  // SEMANTICO
  (yyval.no)->is_const = 1;
  (yyval.no)->type = TYPE_INT;
}
#line 2682 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 885 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(num);
  (yyval.no)->fval = (yyvsp[0].fval);
  // SEMANTICO
  (yyval.no)->is_const = 1;
  (yyval.no)->type = TYPE_FLOAT;
}
#line 2694 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 894 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(lvalue);
  No* tok = Token_New("ID", (yyvsp[0]._id));
  add_Node_Child_If_Not_Null((yyval.no), tok);
  // SEMANTICO
  SymEntry* entry = last_decl(&reshi, (yyvsp[0]._id));
  // CHECK FOR NULL (== nao declarado)
  // printf("[ID: %s]entry->type: %s\n", $ID, type2string(entry->type));
  if(entry) {
    if(is_fun(entry->tag)) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       (yyvsp[0]._id), numlines, currCol - (strlen((yyvsp[0]._id)) + 2), entry->local.line, entry->local.col);
    }
    else {
      tok->type = entry->type;
      (yyval.no)->type = entry->type;
      link_symentry_no(&entry, &tok);
    }
  }
  else {
    (yyval.no)->type = TYPE_UNDEFINED;
    printf("Variavel %s, l.%d c.%lu nao declarada!\n", (yyvsp[0]._id), numlines, currCol - (strlen((yyvsp[0]._id)) + 2));
  }
  // printf("lvalue->type=%s \n", type2string( $$->type ));
  free((yyvsp[0]._id)), (yyvsp[0]._id) = NULL;
}
#line 2725 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 920 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-3]._id)));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  // SEMANTICO    
  if(!last_decl(&reshi, (yyvsp[-3]._id))){printf("Variavel %s, l.%d nao declarada!\n", (yyvsp[-3]._id), numlines);}
  free((yyvsp[-3]._id)); (yyvsp[-3]._id) = NULL;
}
#line 2738 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 928 "new_grammar.y" /* yacc.c:1646  */
    {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null((yyval.no), Token_New("ID", (yyvsp[-6]._id)));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-4].no));
  add_Node_Child_If_Not_Null((yyval.no), (yyvsp[-1].no));
  // SEMANTICO    
  if(!last_decl(&reshi, (yyvsp[-6]._id))){printf("Variavel %s, l.%d nao declarada!\n", (yyvsp[-6]._id), numlines);}
  free((yyvsp[-6]._id)); (yyvsp[-6]._id) = NULL;
}
#line 2752 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 939 "new_grammar.y" /* yacc.c:1646  */
    {
  (yyval.no) = (yyvsp[-1].no);
}
#line 2760 "new_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 942 "new_grammar.y" /* yacc.c:1646  */
    {(yyval.no) = (yyvsp[-1].no);}
#line 2766 "new_grammar.tab.c" /* yacc.c:1646  */
    break;


#line 2770 "new_grammar.tab.c" /* yacc.c:1646  */
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
#line 944 "new_grammar.y" /* yacc.c:1906  */



void yyerror (char const *s) {
  fprintf (stderr, "%s | l. %d, c. %d\n", s, numlines, currCol - yyleng);
  fprintf (stderr, "%s | l. %d, c. %d\n", s, yylloc.first_line, yylloc.first_column);
}

void nullify(void** p) {
  *p = NULL;
}

int main(){
  currScope = GLOBAL_SCOPE;
  reshi = NULL;
  nodeCounter = 0;
  yyparse();
  if(root) {
    show_Sub_Tree(root, 1, SVAL);
    show_Lis(root,SVAL);
  }
  print_reshi(reshi);
  yylex_destroy();
  
  free_All_Child(root);
  free_Lis(root);
  delGambs();
}
