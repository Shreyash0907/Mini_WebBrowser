%debug
%{
    #include <string>
    #include <vector>
    extern int yylineno;
    using namespace std; // Bringing std namespace into scope
    #include "node.hpp"
    #include <cstring>
    Node* root;
    bool isPre = false;
%}


%code requires {
    #include <cstdio>
    #include <cstring>
    #include <string>
    #include <vector>
    #include "node.hpp"
    extern int yylex(void);
    static void yyerror(const char* s); 
    using namespace std;

}

%union {
    std::string* str; // Use std::string to specify the type correctly
    Node* node;
}


%token HTML_BEGIN
%token HTML_END
%token HEAD_BEGIN
%token HEAD_END
%token TITLE_BEGIN
%token TITLE_END
%token BODY_BEGIN
%token BODY_END
%token NAV_BEGIN
%token NAV_END
%token UL_BEGIN
%token UL_END
%token LI_BEGIN
%token LI_END
%token HEADER_BEGIN
%token HEADER_END
%token H1_BEGIN
%token H1_END
%token H2_BEGIN
%token H2_END
%token H3_BEGIN
%token H3_END
%token H4_BEGIN
%token H4_END
%token H5_BEGIN
%token H5_END
%token PARA_BEGIN
%token PARA_END
%token SECTION_BEGIN
%token SECTION_END
%token ARTICLE_BEGIN
%token ARTICLE_END
%token ASIDE_BEGIN
%token ASIDE_END
%token FOOTER_BEGIN
%token FOOTER_END
%token A_BEGIN
%token A_END
%token STRONG_BEGIN
%token STRONG_END
%token EM_BEGIN
%token EM_END
%token U_BEGIN
%token U_END
%token SMALL_BEGIN
%token SMALL_END
%token BLOCKQUOTE_BEGIN
%token BLOCKQUOTE_END
%token PRE_BEGIN
%token PRE_END
%token CODE_BEGIN
%token CODE_END
%token OL_BEGIN
%token OL_END
%token <str> TEXT SPACE NEWLINE
%token HREF
%token IMG_BEGIN
%token SRC
%token ALT
%token LANGBRACKET
%token RANGBRACKET
%token EQUAL
%token DOUBLEINVERTEDCOMMA
%token WHITESPACE
%token PREAMBLE

%type<node> start html head title titleContent body textContent text bodyContent semanticTags textTags textTag list listElements anchor image imageAttributes



%start start

%%


    start : preabmle start                                          {}
            | html                                                  {
                                                                        root = new Node(Start);
                                                                        root->productions.push_back($1);
                                                                    }
            ;

    preabmle : TEXT| PREAMBLE                                       {}
                ;
    html : HTML_BEGIN head HTML_END                                 {
                                                                        $$ = new Node(Html);
                                                                        $$->productions.push_back($2);
                                                                    }
            ;

    head : HEAD_BEGIN title HEAD_END body                           {
                                                                        $$ = new Node(Head);
                                                                        $$->productions.push_back($2);
                                                                        $$->productions.push_back($4);
                                                                    }
        ;
    
    title : TITLE_BEGIN titleContent TITLE_END                      {
                                                                        $$ = new Node(Title);
                                                                        $$->setValue($2->getValue());
                                                                    }
        ;


    titleContent : textContent                                      {
                                                                        $$ = new Node(TitleContent);
                                                                        $$->setValue($1->getValue());
                                                                    }

    body : BODY_BEGIN bodyContent BODY_END                          {
                                                                        $$ = new Node(Body);
                                                                        $$->productions.push_back($2);
                                                                    }

    textContent :                                                   {
                                                                        $$ = new Node(TextContent);
                                                                    }
                | textContent text                                  {
                                                                        $$ = new Node(TextContent);
                                                                        $$->setValue(new std::string(std::string(*$1->getValue()) + *$2->getValue()));
                                                                    }
                ;
    
    text : TEXT                                                     {
                                                                        $$ = new Node(Text);
                                                                        $$->setValue(new std::string(*$1));
                                                                    }
            | SPACE                                                 {
                                                                        $$ = new Node(Space);
                                                                        if(isPre){
                                                                            $$->setValue(new std::string(*$1));
                                                                        }else{
                                                                            $$->setValue(new std::string(" "));
                                                                        }
                                                                    }
            | NEWLINE                                               {
                                                                        $$ = new Node(Newline);
                                                                        if(isPre){
                                                                            $$->setValue(new std::string(*$1));
                                                                        }
                                                                    }    
            ;

    bodyContent : semanticTags bodyContent                          {
                                                                        $$ = new Node(BodyContent);
                                                                        $$->productions.push_back($1);
                                                                        $$->productions.push_back($2);
                                                                    }
                | semanticTags                                      {
                                                                        $$ = new Node(BodyContent);
                                                                        $$->productions.push_back($1);   
                                                                    }
                ;
 
    semanticTags : HEADER_BEGIN bodyContent HEADER_END              {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | NAV_BEGIN bodyContent NAV_END                     {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | SECTION_BEGIN bodyContent SECTION_END             {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | ARTICLE_BEGIN bodyContent ARTICLE_END             {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | ASIDE_BEGIN bodyContent ASIDE_END                 {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | FOOTER_BEGIN bodyContent FOOTER_END               {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | H1_BEGIN textTags H1_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(H1);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);

                                                                        $$->productions.push_back(temp);
                                                                    }
                | H2_BEGIN textTags H2_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(H2);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | H3_BEGIN textTags H3_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(H3);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | H4_BEGIN textTags H4_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(H4);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | H5_BEGIN textTags H5_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(H5);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | PARA_BEGIN textTags PARA_END                      {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Paragraph);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | STRONG_BEGIN textTags STRONG_END                  {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Strong);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | EM_BEGIN textTags EM_END                          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | BLOCKQUOTE_BEGIN textTags BLOCKQUOTE_END          {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Blockquote);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));

                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | PRE_BEGIN pretag textTags PRE_END                 {
                                                                        isPre = false;
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Pre);
                                                                        temp->productions.push_back($3);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | list                                              {
                                                                        $$ = new Node(SemanticTags);

                                                                        
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        $$->productions.push_back($1);
                                                                        $$->productions.push_back(newline);
                                                                    }
                | A_BEGIN anchor A_END                              {
                                                                        $$ = new Node(SemanticTags);
                                                                        $$->productions.push_back($2);
                                                                    }
                | IMG_BEGIN image RANGBRACKET                       {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Image);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | U_BEGIN textTags U_END                            {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | CODE_BEGIN textTags CODE_END                            {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Code);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | SMALL_BEGIN textTags SMALL_END                    {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Small);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | TEXT                                              {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Text);

                                                                        temp->setValue(new std::string(*$1));
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                        
                                                                    }
                | SPACE                                             {
                                                                        $$ = new Node(SemanticTags);
                                                                        Node* temp = new Node(Space);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*$1));
                                                                        }else{
                                                                            temp->setValue(new std::string(" "));
                                                                        }

                                                                        $$->productions.push_back(temp);
                                                                    }
                | NEWLINE                                           {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Newline);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*$1));
                                                                        }

                                                                        $$->productions.push_back(temp);
                                                                    }
                    ;

    textTags : textTag textTags                                     {
                                                                        $$ = new Node(TextTags);
                                                                        $$->productions.push_back($1);
                                                                        $$->productions.push_back($2);
                                                                    }
            | textTag                                               {
                                                                        $$ = new Node(TextTags);
                                                                        $$->productions.push_back($1);
                                                                    }
            ;

    textTag : PARA_BEGIN textTags PARA_END                          {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Paragraph);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        $$->productions.push_back(temp);
                                                                    }
                | STRONG_BEGIN textTags STRONG_END                  {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Strong);
                                                                        temp->productions.push_back($2);
                                                                        Node* space = new Node(Space);
                                                                        space->setValue(new std::string(" "));
                                                                        $$->productions.push_back(temp);
                                                                        temp->productions.push_back(space);
                                                                    }
                | EM_BEGIN textTags EM_END                          {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Em);
                                                                        Node* space = new Node(Space);
                                                                        space->setValue(new std::string(" "));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(space);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | BLOCKQUOTE_BEGIN textTags BLOCKQUOTE_END          {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Blockquote);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        temp->productions.push_back($2);
                                                                        temp->productions.push_back(newline);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | PRE_BEGIN pretag textTags PRE_END                 {
                                                                        isPre = false;
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Pre);
                                                                        temp->productions.push_back($3);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | list                                              {
                                                                        $$ = new Node(TextTag);
                                                                        $$->productions.push_back($1);
                                                                        Node* newline = new Node(Newline);
                                                                        newline->setValue(new std::string("\n"));
                                                                        $$->productions.push_back(newline);
                                                                    }
                | A_BEGIN anchor A_END                              {
                                                                        $$ = new Node(TextTag);
                                                                        $$->productions.push_back($2);
                                                                    }
                | IMG_BEGIN image RANGBRACKET                       {
                                                                        $$ = new Node(TextTag);
                                                                        $$->productions.push_back($2);
                                                                    }
                | U_BEGIN textTags U_END                            {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Em);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | CODE_BEGIN textTags CODE_END                            {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Code);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | SMALL_BEGIN textTags SMALL_END                    {
                                                                        $$ = new Node(SemanticTags);

                                                                        Node* temp = new Node(Small);
                                                                        temp->productions.push_back($2);
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | TEXT                                              {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Text);
                                                                        cout<<*$1<<" "<<std::flush;
                                                                        temp->setValue(new std::string(*$1));
                                                                        
                                                                        $$->productions.push_back(temp);
                                                                    }
                | SPACE                                             {
                                                                        $$ = new Node(TextTag);
                                                                        Node* temp = new Node(Space);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*$1));
                                                                        }else{
                                                                            temp->setValue(new std::string(" "));
                                                                        }

                                                                        $$->productions.push_back(temp);
                                                                    }
                | NEWLINE                                           {
                                                                        $$ = new Node(TextTag);

                                                                        Node* temp = new Node(Newline);
                                                                        if(isPre){
                                                                            temp->setValue(new std::string(*$1));
                                                                        }

                                                                        $$->productions.push_back(temp);
                                                                    }
                ;
    
    pretag : {isPre = true;};

    list : OL_BEGIN listElements OL_END                             {
                                                                        $$ = new Node(OList);
                                                                        $$->productions.push_back($2);
                                                                    }
        | UL_BEGIN listElements UL_END                              {
                                                                        $$ = new Node(UList);
                                                                        $$->productions.push_back($2);
                                                                    }
        ;
    
    listElements : listElements LI_BEGIN bodyContent LI_END         {
                                                                        $$ = new Node(ListElement);
                                                                        $$->productions.push_back($1);
                                                                        $$->productions.push_back($3);
                                                                    }
                 | LI_BEGIN bodyContent LI_END                      {
                                                                        $$ = new Node(ListElement);
                                                                        $$->productions.push_back($2);
                                                                    }
                 ;

    anchor : HREF textContent DOUBLEINVERTEDCOMMA RANGBRACKET bodyContent       {
                                                                                    $$ = new Node(Anchor);
                                                                                    $$->setValue($2->getValue());
                                                                                    Node* temp = new Node(AnchorText);
                                                                                    temp->productions.push_back($5);
                                                                                    $$->productions.push_back(temp);
                                                                                    
                                                                                }
                ;

    image : imageAttributes DOUBLEINVERTEDCOMMA image               {
                                                                                    $$ = new Node(Image);
                                                                                    $$->productions.push_back($1);
                                                                                    $$->productions.push_back($3);
                                                                                }
            |                                                                   {
                                                                                    $$ = new Node(Image);
                                                                                }
            ;

    imageAttributes : SRC textContent                                           {
                                                                                    $$ = new Node(Src);
                                                                                    $$->setValue($2->getValue());
                                                                                }    
                    | ALT textContent                                           {
                                                                                    $$ = new Node(Alt);
                                                                                    $$->setValue($2->getValue());
                                                                                } 
                    ;

%%



void yyerror(const char *s){
    extern char *yytext;
    fprintf(stderr, "Error: %s at line token '%s'\n", s, yytext);
}

Node* getRoot(){
    return root;
}