#include "common.h"

//something something dark side. 
//getting used to the gitshell window...



/*
creates table from info passed through by inputArg->tokenizer->parser
plan is...
1. first line will contain the attributes which will be at the top of each  column
2. following lines will contain the infromation relevant to the columns. i.e. the values contained within
*/

//test table size is currently 10 from call in test.c
char * names[10] = { "primus", "secundus", "tersous", "quatrus", "cincus", "sesus", "severus", "octus", "nino", "tenith" };
int vals[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


struct Table* createTable(int count)   
{
	int i;
	struct Tuple* tuples = (struct Tuple*)malloc(sizeof(struct Tuple) * count);

	for (int i = 0; i < count; i++)
	{
		struct Field* keys = (struct Field*)malloc(sizeof(struct Field));
		tuples[i].fields = keys;
		tuples[i].primaryKey = keys;
		//printf("%s%d\n", keys[i].name, keys[i].value);

		//getchar();

		tuples[i].primaryKey->value = vals[i];
		tuples[i].primaryKey->name = names[i];
//		printf("%10s", tuples[i].primaryKey->name);
//		printf("\n%10d", tuples[i].primaryKey->value);
	}
	struct Table* table = (struct Table*)malloc(sizeof(struct Table));
	table->tuples = tuples;
	table->count = count;
	table->name = "tables.test";


   getchar();    //for testing purposes, holds up cmd after
   return(table);
}
