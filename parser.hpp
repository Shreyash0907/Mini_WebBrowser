/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "parser.y"

    #include <cstdio>
    #include <cstring>
    #include <string>
    #include <vector>
    #include "node.hpp"
    extern int yylex(void);
    static void yyerror(const char* s); 
    using namespace std;


#line 61 "parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    HTML_BEGIN = 258,              /* HTML_BEGIN  */
    HTML_END = 259,                /* HTML_END  */
    HEAD_BEGIN = 260,              /* HEAD_BEGIN  */
    HEAD_END = 261,                /* HEAD_END  */
    TITLE_BEGIN = 262,             /* TITLE_BEGIN  */
    TITLE_END = 263,               /* TITLE_END  */
    BODY_BEGIN = 264,              /* BODY_BEGIN  */
    BODY_END = 265,                /* BODY_END  */
    NAV_BEGIN = 266,               /* NAV_BEGIN  */
    NAV_END = 267,                 /* NAV_END  */
    UL_BEGIN = 268,                /* UL_BEGIN  */
    UL_END = 269,                  /* UL_END  */
    LI_BEGIN = 270,                /* LI_BEGIN  */
    LI_END = 271,                  /* LI_END  */
    HEADER_BEGIN = 272,            /* HEADER_BEGIN  */
    HEADER_END = 273,              /* HEADER_END  */
    H1_BEGIN = 274,                /* H1_BEGIN  */
    H1_END = 275,                  /* H1_END  */
    H2_BEGIN = 276,                /* H2_BEGIN  */
    H2_END = 277,                  /* H2_END  */
    H3_BEGIN = 278,                /* H3_BEGIN  */
    H3_END = 279,                  /* H3_END  */
    H4_BEGIN = 280,                /* H4_BEGIN  */
    H4_END = 281,                  /* H4_END  */
    H5_BEGIN = 282,                /* H5_BEGIN  */
    H5_END = 283,                  /* H5_END  */
    PARA_BEGIN = 284,              /* PARA_BEGIN  */
    PARA_END = 285,                /* PARA_END  */
    SECTION_BEGIN = 286,           /* SECTION_BEGIN  */
    SECTION_END = 287,             /* SECTION_END  */
    ARTICLE_BEGIN = 288,           /* ARTICLE_BEGIN  */
    ARTICLE_END = 289,             /* ARTICLE_END  */
    ASIDE_BEGIN = 290,             /* ASIDE_BEGIN  */
    ASIDE_END = 291,               /* ASIDE_END  */
    FOOTER_BEGIN = 292,            /* FOOTER_BEGIN  */
    FOOTER_END = 293,              /* FOOTER_END  */
    A_BEGIN = 294,                 /* A_BEGIN  */
    A_END = 295,                   /* A_END  */
    STRONG_BEGIN = 296,            /* STRONG_BEGIN  */
    STRONG_END = 297,              /* STRONG_END  */
    EM_BEGIN = 298,                /* EM_BEGIN  */
    EM_END = 299,                  /* EM_END  */
    U_BEGIN = 300,                 /* U_BEGIN  */
    U_END = 301,                   /* U_END  */
    SMALL_BEGIN = 302,             /* SMALL_BEGIN  */
    SMALL_END = 303,               /* SMALL_END  */
    BLOCKQUOTE_BEGIN = 304,        /* BLOCKQUOTE_BEGIN  */
    BLOCKQUOTE_END = 305,          /* BLOCKQUOTE_END  */
    PRE_BEGIN = 306,               /* PRE_BEGIN  */
    PRE_END = 307,                 /* PRE_END  */
    CODE_BEGIN = 308,              /* CODE_BEGIN  */
    CODE_END = 309,                /* CODE_END  */
    OL_BEGIN = 310,                /* OL_BEGIN  */
    OL_END = 311,                  /* OL_END  */
    TEXT = 312,                    /* TEXT  */
    SPACE = 313,                   /* SPACE  */
    NEWLINE = 314,                 /* NEWLINE  */
    HREF = 315,                    /* HREF  */
    IMG_BEGIN = 316,               /* IMG_BEGIN  */
    SRC = 317,                     /* SRC  */
    ALT = 318,                     /* ALT  */
    LANGBRACKET = 319,             /* LANGBRACKET  */
    RANGBRACKET = 320,             /* RANGBRACKET  */
    EQUAL = 321,                   /* EQUAL  */
    DOUBLEINVERTEDCOMMA = 322,     /* DOUBLEINVERTEDCOMMA  */
    WHITESPACE = 323               /* WHITESPACE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "parser.y"

    std::string* str; // Use std::string to specify the type correctly
    Node* node;

#line 151 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
