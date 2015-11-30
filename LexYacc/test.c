#include <stdio.h>
#include "lexheader.h"
#include "sql.tab.h"

extern int intval;

main()
{

int yyparse();
/*
char * line = "INSERT 54\n";
YY_BUFFER_STATE bp = yy_scan_string( line ); 
yy_switch_to_buffer(bp); 
yyparse(); 
yy_delete_buffer(bp);     
printf ("hello %d",intval);

*/
printf("Enter the query:");

//while(1)
printf ("%d\n",yyparse());

}

void test(char *input)
{
   //char sample[100];
   //sample = input;
   printf("In sql.c: %s\n", input);
}
