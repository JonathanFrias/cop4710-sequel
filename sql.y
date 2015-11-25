%{ 
#define YYSTYPE char*
#include <stdio.h>
%}

%start START
%token ID 
%token CREATE DROP LOAD SAVE DATABASE TABLE INSERT INTO FROM 
%token WHERE SET DELETE UPDATE SELECT WSELECT VALUES
%token DEC INT STR DATETYPE DATE NUMBER CHARACTER INTEGER
%token LT GT LTEQ GTEQ EQ EQEQ NOTEQ


%%
START          : COMMAND_LIST  
                     
COMMAND_LIST   : COMMAND COMMAND_LIST2
 
COMMAND_LIST2  : COMMAND COMMAND_LIST2 
	       | /* EMPTY */

COMMAND        : SYSTEM_COMMAND 
	       | DDL_COMMAND 
	       | DML_COMMAND

SYSTEM_COMMAND : CREATE_DATABASE_COMMAND
               | DROP_DATABASE_COMMAND
               | SAVE_COMMAND
               | LOAD_DATABASE_COMMAND

               
DDL_COMMAND    : CREATE_TABLE_COMMAND
               | DROP_TABLE_COMMAND

DDL_COMMAND    : CREATE_TABLE_COMMAND
               | DROP_TABLE_COMMAND

DML_COMMAND    : INSERT_INTO_COMMAND
               | DELETE_FROM_COMMAND
               | UPDATE_COMMAND
               | SELECT_COMMAND
               | W_SELECT_COMMAND

CREATE_DATABASE_COMMAND : CREATE DATABASE ID ';'

DROP_DATABASE_COMMAND   : DROP DATABASE ID ';'

SAVE_COMMAND            : SAVE ';'

LOAD_DATABASE_COMMAND   : LOAD DATABASE ID ';'

CREATE_TABLE_COMMAND    : CREATE TABLE ID '(' FIELD_DEF_LIST ')' ';'

DROP_TABLE_COMMAND      : DROP TABLE ID ';'

INSERT_INTO_COMMAND     : INSERT INTO ID INSERT_INTO_COMMAND2

INSERT_INTO_COMMAND2    : '(' FIELD_LIST ')' VALUES '(' LITERAL_LIST ')' ';'
                        | VALUES '(' LITERAL_LIST ')' ';'

DELETE_FROM_COMMAND     : DELETE FROM ID DELETE_FROM_COMMAND2

DELETE_FROM_COMMAND2    : WHERE CONDITION ';' | ';'

UPDATE_COMMAND          : UPDATE ID SET ID '=' LITERAL UPDATE_COMMAND2

UPDATE_COMMAND2         : ',' ID '=' LITERAL UPDATE_COMMAND2      
                        | UPDATE_COMMAND3

UPDATE_COMMAND3         : WHERE CONDITION ';' 
			| ';'

SELECT_COMMAND          : SELECT '*' FROM ID ';'

W_SELECT_COMMAND        : WSELECT W_SELECT_COMMAND2

W_SELECT_COMMAND2       : '*' FROM ID W_SELECT_COMMAND3
                        | '(' FIELD_LIST ')' FROM ID W_SELECT_COMMAND3

W_SELECT_COMMAND3       : WHERE CONDITION ';' 
		        | ';'

FIELD_DEF_LIST 		: FIELD_DEF FIELD_DEF_LIST2 

FIELD_DEF_LIST2 	: ',' FIELD_DEF FIELD_DEF_LIST2 
	        	| /* EMPTY */ 

FIELD_DEF 		: FIELD_TYPE ID 

FIELD_LIST 		: ID FIELD_LIST2

FIELD_LIST2 		: ',' ID FIELD_LIST2 
	    		| /* EMPTY */ 

FIELD_TYPE              : INTEGER '(' INT ')' 
			| INT
                        | NUMBER '(' INT ')' 
                        | NUMBER '(' INT ',' INT ')'
                        | NUMBER
                        | CHARACTER '(' INT ')'
                        | DATE

LITERAL_LIST            : LITERAL LITERAL_LIST2

LITERAL_LIST2           : ',' LITERAL LITERAL_LIST2 
		        | /* EMPTY */

LITERAL                 : INT 
		        | DEC 
			| STR 
			| DATETYPE

CONDITION               : ID COMP LITERAL 

COMP                    : LT 
			| GT 
			| EQEQ 
			| LTEQ 
			| GTEQ
			| NOTEQ 
%%


#include "lex.yy.c"
main()
{
   yyparse();
}
yyerror()
{
   printf("REJECT\n");
}
yywrap()
{
   printf("ACCEPT\n");

}
