#include "common.h"

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
		usleep(10000);
	}

	printf("%45s\n", "Welcome to wSQLx!");


	char * sqlString = "wSQLx: ";
	char * input = {0};
	do
	{
		printf("%sPlese input command.", sqlString);
		scanf("%s", input);


	}while (input != "exit");    //this infinitely loops
}

