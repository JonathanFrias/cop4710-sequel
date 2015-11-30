%{
#include <stdio.h>
#include "sql.tab.h"

    extern C2(void)
    {
        int yylex(void);
    }

int line_num = 1;       
%}
Delimiter    [ \t]
WhiteSpace   {Delimiter}+
Letter       [A-Za-z]
Digit        [0-9]
%%
"CREATE"                 {return(CREATE);}
"DROP"                   {return(DROP);}
"LOAD"                   {return(LOAD);}
"SAVE"                   {return(SAVE);}
"COMMIT"                 {return(COMMIT);}
"DATABASE"               {return(DATABASE);}
"TABLE"                  {return(TABLE);}
"INSERT"                 {return(INSERT);}
"INTO"                   {return(INTO);}
"FROM"                   {return(FROM);}
"WHERE"                  {return(WHERE);}
"SET"                    {return(SET);}
"DELETE"                 {return(DELETE);}
"UPDATE"                 {return(UPDATE);}
"WUPDATE"                {return(WUPDATE);}
"SELECT"                 {return(SELECT);}
"WSELECT"                {return(WSELECT);}
"VALUES"                 {return(VALUES);}
"INTEGER"                {return(INTEGER);}
"NUMBER"                 {return(NUMBER);}
"CHARACTER"              {return(CHARACTER);}
"*"                      {return('*');}
"("                      {return('(');}
")"                      {return(')');}
"["                      {return('[');}
"]"                      {return(']');}
","                      {return(',');}
"<"                      {return(LT);}
">"                      {return(GT);}
"<="                     {return(LTEQ);}
">="                     {return(GTEQ);}
"="                      {return(EQ);}
";"                      {return(';');exit(0);}
":"                      {return(':');}
{Letter}({Digit}|{Letter})*                  {yylval.sval = strdup(yytext);return(ID);}
{Digit}+'.'{Digit}+                        {yylval.fval = atof(yytext);return(DEC);}
'-'{Digit}+'.'{Digit}+                   {yylval.fval = atof(yytext);return(DEC);}
{Digit}+                                     {yylval.ival = atoi(yytext);return(INT);}
'-'{Digit}+                                {yylval.ival = atoi(yytext);return(INT);}
"'"({Letter}|{Digit}|{WhiteSpace})+"'"   {yylval.sval = strdup(yytext);return(STR);}
"'"{Digit}{Digit}"/"{Digit}{Digit}"/"{Digit}{Digit}{Digit}{Digit}"'"   {return(DATEL);}
"'"{Digit}{Digit}"/"{Digit}{Digit}"/"{Digit}{Digit}"'"                 {return(DATESH);}
"'"{Digit}{Digit}':'{Digit}{Digit}':'{Digit}{Digit}"'"                 {return(TIME);}
{WhiteSpace}             ;
\n                     {return(ENDL);exit(0);}
.                        {printf("LEX REJECT\n");exit(0);}
%%
