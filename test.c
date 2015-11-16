#include "common.h"
#include "assert.h"

void example1(void);
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
  example1();
  testStore();
  testRetrieve();
  testParseGrammer();
  return 0;
}

void example1(void) {
  struct ParseTree* p = (struct ParseTree*) malloc(PARSETREE_SIZE);
  p->commandType = SELECT;
  p->table = "table1";
  p->fields = malloc(FIELD_SIZE * 10);

  printf("%s\n", p->table);

  // cleanup
  free(p->fields);
  free(p);
}