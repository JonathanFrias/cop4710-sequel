%{
#include <stdio.h>
#include "sql.tab.h"
/*
extern C2(void) {
  int yylex(void);
}
*/
int line_number = 1;

%}

Delimiter    [ \t]
WhiteSpace   {Delimiter}+
Letter       [A-Za-z]
Digit        [0-9]
Integer      {Digit}+
Float        {Digit}+"."{Digit}+
Date	     (0[1-9]|1[012])"/"(0[1-9]|[12][0-9]|3[01])"/"[0-9][0-9][0-9][0-9]
Other	     [-!@#$%&+:"~`]


%%
{WhiteSpace}				 { ; }
[Cc][Rr][Ee][Aa][Tt][Ee]                 {printf("token: CREATE\n");return(CREATE);}
[Dd][Rr][Oo][Pp]                         {printf("token: DROP\n");return(DROP);}
[Ll][Oo][Aa][Dd]                         {printf("token: LOAD\n");return(LOAD);}
[Ss][Aa][Vv][Ee]                         {printf("token: SAVE\n");return(SAVE);}
[Dd][Aa][Tt][Aa][Bb][Aa][Ss][Ee]         {printf("token: DATABASE\n");return(DATABASE);}
[Tt][Aa][Bb][Ll][Ee]                     {printf("token: TABLE\n");return(TABLE);}
[Ii][Nn][Ss][Ee][Rr][Tt]                 {printf("token: INSERT\n");return(INSERT);}
[Ii][Nn][Tt][Oo]                         {printf("token: INTO\n");return(INTO);}
[Ff][Rr][Oo][Mm]                         {printf("token: FROM\n");return(FROM);}
[Ww][Hh][Ee][Rr][Ee]                     {printf("token: WHERE\n");return(WHERE);}
[Ss][Ee][Tt]                    	 {printf("token: SET\n");return(SET);}
[Dd][Ee][Ll][Ee][Tt][Ee]                 {printf("token: DELETE\n");return(DELETE);}
[Uu][Pp][Dd][Aa][Tt][Ee]                 {printf("token: UPDATE\n");return(UPDATE);}
[Ss][Ee][Ll][Ee][Cc][Tt]                 {printf("token: SELECT\n");return(SELECT);}
[Ww][Ss][Ee][Ll][Ee][Cc][Tt]             {printf("token: WSELECT\n");return(WSELECT);}
[Vv][Aa][Ll][Uu][Ee][Ss]                 {printf("token: VALUES\n");return(VALUES);}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]             {printf("token: INTEGER\n");return(INTEGER);}
[Nn][Uu][Mm][Bb][Ee][Rr]                 {printf("token: NUMBER\n");return(NUMBER);}
[Cc][Hh][Aa][Rr][Aa][Cc][Tt][Ee][Rr]     {printf("token: CHARACTER\n");return(CHARACTER);}
[Dd][Aa][Tt][Ee]			 {printf("token: DATE\n");return(DATE);}
[a-zA-Z][a-zA-Z0-9_]*			 {printf("token: ID %s\n", yytext);return(ID);}
"*"                      {printf("token: AST\n");return(AST);}
"("                      {printf("token: RP\n");return(LP);}
")"                      {printf("token: LP\n");return(RP);}
","                      {printf("token: COMMA\n");return(COMMA);}
"<"                      {printf("token: LT\n");return(LT);}
">"                      {printf("token: GT\n");return(GT);}
"<="                     {printf("token: LTEQ\n");return(LTEQ);}
">="                     {printf("token: GTEQ\n");return(GTEQ);}
"=="			 {printf("token: EQEQ\n");return(EQEQ);}
"!="			 {printf("token: NOTEQ\n");return(NOTEQ);}
";"                      {printf("token: SEMIC\n");return(SEMIC);}
"="			 {printf("token: EQ\n");return(EQ);}
{Float}                  {printf("token: DEC\n");return(DEC);}
"-"{Float}               {printf("token: DEC\n");return(DEC);}
{Integer}                 {printf("token: INT\n");return(INT);}
"-"{Integer}              {printf("token: INT\n");return(INT);}
"'"[ \ta-zA-Z0-9]+"'"   {printf("token: STR\n");return(STR);}
{Date}		         {printf("token: DATETYPE\n");return(DATETYPE);}
\n			 { ; } 
.	                 {printf("Character %s not tokenized\n", yytext);return 0;}
%%

int yywrap(void) {

}

int yyparse(void) {
  yylex();
  return 0;
}
