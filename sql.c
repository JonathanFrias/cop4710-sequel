#include "sql.tab.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int i = 0;
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
		usleep(2000);
	}

	printf("Welcome to wSQLx! Enter a command or\n");
	printf("Enter 'exit' to quit wSQLx or 'help' for more information\n\n");

	yyscan_t scanner;
	printf("scanner created\n");
	YY_BUFFER_STATE buf;
	printf("buf created\n");
	yylex_init(&scanner);
	printf("scanner initialized\n");
	
	char * user_input = {0};
	printf("user_input initialized\n");
	//do
	//{
		printf("wSQLx: ");
		scanf("%[^\n]%*c", user_input);
		
		buf = yy_scan_string(user_input, scanner);
		yyparse(user_input);
		


	//}while (strcmp(user_input, "exit") != 0);    //this infinitely loops
	
	yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);
	
	return 0;
	
}
