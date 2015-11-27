%{
#include <stdio.h>
#include <stdlib.h>

int intval;

void yyerror(const char *s)
{
    fprintf(stderr, "REJECT: %s\n", s);
}

extern C(void)
{
        int yylex(void);  

        int yywrap()
        {
		exit(0);
        }

}
%}

%union{
   int ival;
   float fval;
   char *sval;
}
%start START
%token <sval> ID
%token <ival> INT
%token <fval> DEC
%token <sval> STR
%token CREATE DROP LOAD SAVE COMMIT DATABASE TABLE INSERT INTO FROM
%token WHERE SET DELETE UPDATE WUPDATE SELECT WSELECT VALUES
%token DATEL DATESH TIME NUMBER CHARACTER INTEGER
%token LT GT LTEQ GTEQ EQ ENDL
%%
START          : COMMAND_LIST ENDL{printf("Query is valid...\n");exit(0);};
COMMAND_LIST   : COMMAND COMMAND_LIST2
COMMAND_LIST2  : COMMAND COMMAND_LIST2 | /* EMPTY */
COMMAND        : SYSTEM_COMMAND | DDL_COMMAND | DML_COMMAND  
SYSTEM_COMMAND : CREATE_DATABASE_COMMAND
                 | DROP_DATABASE_COMMAND
                 | COMMIT_COMMAND
                 | SAVE_COMMAND
                 | LOAD_DATABASE_COMMAND   

DDL_COMMAND    : CREATE_TABLE_COMMAND
                 | DROP_TABLE_COMMAND

DML_COMMAND    : INSERT_INTO_COMMAND
                 | DELETE_FROM_COMMAND
                 | UPDATE_COMMAND
                 | W_UPDATE_COMMAND
                 | SELECT_COMMAND
                 | W_SELECT_COMMAND

CREATE_DATABASE_COMMAND : CREATE DATABASE ID ';' {printf("In Yacc: %s\n", $3);test($3);}
DROP_DATABASE_COMMAND   : DROP DATABASE ID ';'
SAVE_COMMAND            : SAVE ';'
COMMIT_COMMAND          : COMMIT ';'
LOAD_DATABASE_COMMAND   : LOAD DATABASE ID ';'

CREATE_TABLE_COMMAND    : CREATE TABLE ID '(' FIELD_DEF_LIST ')' ';'
DROP_TABLE_COMMAND      : DROP TABLE ID ';'
INSERT_INTO_COMMAND     : INSERT INTO ID INSERT_INTO_COMMAND2
INSERT_INTO_COMMAND2    : '(' FIELD_LIST ')' VALUES '(' LITERAL_LIST ')' 
';'
                          | VALUES '(' LITERAL_LIST ')' ';'
DELETE_FROM_COMMAND     : DELETE FROM ID DELETE_FROM_COMMAND2
DELETE_FROM_COMMAND2    : WHERE CONDITION ';' | ';'  
                          
UPDATE_COMMAND          : UPDATE ID SET ID '=' LITERAL UPDATE_COMMAND2
UPDATE_COMMAND2         : ',' ID '=' LITERAL UPDATE_COMMAND2
                          | UPDATE_COMMAND3
UPDATE_COMMAND3         : WHERE CONDITION ';' | ';'

W_UPDATE_COMMAND        : WUPDATE ID SET W_UPDATE_COMMAND2
W_UPDATE_COMMAND2       : DATE_TIME ID '=' EXPRESSION W_UPDATE_COMMAND3
                          | ID '=' EXPRESSION W_UPDATE_COMMAND3
W_UPDATE_COMMAND3       : ',' W_UPDATE_COMMAND4 | W_UPDATE_COMMAND5
W_UPDATE_COMMAND4       : DATE_TIME ID '=' EXPRESSION W_UPDATE_COMMAND3
                          | ID '=' EXPRESSION W_UPDATE_COMMAND3
W_UPDATE_COMMAND5       : WHERE CONDITION ';' | ';' 

SELECT_COMMAND          : SELECT '*' FROM ID ';'

W_SELECT_COMMAND        : WSELECT W_SELECT_COMMAND2
W_SELECT_COMMAND2       : '*' FROM ID W_SELECT_COMMAND3
                          | '(' FIELD_LIST ')' FROM ID W_SELECT_COMMAND3
W_SELECT_COMMAND3       : WHERE CONDITION ';' | ';'

FIELD_DEF_LIST : FIELD_DEF FIELD_DEF_LIST2
FIELD_DEF_LIST2 : ',' FIELD_DEF FIELD_DEF_LIST2
                | /* EMPTY */
FIELD_DEF   : ID FIELD_TYPE
FIELD_LIST  : ID FIELD_LIST2
FIELD_LIST2 : ',' ID FIELD_LIST2 | /* EMPTY */
FIELD_TYPE                : INTEGER '(' INT ')' | INT
                          | NUMBER '(' INT ')'
                          | NUMBER '(' INT ',' INT ')'
                          | NUMBER
                          | CHARACTER '(' INT ')'

LITERAL_LIST            : LITERAL LITERAL_LIST2
LITERAL_LIST2           : ',' LITERAL LITERAL_LIST2 | /* EMPTY */
LITERAL                 : INT | DEC | STR | DATEL | DATESH
                          
DATE_TIME               : DATE ':' TIME
DATE                    : DATEL | DATESH
CONDITION               : ID COMP LITERAL | ID '=' ID
COMP                    : LT | GT | EQ | LTEQ | GTEQ
EXPRESSION              : /* EMPTY */
%%

yywrap()
{
   exit(0);
}


/*
It works if I uncomment this block of code
int main()
{
    while(1){
        printf("Enter the string");
        yyparse();
    }
}
*/
