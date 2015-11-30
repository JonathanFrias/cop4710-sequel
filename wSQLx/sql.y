%{ 
#include <stdio.h>
#include <stdlib.h>
#include "commandHelpers.h"
int intval;
int i = 0;
char names[1000];
char values[1000];
char type[1000];

struct Command* c;
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
%token CREATE DROP LOAD SAVE DATABASE TABLE INSERT INTO FROM 
%token WHERE SET DELETE UPDATE SELECT WSELECT VALUES
%token DATETYPE DATE NUMBER CHARACTER INTEGER
%token LT GT LTEQ GTEQ EQ EQEQ NOTEQ 
%token RP LP COMMA SEMIC AST



%%
START          : COMMAND_LIST 
                     
COMMAND_LIST   : COMMAND {printf("Query Accepted\n"); /* create new current command */} COMMAND_LIST2 
 
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

DML_COMMAND    : INSERT_INTO_COMMAND
               | DELETE_FROM_COMMAND
               | UPDATE_COMMAND
               | SELECT_COMMAND
               | W_SELECT_COMMAND

CREATE_DATABASE_COMMAND : CREATE DATABASE ID SEMIC {struct Command* CDBC = createCreateDatabaseCommand($3);createDatabase(CDBC);} 
 
DROP_DATABASE_COMMAND   : DROP DATABASE ID SEMIC

SAVE_COMMAND            : SAVE SEMIC

LOAD_DATABASE_COMMAND   : LOAD DATABASE ID SEMIC {setDatabase($3);}

CREATE_TABLE_COMMAND    : CREATE TABLE ID LP FIELD_DEF_LIST RP SEMIC  {struct Field* FL = createFieldList(names, values, type, i); struct Command* CTC = createCreateTableCommand($3, FL); createTable(CTC);}

DROP_TABLE_COMMAND      : DROP TABLE ID SEMIC

INSERT_INTO_COMMAND     : INSERT INTO ID INSERT_INTO_COMMAND2

INSERT_INTO_COMMAND2    : LP FIELD_LIST RP VALUES LP LITERAL_LIST RP SEMIC
                        | VALUES LP LITERAL_LIST RP SEMIC

DELETE_FROM_COMMAND     : DELETE FROM ID DELETE_FROM_COMMAND2

DELETE_FROM_COMMAND2    : WHERE CONDITION SEMIC | SEMIC

UPDATE_COMMAND          : UPDATE ID SET ID EQ LITERAL UPDATE_COMMAND2

UPDATE_COMMAND2         : COMMA ID EQ LITERAL UPDATE_COMMAND2      
                        | UPDATE_COMMAND3

UPDATE_COMMAND3         : WHERE CONDITION SEMIC | SEMIC

SELECT_COMMAND          : SELECT AST FROM ID SEMIC

W_SELECT_COMMAND        : WSELECT W_SELECT_COMMAND2

W_SELECT_COMMAND2       : AST FROM ID W_SELECT_COMMAND3
                        | LP FIELD_LIST RP FROM ID W_SELECT_COMMAND3

W_SELECT_COMMAND3       : WHERE CONDITION SEMIC 
		        | SEMIC

FIELD_DEF_LIST 		: FIELD_DEF FIELD_DEF_LIST2 

FIELD_DEF_LIST2 	: COMMA FIELD_DEF FIELD_DEF_LIST2 
	        	| /* EMPTY */ 

FIELD_DEF 		: ID FIELD_TYPE {names[i] = "test"; i++;}

FIELD_LIST 		: ID FIELD_LIST2 

FIELD_LIST2 		: COMMA ID FIELD_LIST2 {names[i] = $2; i++;}
	    		| /* EMPTY */ 

FIELD_TYPE              : INTEGER LP INT RP {type[i] = 'I';}
			| INTEGER {type[i] = 'I';}
                        | NUMBER LP INT RP  {type[i] = 'I';}
                        | NUMBER LP INT COMMA INT RP {type[i] = 'I';}
                        | NUMBER {type[i] = 'I';}
                        | CHARACTER LP INT RP {type[i] = 'T';}
			| DATE {type[i] = 'D';}

LITERAL_LIST            : LITERAL LITERAL_LIST2

LITERAL_LIST2           : COMMA LITERAL LITERAL_LIST2 
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

yyerror() {
   printf("REJECT\n");
   exit(0);
}

yywrap() {
  printf("wrap!\n");
}
