#include "common.h"
#include "assert.h"

struct Table* createExampleTable(int count);
bool destroyExampleTable(struct Table*);
void testStore(void);
void testRetrieve(void);
void testParseGrammer(void);
void printTable(struct Table* table);

// The following method stubs are not implemented!
// When they are implemented, you can remove them
// from here and link to the full function using our
// common header file!
struct ParseTree* parseGrammer(char* sql) {
  return NULL;
}

bool storeTuples(struct Tuple* tuples, int count) {
  return false;
}

bool storeTable(struct Table* table) {
  return false;
}

struct Table* retrieve(struct ParseTree* tree) {
  return NULL;
}

void testParseGrammer(void) {
  struct ParseTree* parseTree = parseGrammer("SELECT id from table1");

  assert(parseTree != 0, "Should not contain a null pointer!");
  assert(parseTree->commandType == SELECT, "Command type should equal select!");
  assert(strcmp("table1", parseTree->table) == 0, "The table was not set propertly!");
  assert(parseTree->whereConstraints != NULL, "WhereConstraints should have been specified!");
  assert(parseTree->updateFields == NULL, "UPDATE fields were not specified!");
  assert(parseTree->insertFields == NULL, "INSERT fields were not specified!");
  assert(parseTree->fields != NULL, "Field should not be null!");
}

void testStore(void) {
  struct Table* table = createExampleTable(10);

  bool res = storeTuples(table->tuples, 10);
  assert(res, "storeTuples function did not report success!");

  bool res2 = storeTable(table);
  assert(res, "storeTable function did not report success!");
}

void testRetrieve(void) {
  // setup
  struct Table* table = createExampleTable(10);
  bool res = storeTuples(table->tuples, 10);

  //test
  char sql[100];
  sprintf(sql, "select * from %s;\n", table->name);

  struct ParseTree* parseTree = parseGrammer(sql);

  struct Table* results = retrieve(parseTree);
  assert(results != 0, "retrieve operation returned a null pointer!");
  assert(results->count == table->count, "All records not stored correctly!");

  //teardown
  destroyExampleTable(table);
}

/*
 * This is just the main method!
 */
int main(void) {
  printf("===============Example Table:\n");

  // create a table with 10 tuples.
  struct Table* table = createTable(10);

  printf("%10s%10s\n", "EMP", "EMP#");    //should modify the structure to include an attribute list
  for (int i = 0; i < 10; i++)
	  printf("%10s%10d\n", table->tuples[i].primaryKey->name, table->tuples[i].primaryKey->value);
  printf("\n");


  SqlRun();
  //struct Table* table = createExampleTable(10);
  //printTable(table);
  //destroyExampleTable(table);

  getchar();
  printf("\n===============testStore\n");
  testStore();

  getchar();
  printf("\n===============testRetrieve\n");
  testRetrieve();

  getchar();
  printf("\n===============testParseGrammer\n");
  testParseGrammer();

  getchar();
  return 0;
}

/*
 *  This example represents the a sample of how
 *  the contents of a table should be represented.
 *  You'll notice here that it is simply a array
 *  of Tuple objects. (Hopefully that makes sense!)
 */
struct Table* createExampleTable(int count) {
  // Allocate space in memory for a known amount of tuples.
  struct Tuple* tuples = (struct Tuple*) malloc(sizeof(struct Tuple)*count);

  for(int i = 0; i < count; i++) {
    // Create a Field* that represents the primary key
    struct Field* primaryKeyField = (struct Field*) malloc(sizeof(struct Field));

    tuples[i].fields = primaryKeyField;
    tuples[i].primaryKey = primaryKeyField;

    char* name = malloc(sizeof(char)*12);
    char* value = malloc(sizeof(char)*12);

    // initialize name and value variables
    sprintf(name, "name%d", i);
    sprintf(value, "value%d", i);

    tuples[i].primaryKey->name = name;
    tuples[i].primaryKey->value = value;
  }

  // Allocate space in memory for a table construct
  struct Table* table = (struct Table*) malloc(sizeof(struct Table));
  table->tuples = tuples;
  table->count = count;
  table->name = "exampleTable";
  return table;
}

void printTable(struct Table* table) {
  for(int i = 0; i < table->count; i++) {
    printf("%s\n", table->tuples[i].primaryKey->name);
    printf("%s\n", table->tuples[i].primaryKey->value);
  }
  return;
}

/*
 * Cleanup allocated memory from a table.
 */
bool destroyExampleTable(struct Table* table) {
  for(int i = 0; i < table->count; i++) {
    free(table->tuples[i].primaryKey->name);
    free(table->tuples[i].primaryKey->value);
    free(table->tuples[i].primaryKey);
  }
  free(table->tuples);
  free(table);
  return true;
}
