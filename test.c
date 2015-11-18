#include "common.h"
#include "assert.h"

void exampleTable(void);
void testStore(void);
void testRetrieve(void);
void testParseGrammer(void);

struct ParseTree* parseGrammer(char* sql) {
  return NULL;
}

void store(struct Tuple* tuples, int count) {
  return;
}

struct Tuple* retrieve(struct ParseTree tree) {
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
}

void testRetrieve(void) {
}

int main(void) {
  printf("===============Examlpe Table:\n");
  exampleTable();
  printf("\n===============testStore\n");
  testStore();
  printf("\n===============testRetrieve\n");
  testRetrieve();
  printf("\n===============testParseGrammer\n");
  testParseGrammer();
  return 0;
}

/*
 *  This example represents the a sample of how
 *  the contents of a table should be represented.
 *  You'll notice here that it is simply a array
 *  of Tuple objects. (Hopefully that makes sense!)
 */
void exampleTable(void) {
  int count = 10;


  // Allocate space in memory for a known amount of tuples.
  struct Tuple* tuples = (struct Tuple*) malloc(sizeof(struct Tuple)*count);

  for(int i = 0; i < count; i++) {
    // Create a Field* that represents the primary key
    struct Field* primaryKeyField = (struct Field*) malloc(sizeof(struct Field));

    tuples[i].fields = primaryKeyField;
    tuples[i].primaryKey = primaryKeyField;

    char* name = malloc(sizeof(char)*12);
    char* value = malloc(sizeof(char)*12);

    // initialize name and value variables to include
    // our iterator i.
    sprintf(name, "name%d", i);
    sprintf(value, "value%d", i);

    tuples[i].primaryKey->name = name;
    tuples[i].primaryKey->value = value;
  }

  for(int i = 0; i < count; i++) {
    printf("%s\n", tuples[i].primaryKey->name);
    printf("%s\n", tuples[i].primaryKey->value);
    free(tuples[i].primaryKey->name);
    free(tuples[i].primaryKey->value);
    free(tuples[i].primaryKey);
  }
  free(tuples);
}
