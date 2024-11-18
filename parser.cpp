/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

    #include <string>
    #include <vector>
    extern int yylineno;
    using namespace std; // Bringing std namespace into scope
    #include "node.hpp"
    #include <cstring>
    Node* root;
    bool isPre = false;

#line 82 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_HTML_BEGIN = 3,                 /* HTML_BEGIN  */
  YYSYMBOL_HTML_END = 4,                   /* HTML_END  */
  YYSYMBOL_HEAD_BEGIN = 5,                 /* HEAD_BEGIN  */
  YYSYMBOL_HEAD_END = 6,                   /* HEAD_END  */
  YYSYMBOL_TITLE_BEGIN = 7,                /* TITLE_BEGIN  */
  YYSYMBOL_TITLE_END = 8,                  /* TITLE_END  */
  YYSYMBOL_BODY_BEGIN = 9,                 /* BODY_BEGIN  */
  YYSYMBOL_BODY_END = 10,                  /* BODY_END  */
  YYSYMBOL_NAV_BEGIN = 11,                 /* NAV_BEGIN  */
  YYSYMBOL_NAV_END = 12,                   /* NAV_END  */
  YYSYMBOL_UL_BEGIN = 13,                  /* UL_BEGIN  */
  YYSYMBOL_UL_END = 14,                    /* UL_END  */
  YYSYMBOL_LI_BEGIN = 15,                  /* LI_BEGIN  */
  YYSYMBOL_LI_END = 16,                    /* LI_END  */
  YYSYMBOL_HEADER_BEGIN = 17,              /* HEADER_BEGIN  */
  YYSYMBOL_HEADER_END = 18,                /* HEADER_END  */
  YYSYMBOL_H1_BEGIN = 19,                  /* H1_BEGIN  */
  YYSYMBOL_H1_END = 20,                    /* H1_END  */
  YYSYMBOL_H2_BEGIN = 21,                  /* H2_BEGIN  */
  YYSYMBOL_H2_END = 22,                    /* H2_END  */
  YYSYMBOL_H3_BEGIN = 23,                  /* H3_BEGIN  */
  YYSYMBOL_H3_END = 24,                    /* H3_END  */
  YYSYMBOL_H4_BEGIN = 25,                  /* H4_BEGIN  */
  YYSYMBOL_H4_END = 26,                    /* H4_END  */
  YYSYMBOL_H5_BEGIN = 27,                  /* H5_BEGIN  */
  YYSYMBOL_H5_END = 28,                    /* H5_END  */
  YYSYMBOL_PARA_BEGIN = 29,                /* PARA_BEGIN  */
  YYSYMBOL_PARA_END = 30,                  /* PARA_END  */
  YYSYMBOL_SECTION_BEGIN = 31,             /* SECTION_BEGIN  */
  YYSYMBOL_SECTION_END = 32,               /* SECTION_END  */
  YYSYMBOL_ARTICLE_BEGIN = 33,             /* ARTICLE_BEGIN  */
  YYSYMBOL_ARTICLE_END = 34,               /* ARTICLE_END  */
  YYSYMBOL_ASIDE_BEGIN = 35,               /* ASIDE_BEGIN  */
  YYSYMBOL_ASIDE_END = 36,                 /* ASIDE_END  */
  YYSYMBOL_FOOTER_BEGIN = 37,              /* FOOTER_BEGIN  */
  YYSYMBOL_FOOTER_END = 38,                /* FOOTER_END  */
  YYSYMBOL_A_BEGIN = 39,                   /* A_BEGIN  */
  YYSYMBOL_A_END = 40,                     /* A_END  */
  YYSYMBOL_STRONG_BEGIN = 41,              /* STRONG_BEGIN  */
  YYSYMBOL_STRONG_END = 42,                /* STRONG_END  */
  YYSYMBOL_EM_BEGIN = 43,                  /* EM_BEGIN  */
  YYSYMBOL_EM_END = 44,                    /* EM_END  */
  YYSYMBOL_U_BEGIN = 45,                   /* U_BEGIN  */
  YYSYMBOL_U_END = 46,                     /* U_END  */
  YYSYMBOL_SMALL_BEGIN = 47,               /* SMALL_BEGIN  */
  YYSYMBOL_SMALL_END = 48,                 /* SMALL_END  */
  YYSYMBOL_BLOCKQUOTE_BEGIN = 49,          /* BLOCKQUOTE_BEGIN  */
  YYSYMBOL_BLOCKQUOTE_END = 50,            /* BLOCKQUOTE_END  */
  YYSYMBOL_PRE_BEGIN = 51,                 /* PRE_BEGIN  */
  YYSYMBOL_PRE_END = 52,                   /* PRE_END  */
  YYSYMBOL_CODE_BEGIN = 53,                /* CODE_BEGIN  */
  YYSYMBOL_CODE_END = 54,                  /* CODE_END  */
  YYSYMBOL_OL_BEGIN = 55,                  /* OL_BEGIN  */
  YYSYMBOL_OL_END = 56,                    /* OL_END  */
  YYSYMBOL_TEXT = 57,                      /* TEXT  */
  YYSYMBOL_SPACE = 58,                     /* SPACE  */
  YYSYMBOL_NEWLINE = 59,                   /* NEWLINE  */
  YYSYMBOL_HREF = 60,                      /* HREF  */
  YYSYMBOL_IMG_BEGIN = 61,                 /* IMG_BEGIN  */
  YYSYMBOL_SRC = 62,                       /* SRC  */
  YYSYMBOL_ALT = 63,                       /* ALT  */
  YYSYMBOL_LANGBRACKET = 64,               /* LANGBRACKET  */
  YYSYMBOL_RANGBRACKET = 65,               /* RANGBRACKET  */
  YYSYMBOL_EQUAL = 66,                     /* EQUAL  */
  YYSYMBOL_DOUBLEINVERTEDCOMMA = 67,       /* DOUBLEINVERTEDCOMMA  */
  YYSYMBOL_WHITESPACE = 68,                /* WHITESPACE  */
  YYSYMBOL_PREAMBLE = 69,                  /* PREAMBLE  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_start = 71,                     /* start  */
  YYSYMBOL_preabmle = 72,                  /* preabmle  */
  YYSYMBOL_html = 73,                      /* html  */
  YYSYMBOL_head = 74,                      /* head  */
  YYSYMBOL_title = 75,                     /* title  */
  YYSYMBOL_titleContent = 76,              /* titleContent  */
  YYSYMBOL_body = 77,                      /* body  */
  YYSYMBOL_textContent = 78,               /* textContent  */
  YYSYMBOL_text = 79,                      /* text  */
  YYSYMBOL_bodyContent = 80,               /* bodyContent  */
  YYSYMBOL_semanticTags = 81,              /* semanticTags  */
  YYSYMBOL_textTags = 82,                  /* textTags  */
  YYSYMBOL_textTag = 83,                   /* textTag  */
  YYSYMBOL_pretag = 84,                    /* pretag  */
  YYSYMBOL_list = 85,                      /* list  */
  YYSYMBOL_listElements = 86,              /* listElements  */
  YYSYMBOL_anchor = 87,                    /* anchor  */
  YYSYMBOL_image = 88,                     /* image  */
  YYSYMBOL_imageAttributes = 89            /* imageAttributes  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   171

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   108,   114,   114,   116,   122,   129,   136,
     141,   146,   149,   155,   159,   167,   175,   180,   186,   190,
     194,   198,   202,   206,   210,   221,   231,   241,   251,   261,
     271,   279,   287,   299,   308,   317,   321,   329,   337,   345,
     353,   363,   374,   386,   391,   397,   407,   417,   428,   439,
     448,   455,   459,   463,   471,   479,   487,   496,   507,   519,
     521,   525,   531,   536,   542,   552,   557,   562,   566
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "HTML_BEGIN",
  "HTML_END", "HEAD_BEGIN", "HEAD_END", "TITLE_BEGIN", "TITLE_END",
  "BODY_BEGIN", "BODY_END", "NAV_BEGIN", "NAV_END", "UL_BEGIN", "UL_END",
  "LI_BEGIN", "LI_END", "HEADER_BEGIN", "HEADER_END", "H1_BEGIN", "H1_END",
  "H2_BEGIN", "H2_END", "H3_BEGIN", "H3_END", "H4_BEGIN", "H4_END",
  "H5_BEGIN", "H5_END", "PARA_BEGIN", "PARA_END", "SECTION_BEGIN",
  "SECTION_END", "ARTICLE_BEGIN", "ARTICLE_END", "ASIDE_BEGIN",
  "ASIDE_END", "FOOTER_BEGIN", "FOOTER_END", "A_BEGIN", "A_END",
  "STRONG_BEGIN", "STRONG_END", "EM_BEGIN", "EM_END", "U_BEGIN", "U_END",
  "SMALL_BEGIN", "SMALL_END", "BLOCKQUOTE_BEGIN", "BLOCKQUOTE_END",
  "PRE_BEGIN", "PRE_END", "CODE_BEGIN", "CODE_END", "OL_BEGIN", "OL_END",
  "TEXT", "SPACE", "NEWLINE", "HREF", "IMG_BEGIN", "SRC", "ALT",
  "LANGBRACKET", "RANGBRACKET", "EQUAL", "DOUBLEINVERTEDCOMMA",
  "WHITESPACE", "PREAMBLE", "$accept", "start", "preabmle", "html", "head",
  "title", "titleContent", "body", "textContent", "text", "bodyContent",
  "semanticTags", "textTags", "textTag", "pretag", "list", "listElements",
  "anchor", "image", "imageAttributes", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,     2,   -74,   -74,    10,    -2,   -74,    23,    38,   -74,
     -74,   -74,    37,   -74,    44,   -33,    36,   -74,   -74,   -74,
     -74,   -74,    83,   -74,    83,    31,    83,   110,   110,   110,
     110,   110,   110,    83,    83,    83,    83,    -6,   110,   110,
     110,   110,   110,   -74,   110,    31,   -74,   -74,   -74,   -35,
      46,    83,   -74,    45,    83,    20,    40,   110,    -6,   110,
     110,   110,   110,   110,   -74,   110,   -74,   -74,   -74,   -35,
      39,   110,   -74,    41,    51,    34,    33,    32,    49,    30,
      29,    47,   -74,    42,    35,    43,    53,    28,    55,   110,
      24,   -12,   -74,   -74,    19,    21,   -74,   -74,   -74,    70,
     -74,    83,   -74,    59,    50,    61,    48,    63,    65,    57,
     110,    67,    26,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -36,   -74,   -74,   -74,   -74,   -74,
     -74,    73,   -74,   -74,   -33,   -33,   -74,   -35,   -74,    77,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,    75,   -74,   -74,
      52,   -74,   -74,   -74,   -74,    83,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     4,     5,     0,     0,     3,     0,     0,     1,
       2,    11,     0,     6,     0,     9,     0,     8,    13,    14,
      15,    12,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,     0,    40,    41,    42,    66,
       0,    17,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,    56,    57,    58,    66,
       0,    44,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,    11,     0,     0,    10,    16,    19,     0,
      61,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    43,    25,    26,    27,    28,    29,
      20,    21,    22,    23,     0,    35,    30,    31,    37,    39,
      32,     0,    38,    60,    67,    68,    36,    66,    63,     0,
      45,    51,    46,    47,    53,    55,    48,     0,    54,    52,
       0,    33,    65,    62,    49,     0,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,    90,   -74,   -74,   -74,   -74,   -74,   -74,   -73,   -74,
     -18,   -74,     9,   -74,    71,   -22,    56,    85,   -64,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     8,    12,    14,    23,    15,    21,
      50,    51,    70,    71,    89,    72,    55,    83,    94,    95
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,     1,    52,   101,    52,   112,    53,     7,    56,   124,
       9,    52,    52,    52,    52,    78,    79,    80,    81,   134,
     135,    18,    19,    20,    18,    19,    20,    92,    93,    52,
      11,   150,    52,    97,   100,   101,    99,    73,    74,    75,
      76,    77,    13,    16,   133,    22,    54,    84,    85,    86,
      87,    88,    17,    90,    82,     2,    96,    98,   102,   113,
     117,   118,   119,   115,   121,   122,   103,     3,   105,   106,
     107,   108,   109,   152,   111,   116,   129,   126,   132,    52,
     114,   120,   125,   139,   136,   123,   138,   127,   137,   140,
     141,   149,   143,   153,    24,    10,    25,     0,   131,   128,
      26,    91,    27,   142,    28,   130,    29,   146,    30,   144,
      31,     0,    32,   145,    33,     0,    34,   155,    35,   147,
      36,   148,    37,    25,    38,   151,    39,   154,    40,     0,
      41,     0,    42,    52,    43,   110,    44,   156,    45,    57,
      46,    47,    48,   104,    49,     0,     0,     0,     0,    58,
       0,    59,     0,    60,     0,    61,     0,    62,     0,    63,
       0,    64,     0,    65,     0,    45,     0,    66,    67,    68,
       0,    69
};

static const yytype_int16 yycheck[] =
{
      22,     3,    24,    15,    26,    69,    24,     5,    26,    82,
       0,    33,    34,    35,    36,    33,    34,    35,    36,    92,
      93,    57,    58,    59,    57,    58,    59,    62,    63,    51,
       7,    67,    54,    51,    14,    15,    54,    28,    29,    30,
      31,    32,     4,     6,    56,     9,    15,    38,    39,    40,
      41,    42,     8,    44,    60,    57,    10,    12,    18,    20,
      26,    28,    30,    22,    34,    36,    57,    69,    59,    60,
      61,    62,    63,   137,    65,    24,    48,    42,    54,   101,
      71,    32,    40,   101,    65,    38,    16,    44,    67,    30,
      40,    65,    44,    16,    11,     5,    13,    -1,    89,    46,
      17,    45,    19,    42,    21,    50,    23,    50,    25,    46,
      27,    -1,    29,    48,    31,    -1,    33,    65,    35,   110,
      37,    54,    39,    13,    41,    52,    43,    52,    45,    -1,
      47,    -1,    49,   155,    51,    64,    53,   155,    55,    29,
      57,    58,    59,    58,    61,    -1,    -1,    -1,    -1,    39,
      -1,    41,    -1,    43,    -1,    45,    -1,    47,    -1,    49,
      -1,    51,    -1,    53,    -1,    55,    -1,    57,    58,    59,
      -1,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    57,    69,    71,    72,    73,     5,    74,     0,
      71,     7,    75,     4,    76,    78,     6,     8,    57,    58,
      59,    79,     9,    77,    11,    13,    17,    19,    21,    23,
      25,    27,    29,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    53,    55,    57,    58,    59,    61,
      80,    81,    85,    80,    15,    86,    80,    29,    39,    41,
      43,    45,    47,    49,    51,    53,    57,    58,    59,    61,
      82,    83,    85,    82,    82,    82,    82,    82,    80,    80,
      80,    80,    60,    87,    82,    82,    82,    82,    82,    84,
      82,    86,    62,    63,    88,    89,    10,    80,    12,    80,
      14,    15,    18,    82,    87,    82,    82,    82,    82,    82,
      84,    82,    88,    20,    82,    22,    24,    26,    28,    30,
      32,    34,    36,    38,    78,    40,    42,    44,    46,    48,
      50,    82,    54,    56,    78,    78,    65,    67,    16,    80,
      30,    40,    42,    44,    46,    48,    50,    82,    54,    65,
      67,    52,    88,    16,    52,    65,    80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    73,    74,    75,    76,
      77,    78,    78,    79,    79,    79,    80,    80,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      85,    85,    86,    86,    87,    88,    88,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     3,     4,     3,     1,
       3,     0,     2,     1,     1,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     2,     1,     3,     3,     3,     3,     4,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     0,
       3,     3,     4,     3,     5,     3,     0,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: preabmle start  */
#line 107 "parser.y"
                                                                    {}
#line 1265 "parser.cpp"
    break;

  case 3: /* start: html  */
#line 108 "parser.y"
                                                                    {
                                                                        root = new Node(Start);
                                                                        root->productions.push_back((yyvsp[0].node));
                                                                    }
#line 1274 "parser.cpp"
    break;

  case 5: /* preabmle: PREAMBLE  */
#line 114 "parser.y"
                                                                    {}
#line 1280 "parser.cpp"
    break;

  case 6: /* html: HTML_BEGIN head HTML_END  */
#line 116 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Html);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1289 "parser.cpp"
    break;

  case 7: /* head: HEAD_BEGIN title HEAD_END body  */
#line 122 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Head);
                                                                        (yyval.node)->productions.push_back((yyvsp[-2].node));
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                    }
#line 1299 "parser.cpp"
    break;

  case 8: /* title: TITLE_BEGIN titleContent TITLE_END  */
#line 129 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Title);
                                                                        (yyval.node)->setValue((yyvsp[-1].node)->getValue());
                                                                    }
#line 1308 "parser.cpp"
    break;

  case 9: /* titleContent: textContent  */
#line 136 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TitleContent);
                                                                        (yyval.node)->setValue((yyvsp[0].node)->getValue());
                                                                    }
#line 1317 "parser.cpp"
    break;

  case 10: /* body: BODY_BEGIN bodyContent BODY_END  */
#line 141 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Body);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1326 "parser.cpp"
    break;

  case 11: /* textContent: %empty  */
#line 146 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextContent);
                                                                    }
#line 1334 "parser.cpp"
    break;

  case 12: /* textContent: textContent text  */
#line 149 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextContent);
                                                                        (yyval.node)->setValue(new std::string(std::string(*(yyvsp[-1].node)->getValue()) + *(yyvsp[0].node)->getValue()));
                                                                    }
#line 1343 "parser.cpp"
    break;

  case 13: /* text: TEXT  */
#line 155 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Text);
                                                                        (yyval.node)->setValue(new std::string(*(yyvsp[0].str)));
                                                                    }
#line 1352 "parser.cpp"
    break;

  case 14: /* text: SPACE  */
#line 159 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Space);
                                                                        if(isPre){
                                                                            (yyval.node)->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }else{
                                                                            (yyval.node)->setValue(new std::string(" "));
                                                                        }
                                                                    }
#line 1365 "parser.cpp"
    break;

  case 15: /* text: NEWLINE  */
#line 167 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(Newline);
                                                                        if(isPre){
                                                                            (yyval.node)->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }
                                                                    }
#line 1376 "parser.cpp"
    break;

  case 16: /* bodyContent: semanticTags bodyContent  */
#line 175 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(BodyContent);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                    }
#line 1386 "parser.cpp"
    break;

  case 17: /* bodyContent: semanticTags  */
#line 180 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(BodyContent);
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));   
                                                                    }
#line 1395 "parser.cpp"
    break;

  case 18: /* semanticTags: HEADER_BEGIN bodyContent HEADER_END  */
#line 186 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1404 "parser.cpp"
    break;

  case 19: /* semanticTags: NAV_BEGIN bodyContent NAV_END  */
#line 190 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1413 "parser.cpp"
    break;

  case 20: /* semanticTags: SECTION_BEGIN bodyContent SECTION_END  */
#line 194 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1422 "parser.cpp"
    break;

  case 21: /* semanticTags: ARTICLE_BEGIN bodyContent ARTICLE_END  */
#line 198 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1431 "parser.cpp"
    break;

  case 22: /* semanticTags: ASIDE_BEGIN bodyContent ASIDE_END  */
#line 202 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1440 "parser.cpp"
    break;

  case 23: /* semanticTags: FOOTER_BEGIN bodyContent FOOTER_END  */
#line 206 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1449 "parser.cpp"
    break;

  case 24: /* semanticTags: H1_BEGIN textTags H1_END  */
#line 210 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(H1);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);

                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1465 "parser.cpp"
    break;

  case 25: /* semanticTags: H2_BEGIN textTags H2_END  */
#line 221 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(H2);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1480 "parser.cpp"
    break;

  case 26: /* semanticTags: H3_BEGIN textTags H3_END  */
#line 231 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(H3);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1495 "parser.cpp"
    break;

  case 27: /* semanticTags: H4_BEGIN textTags H4_END  */
#line 241 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(H4);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1510 "parser.cpp"
    break;

  case 28: /* semanticTags: H5_BEGIN textTags H5_END  */
#line 251 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(H5);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1525 "parser.cpp"
    break;

  case 29: /* semanticTags: PARA_BEGIN textTags PARA_END  */
#line 261 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Paragraph);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1540 "parser.cpp"
    break;

  case 30: /* semanticTags: STRONG_BEGIN textTags STRONG_END  */
#line 271 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Strong);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1553 "parser.cpp"
    break;

  case 31: /* semanticTags: EM_BEGIN textTags EM_END  */
#line 279 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1566 "parser.cpp"
    break;

  case 32: /* semanticTags: BLOCKQUOTE_BEGIN textTags BLOCKQUOTE_END  */
#line 287 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Blockquote);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));

                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1583 "parser.cpp"
    break;

  case 33: /* semanticTags: PRE_BEGIN pretag textTags PRE_END  */
#line 299 "parser.y"
                                                                    {
                                                                        isPre = false;
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Pre);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1597 "parser.cpp"
    break;

  case 34: /* semanticTags: list  */
#line 308 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                        (yyval.node)->productions.push_back(newline);
                                                                    }
#line 1611 "parser.cpp"
    break;

  case 35: /* semanticTags: A_BEGIN anchor A_END  */
#line 317 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1620 "parser.cpp"
    break;

  case 36: /* semanticTags: IMG_BEGIN image RANGBRACKET  */
#line 321 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Image);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1633 "parser.cpp"
    break;

  case 37: /* semanticTags: U_BEGIN textTags U_END  */
#line 329 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1646 "parser.cpp"
    break;

  case 38: /* semanticTags: CODE_BEGIN textTags CODE_END  */
#line 337 "parser.y"
                                                                          {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Code);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1659 "parser.cpp"
    break;

  case 39: /* semanticTags: SMALL_BEGIN textTags SMALL_END  */
#line 345 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Small);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1672 "parser.cpp"
    break;

  case 40: /* semanticTags: TEXT  */
#line 353 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Text);

                                                                        temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                        
                                                                    }
#line 1687 "parser.cpp"
    break;

  case 41: /* semanticTags: SPACE  */
#line 363 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);
                                                                        Node* temp = new Node(Space);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }else{
                                                                            temp->setValue(new std::string(" "));
                                                                        }

                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1703 "parser.cpp"
    break;

  case 42: /* semanticTags: NEWLINE  */
#line 374 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Newline);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }

                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1718 "parser.cpp"
    break;

  case 43: /* textTags: textTag textTags  */
#line 386 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                    }
#line 1728 "parser.cpp"
    break;

  case 44: /* textTags: textTag  */
#line 391 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTags);
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                    }
#line 1737 "parser.cpp"
    break;

  case 45: /* textTag: PARA_BEGIN textTags PARA_END  */
#line 397 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Paragraph);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1752 "parser.cpp"
    break;

  case 46: /* textTag: STRONG_BEGIN textTags STRONG_END  */
#line 407 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Strong);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        Node* space = new Node(Space);
                                                                        space->setValue(new std::string(" "));
                                                                        (yyval.node)->productions.push_back(temp);
                                                                        temp->productions.push_back(space);
                                                                    }
#line 1767 "parser.cpp"
    break;

  case 47: /* textTag: EM_BEGIN textTags EM_END  */
#line 417 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Em);
                                                                        Node* space = new Node(Space);
                                                                        space->setValue(new std::string(" "));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(space);
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1783 "parser.cpp"
    break;

  case 48: /* textTag: BLOCKQUOTE_BEGIN textTags BLOCKQUOTE_END  */
#line 428 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Blockquote);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        temp->productions.push_back(newline);
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1799 "parser.cpp"
    break;

  case 49: /* textTag: PRE_BEGIN pretag textTags PRE_END  */
#line 439 "parser.y"
                                                                    {
                                                                        isPre = false;
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Pre);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1813 "parser.cpp"
    break;

  case 50: /* textTag: list  */
#line 448 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);
                                                                        (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        (yyval.node)->productions.push_back(newline);
                                                                    }
#line 1825 "parser.cpp"
    break;

  case 51: /* textTag: A_BEGIN anchor A_END  */
#line 455 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1834 "parser.cpp"
    break;

  case 52: /* textTag: IMG_BEGIN image RANGBRACKET  */
#line 459 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1843 "parser.cpp"
    break;

  case 53: /* textTag: U_BEGIN textTags U_END  */
#line 463 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1856 "parser.cpp"
    break;

  case 54: /* textTag: CODE_BEGIN textTags CODE_END  */
#line 471 "parser.y"
                                                                          {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Code);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1869 "parser.cpp"
    break;

  case 55: /* textTag: SMALL_BEGIN textTags SMALL_END  */
#line 479 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(SemanticTags);

                                                                        Node* temp = new Node(Small);
                                                                        temp->productions.push_back((yyvsp[-1].node));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1882 "parser.cpp"
    break;

  case 56: /* textTag: TEXT  */
#line 487 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Text);
                                                                        cout<<*(yyvsp[0].str)<<" "<<std::flush;
                                                                        temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        
                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1896 "parser.cpp"
    break;

  case 57: /* textTag: SPACE  */
#line 496 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);
                                                                        Node* temp = new Node(Space);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }else{
                                                                            temp->setValue(new std::string(" "));
                                                                        }

                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1912 "parser.cpp"
    break;

  case 58: /* textTag: NEWLINE  */
#line 507 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(TextTag);

                                                                        Node* temp = new Node(Newline);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*(yyvsp[0].str)));
                                                                        }

                                                                        (yyval.node)->productions.push_back(temp);
                                                                    }
#line 1927 "parser.cpp"
    break;

  case 59: /* pretag: %empty  */
#line 519 "parser.y"
             {isPre = true;}
#line 1933 "parser.cpp"
    break;

  case 60: /* list: OL_BEGIN listElements OL_END  */
#line 521 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(OList);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1942 "parser.cpp"
    break;

  case 61: /* list: UL_BEGIN listElements UL_END  */
#line 525 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(UList);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1951 "parser.cpp"
    break;

  case 62: /* listElements: listElements LI_BEGIN bodyContent LI_END  */
#line 531 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(ListElement);
                                                                        (yyval.node)->productions.push_back((yyvsp[-3].node));
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1961 "parser.cpp"
    break;

  case 63: /* listElements: LI_BEGIN bodyContent LI_END  */
#line 536 "parser.y"
                                                                    {
                                                                        (yyval.node) = new Node(ListElement);
                                                                        (yyval.node)->productions.push_back((yyvsp[-1].node));
                                                                    }
#line 1970 "parser.cpp"
    break;

  case 64: /* anchor: HREF textContent DOUBLEINVERTEDCOMMA RANGBRACKET bodyContent  */
#line 542 "parser.y"
                                                                                {
                                                                                    (yyval.node) = new Node(Anchor);
                                                                                    (yyval.node)->setValue((yyvsp[-3].node)->getValue());
                                                                                    Node* temp = new Node(AnchorText);
                                                                                    temp->productions.push_back((yyvsp[0].node));
                                                                                    (yyval.node)->productions.push_back(temp);
                                                                                    
                                                                                }
#line 1983 "parser.cpp"
    break;

  case 65: /* image: imageAttributes DOUBLEINVERTEDCOMMA image  */
#line 552 "parser.y"
                                                                    {
                                                                                    (yyval.node) = new Node(Image);
                                                                                    (yyval.node)->productions.push_back((yyvsp[-2].node));
                                                                                    (yyval.node)->productions.push_back((yyvsp[0].node));
                                                                                }
#line 1993 "parser.cpp"
    break;

  case 66: /* image: %empty  */
#line 557 "parser.y"
                                                                                {
                                                                                    (yyval.node) = new Node(Image);
                                                                                }
#line 2001 "parser.cpp"
    break;

  case 67: /* imageAttributes: SRC textContent  */
#line 562 "parser.y"
                                                                                {
                                                                                    (yyval.node) = new Node(Src);
                                                                                    (yyval.node)->setValue((yyvsp[0].node)->getValue());
                                                                                }
#line 2010 "parser.cpp"
    break;

  case 68: /* imageAttributes: ALT textContent  */
#line 566 "parser.y"
                                                                                {
                                                                                    (yyval.node) = new Node(Alt);
                                                                                    (yyval.node)->setValue((yyvsp[0].node)->getValue());
                                                                                }
#line 2019 "parser.cpp"
    break;


#line 2023 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 572 "parser.y"




void yyerror(const char *s){
    extern char *yytext;
    fprintf(stderr, "Error: %s at line token '%s'\n", s, yytext);
}

Node* getRoot(){
    return root;
}
