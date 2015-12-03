#include "common.h"
#include "../out/sql.tab.h"



struct Command* cmd;
struct Tuple* this_tuple;
struct Where* this_where;
struct Field* this_field;
struct Field* this_field_array[50];



int main(void)     
{
	int i;

	cmd = malloc(sizeof(struct Command));
	this_tuple = malloc(sizeof(struct Tuple));
	this_where = malloc(sizeof(struct Where));
	this_field = malloc(sizeof(struct Field));
	for (i=0; i<50; i++) {
		this_field_array[i] = malloc(sizeof(struct Field));
	}
    
	srand(1/2); 
	char * sqlLine =        
		("                                                                      \n"
		 "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		 "::******************************************************************::\n"
		 "::**                                                              **::\n"
		 "::**                   SSSSSS       QQQQQQQ     LL                **::\n"
		 "::**                  SS     SS    QQ     QQ    LL                **::\n"
		 "::**                  SS          QQ       QQ   LL                **::\n"
		 "::**  ww       ww      SSSSSS     QQ       QQ   LL        xx  xx  **::\n"
		 "::**   w       w            SS    QQ     Q QQ   LL          xx    **::\n"
		 "::**    w  w  w      SS     SS     QQ     QQ    LL          xx    **::\n"
		 "::**     ww ww         SSSSSS       QQQQQQQ Q   LLLLLLL   xx  xx  **::\n"
		 "::**                                                              **::\n"
		 "::******************************************************************::\n"
		 "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		 "                                                                      \n");

	for (i = 0; i < strlen(sqlLine); i++)   
	{
		printf("%c", sqlLine[i]); 
		// usleep(2000);
	}

	printf("Welcome to wSQLx! Enter a command or\n");
	printf("Enter 'exit' to quit wSQLx or 'help' for more information\n\n");
	
	char* current_database = "NULL";
	extern int yyparse(void);
	char user_input[300];
	char temp[300];
	 
	do 
	{
		printf("wSQLx: ");
		scanf("%[^\n]%*c", user_input);
		
		
		user_input[strlen(user_input)+1] = '\0';
		strcpy(temp, user_input);
		YY_BUFFER_STATE string_buffer = yy_scan_string(temp);
		yy_switch_to_buffer(string_buffer);
		yyparse();
		yy_delete_buffer(string_buffer);
		


	} while (strcmp(user_input, "exit") != 0);    //this infinitely loops
	
	
	return 0;
	
}
