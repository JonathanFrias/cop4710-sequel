%{ 
#include "/home/nickjones67/Documents/cop4710-sequel/src/common.h"
#include "/home/nickjones67/Documents/cop4710-sequel/src/commandHelpers.h"

int i;
int intval;
int field_count = 0;
int literal_count = 0;
char dbBuf[30];
char tblBuf[30];
char fieldBuf[50][30];
struct Command* cmd;
struct Tuple* this_tuple;
struct Where* this_where;
struct Field* this_field;
struct Table* this_table;
FieldType this_field_type;
struct Field* this_field_array[50];
char currentName[100];
char currentValue[100];
int currentNameIndex = 0;
int currentValueIndex = 0;
enum whereType this_compare_type;
char this_literal[50][140];


%}

%start START
%token ID 
%token CREATE DROP LOAD SAVE DATABASE TABLE INSERT INTO FROM 
%token WHERE SET DELETE UPDATE SELECT WSELECT VALUES
%token DEC INT STR DATETYPE DATE NUMBER CHARACTER INTEGER
%token LT GT LTEQ GTEQ EQ EQEQ NOTEQ 
%token RP LP COMMA SEMIC AST



%%
START          : COMMAND_LIST 
                     
COMMAND_LIST   : COMMAND { printf("Query Accepted\n"); } COMMAND_LIST2 
 
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

CREATE_DATABASE_COMMAND : CREATE DATABASE ID { strcpy(dbBuf, yytext); } SEMIC { cmd = createCreateDatabaseCommand(dbBuf); createDatabase(cmd); printf("\nDatabase %s created.\n", cmd->table); destroyCommand(cmd); }

DROP_DATABASE_COMMAND   : DROP DATABASE ID { strcpy(dbBuf, yytext); } SEMIC { cmd=createDropDatabaseCommand(dbBuf); dropDatabase(cmd); destroyCommand(cmd); }

SAVE_COMMAND            : SAVE SEMIC { printf("\nSQL you later!!\n\n"); exit(0); }

LOAD_DATABASE_COMMAND   : LOAD DATABASE ID { strcpy(dbBuf, yytext); } SEMIC { setDatabase(dbBuf); printf("\nCurrent database set to %s\n", dbBuf); }

CREATE_TABLE_COMMAND    : CREATE TABLE ID { strcpy(tblBuf, yytext); } LP FIELD_DEF_LIST RP SEMIC { cmd=createCreateTableCommand(tblBuf, this_field_array); createTable(cmd); printf("Table %s created in %s\n", tblBuf, dbBuf); }



DROP_TABLE_COMMAND      : DROP TABLE ID { strcpy(tblBuf, yytext); } SEMIC { cmd=createDropTableCommand(tblBuf); dropTable(cmd); destroyCommand(cmd); }

INSERT_INTO_COMMAND     : INSERT INTO ID { strcpy(tblBuf, yytext); } INSERT_INTO_COMMAND2 

INSERT_INTO_COMMAND2    : LP FIELD_LIST RP VALUES LP LITERAL_LIST RP SEMIC { insertFoo(); }
                        | VALUES LP LITERAL_LIST RP SEMIC { cmd = createInsertCommand(tblBuf, this_field_array); for(i=0; i<literal_count; i++){this_field_array[i]=NULL;} literal_count=0; destroyCommand(cmd); }

DELETE_FROM_COMMAND     : DELETE FROM ID { strcpy(tblBuf, yytext); } DELETE_FROM_COMMAND2

DELETE_FROM_COMMAND2    : WHERE CONDITION SEMIC { /* cmd=createDeleteFromCommand(), pass command, delete command */ } 
			| SEMIC { /* cmd=createDeleteFromCommand(), pass command, delete command */ } 

UPDATE_COMMAND          : UPDATE ID { strcpy(tblBuf, yytext); } SET ID { strcpy(fieldBuf[field_count], yytext);  } EQ LITERAL { strcpy(this_field_array[i]->name, fieldBuf[field_count]); strcpy(this_field_array[i]->value, this_literal[literal_count]); field_count++; } UPDATE_COMMAND2 { for(i=0; i<field_count; i++){this_field_array[i]=NULL;} field_count=0; }

UPDATE_COMMAND2         : COMMA ID { strcpy(fieldBuf[field_count], yytext); } EQ LITERAL { strcpy(this_field_array[i]->name, fieldBuf[field_count]); strcpy(this_field_array[i]->value, this_literal[literal_count]); field_count++; } UPDATE_COMMAND2     
                        | UPDATE_COMMAND3

UPDATE_COMMAND3         : WHERE CONDITION SEMIC { /* cmd=createUpdateCommand(), pass command, destroy command */ }
			| SEMIC { this_field->value="ALL"; this_where->field=this_field; /* cmd=createUpdateCommand(), pass command, destroy command */ }

SELECT_COMMAND          : SELECT AST FROM ID { strcpy(tblBuf, yytext); } SEMIC { cmd=createSelectCommand(tblBuf, this_field_array, this_where); this_table=retrieve(cmd); printTable(this_table); }

W_SELECT_COMMAND        : WSELECT W_SELECT_COMMAND2

W_SELECT_COMMAND2       : AST { strcpy(this_field_array[0]->name, "ALL");  } FROM ID { strcpy(tblBuf, yytext); } W_SELECT_COMMAND3
                        | LP FIELD_LIST RP FROM ID { strcpy(tblBuf, yytext); } W_SELECT_COMMAND3

W_SELECT_COMMAND3       : WHERE CONDITION SEMIC { cmd=createWSelectCommand(tblBuf, this_field_array, this_where); destroyCommand(cmd); } 
		        | SEMIC { this_where->compareType=EQUAL; cmd=createWSelectCommand(tblBuf, this_field_array, this_where); /* pass command, destroy command */ }

FIELD_DEF_LIST 		: FIELD_DEF { this_field_array[field_count]=this_field; field_count++; } FIELD_DEF_LIST2 { this_field_array[field_count]=NULL; field_count=0; }


FIELD_DEF_LIST2 	: COMMA FIELD_DEF { this_field_array[field_count]=this_field; field_count++; } FIELD_DEF_LIST2 
	        	| /* EMPTY */ 

FIELD_DEF 		: ID { strcpy(fieldBuf[field_count], yytext); printf("%s\n", yytext); } FIELD_TYPE { this_field->name=fieldBuf[field_count]; this_field->fieldType=this_field_type; }

FIELD_LIST 		: ID { strcpy(fieldBuf[field_count], yytext); this_field_array[field_count]->name = fieldBuf[field_count]; field_count++; } FIELD_LIST2 { this_field_array[field_count] = NULL; field_count = 0; }

FIELD_LIST2 		: COMMA ID { strcpy(fieldBuf[field_count], yytext); this_field_array[field_count]->name = fieldBuf[field_count]; field_count++; } FIELD_LIST2 
	    		| /* EMPTY */ 

FIELD_TYPE              : INTEGER { this_field_type=INTEGER_t; } 
                        | CHARACTER { this_field_type=TEXT_t; }
			| DATE { this_field_type=DATE_t; }


LITERAL_LIST            : LITERAL { this_field_array[literal_count]->value=this_literal[literal_count]; literal_count++; } LITERAL_LIST2 {literal_count = 0; } 

LITERAL_LIST2           : COMMA LITERAL { this_field_array[literal_count]->value=this_literal[literal_count]; literal_count++; } LITERAL_LIST2 
		        | /* EMPTY */

LITERAL                 : INT { strcpy(this_literal[literal_count], yytext); } 
			| STR { strcpy(this_literal[literal_count], yytext); }
			| DATETYPE { strcpy(this_literal[literal_count], yytext); }

CONDITION               : ID { strcpy(fieldBuf[field_count], yytext); } COMP LITERAL {this_where=createWhere(createField(fieldBuf[field_count], "NULL", TEXT_t), this_compare_type); this_where->target=yytext; }  

COMP                    : LT { this_compare_type=LESS_THAN; } 
			| GT { this_compare_type=GREATER_THAN; } 
			| EQEQ { this_compare_type=EQUAL; }
			| LTEQ { this_compare_type=LESS_THAN_OR_EQ; }
			| GTEQ { this_compare_type=GREATER_THAN_OR_EQ; }
			| NOTEQ { this_compare_type=NOT_EQUAL; }
%%

yyerror() {
   printf("INVALID QUERY\n");
   return 0;
}

yywrap() {
  printf("\n");
}


insertFoo() {
  cmd = createInsertCommand(tblBuf, this_field_array); 
  insertTuple(cmd); 
  for(i=0; i<field_count; i++){
    this_field_array[i]=NULL;} literal_count=0; field_count=0; destroyCommand(cmd);
} 
