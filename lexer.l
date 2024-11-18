%{
// #include HTMLParser.tab.h
#include <string>
#include "parser.hpp"
#include <iostream>

 

%}

          


/*!*
 * @brief Token for alphabet.
 */
ALPHABET                         [a-zA-Z]

/*!*
 * @brief  Token for numbers.
 */                         
NUMERIC                          [0-9]
PUNCTUATION                      [!\#\%\''()*+,\-./:;?@^_`~]

/**
 * @brief Token for word.
 */
WORD                             (({ALPHABET}|{NUMERIC})+({ALPHABET}|{NUMERIC})*)

/**
 * @brief Token for text.
 */
TEXT                             (({WORD}|{PUNCTUATION})+)
NEWLINE                          "\n"
LANGBRACKET                      "<"
RANGBRACKET                      ">"
HTML                             "html"
HEAD                             "head"
TITLE                            "title"
BODY                             "body"
NAV                              "nav"
UL                               "ul"
OL                               "ol"
HEADER                           "header"
H1                               "h1"
H2                               "h2"
H3                               "h3"
H4                               "h4"
H5                               "h5"
PARA                             "p"
SECTION                          "section"
ARTICLE                          "article"
ASIDE                            "aside"
FOOTER                           "footer"
STRONG                           "strong"
EM                               "em"
UNDERLINE                        "u"
SMALL                            "small"
BLOCKQUOTE                       "blockquote"
PRE                              "pre"
CODE                             "code"
SPACE                            [ ]
SLASH                            "/"
LI                               "li"
IMG                              "img"
A                                "a"
WHITESPACE                       (({SPACE}|{NEWLINE})+)
HREF                             "href"
EQUAL                            "="
SRC                              "src"
ALT                              "alt"
DOUBLEINVERTEDCOMMA              \"



%%
{LANGBRACKET}{HTML}{RANGBRACKET}{WHITESPACE}*                            { return HTML_BEGIN; }
{LANGBRACKET}{SLASH}{HTML}{RANGBRACKET}{WHITESPACE}*                     { return HTML_END; }
{LANGBRACKET}{HEAD}{RANGBRACKET}{WHITESPACE}*                            { return HEAD_BEGIN; }
{LANGBRACKET}{SLASH}{HEAD}{RANGBRACKET}{WHITESPACE}*                     { return HEAD_END; }
{LANGBRACKET}{TITLE}{RANGBRACKET}{WHITESPACE}*                           { return TITLE_BEGIN; }
{LANGBRACKET}{SLASH}{TITLE}{RANGBRACKET}{WHITESPACE}*                    { return TITLE_END; }
{LANGBRACKET}{BODY}{RANGBRACKET}{WHITESPACE}*                            { return BODY_BEGIN; }
{LANGBRACKET}{SLASH}{BODY}{RANGBRACKET}{WHITESPACE}*                     { return BODY_END; }
{LANGBRACKET}{NAV}{RANGBRACKET}{WHITESPACE}*                             { return NAV_BEGIN; }
{LANGBRACKET}{SLASH}{NAV}{RANGBRACKET}{WHITESPACE}*                      { return NAV_END; }
{LANGBRACKET}{UL}{RANGBRACKET}{WHITESPACE}*                              { return UL_BEGIN; }
{LANGBRACKET}{SLASH}{UL}{RANGBRACKET}{WHITESPACE}*                       { return UL_END; }
{LANGBRACKET}{LI}{RANGBRACKET}{WHITESPACE}*                              { return LI_BEGIN; }
{LANGBRACKET}{SLASH}{LI}{RANGBRACKET}{WHITESPACE}*                       { return LI_END; }
{LANGBRACKET}{HEADER}{RANGBRACKET}{WHITESPACE}*                          { return HEADER_BEGIN; }
{LANGBRACKET}{SLASH}{HEADER}{RANGBRACKET}{WHITESPACE}*                   { return HEADER_END; }
{LANGBRACKET}{H1}{RANGBRACKET}{WHITESPACE}*                              { return H1_BEGIN; }
{LANGBRACKET}{SLASH}{H1}{RANGBRACKET}{WHITESPACE}*                       { return H1_END; }
{LANGBRACKET}{H2}{RANGBRACKET}{WHITESPACE}*                              { return H2_BEGIN; }
{LANGBRACKET}{SLASH}{H2}{RANGBRACKET}{WHITESPACE}*                       { return H2_END; }
{LANGBRACKET}{H3}{RANGBRACKET}{WHITESPACE}*                              { return H3_BEGIN; }
{LANGBRACKET}{SLASH}{H3}{RANGBRACKET}{WHITESPACE}*                       { return H3_END; }
{LANGBRACKET}{H4}{RANGBRACKET}{WHITESPACE}*                              { return H4_BEGIN; }
{LANGBRACKET}{SLASH}{H4}{RANGBRACKET}{WHITESPACE}*                       { return H4_END; }
{LANGBRACKET}{H5}{RANGBRACKET}{WHITESPACE}*                              { return H5_BEGIN; }
{LANGBRACKET}{SLASH}{H5}{RANGBRACKET}{WHITESPACE}*                       { return H5_END; }
{LANGBRACKET}{PARA}{RANGBRACKET}{WHITESPACE}*                            { return PARA_BEGIN; }
{LANGBRACKET}{SLASH}{PARA}{RANGBRACKET}{WHITESPACE}*                     { return PARA_END; }
{LANGBRACKET}{SECTION}{RANGBRACKET}{WHITESPACE}*                         { return SECTION_BEGIN; }
{LANGBRACKET}{SLASH}{SECTION}{RANGBRACKET}{WHITESPACE}*                  { return SECTION_END; }
{LANGBRACKET}{ARTICLE}{RANGBRACKET}{WHITESPACE}*                         { return ARTICLE_BEGIN; }
{LANGBRACKET}{SLASH}{ARTICLE}{RANGBRACKET}{WHITESPACE}*                  { return ARTICLE_END; }
{LANGBRACKET}{ASIDE}{RANGBRACKET}{WHITESPACE}*                           { return ASIDE_BEGIN; }
{LANGBRACKET}{SLASH}{ASIDE}{RANGBRACKET}{WHITESPACE}*                    { return ASIDE_END; }
{LANGBRACKET}{FOOTER}{RANGBRACKET}{WHITESPACE}*                          { return FOOTER_BEGIN; }
{LANGBRACKET}{SLASH}{FOOTER}{RANGBRACKET}{WHITESPACE}*                   { return FOOTER_END; }
{LANGBRACKET}{A}{WHITESPACE}*                                            { return A_BEGIN;}
{SPACE}*{HREF}{SPACE}*={SPACE}*{DOUBLEINVERTEDCOMMA}                             { return HREF;}
{LANGBRACKET}{IMG}{WHITESPACE}*                                          { return IMG_BEGIN;}
{SPACE}*{SRC}{SPACE}*={SPACE}*{DOUBLEINVERTEDCOMMA}                              { return SRC;}
{SPACE}*{ALT}{SPACE}*={SPACE}*{DOUBLEINVERTEDCOMMA}                              { return ALT;}
{LANGBRACKET}{SLASH}{A}{RANGBRACKET}{WHITESPACE}*                        { return A_END; }
{LANGBRACKET}{STRONG}{RANGBRACKET}{WHITESPACE}*                          { return STRONG_BEGIN; }
{LANGBRACKET}{SLASH}{STRONG}{RANGBRACKET}{WHITESPACE}*                   { return STRONG_END; }
{LANGBRACKET}{EM}{RANGBRACKET}{WHITESPACE}*                              { return EM_BEGIN; }
{LANGBRACKET}{SLASH}{EM}{RANGBRACKET}{WHITESPACE}*                       { return EM_END; }
{LANGBRACKET}{UNDERLINE}{RANGBRACKET}{WHITESPACE}*                       { return U_BEGIN; }
{LANGBRACKET}{SLASH}{UNDERLINE}{RANGBRACKET}{WHITESPACE}*                { return U_END; }
{LANGBRACKET}{SMALL}{RANGBRACKET}{WHITESPACE}*                           { return SMALL_BEGIN; }
{LANGBRACKET}{SLASH}{SMALL}{RANGBRACKET}{WHITESPACE}*                    { return SMALL_END; }
{LANGBRACKET}{BLOCKQUOTE}{RANGBRACKET}{WHITESPACE}*                      { return BLOCKQUOTE_BEGIN; }
{LANGBRACKET}{SLASH}{BLOCKQUOTE}{RANGBRACKET}{WHITESPACE}*               { return BLOCKQUOTE_END; }
{LANGBRACKET}{PRE}{RANGBRACKET}{WHITESPACE}*                             { return PRE_BEGIN; }
{LANGBRACKET}{SLASH}{PRE}{RANGBRACKET}{WHITESPACE}*                      { return PRE_END; }
{LANGBRACKET}{CODE}{RANGBRACKET}{WHITESPACE}*                            { return CODE_BEGIN; }
{LANGBRACKET}{SLASH}{CODE}{RANGBRACKET}{WHITESPACE}*                     { return CODE_END; }
{LANGBRACKET}{OL}{RANGBRACKET}{WHITESPACE}*                              { return OL_BEGIN; }
{LANGBRACKET}{SLASH}{OL}{RANGBRACKET}{WHITESPACE}*                       { return OL_END; }
{LANGBRACKET}                                                            { return LANGBRACKET;}
{RANGBRACKET}                                                            { return RANGBRACKET;}
{EQUAL}                                                                  { return EQUAL;}
{SPACE}+                                                                 { 
                                                                            yylval.str = new std::string(yytext);
                                                                            return SPACE; 
                                                                        }
{NEWLINE}+                                                               { 
                                                                            printf("newline");
                                                                            yylval.str = new std::string(yytext);
                                                                            return NEWLINE; 
                                                                        }
{TEXT}                                                                   { 
                                                                            yylval.str = new std::string(yytext);
                                                                            return TEXT;
                                                                         }
{DOUBLEINVERTEDCOMMA}                                                    { return DOUBLEINVERTEDCOMMA; }
"<!DOCTYPE"                                                             { return PREAMBLE;}
.                                                                        { }

%%

#undef yywrap

int yywrap(){
    return 1;
}
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

