#include "common.h"
#include "parseTreeHelpers.h"

// Test functions!
struct Table* createExampleTable(int count);
bool destroyExampleTable(struct Table*);
void testStore(void);
void testParseGrammer(void);
void printTable(struct Table* table);
void testCreateTable(void);
void testRetrieve(void);

// The following method stubs are not implemented!
// When they are implemented, you can remove them
// from here and link to the full function using our
// common header file!
struct ParseTree* parseGrammer(char* sql) {
  return NULL;
}

bool storeTuples(char* table, struct Tuple* tuples, int count) {
  return false;
}

bool storeTable(struct Table* table) {
  return false;
}

/*
 * This is just the main method!
 */
int main(void) {
  printf("===============Create Table:\n");
  testCreateTable();
  printf("===============Example Table:\n");

  // create a table with 10 tuples.
  struct Table* table = createExampleTable(10);
  printTable(table);

  printf("\n===============testStore\n");
  testStore();

  printf("\n===============testRetrieve\n");
  testRetrieve();

  printf("\n===============testParseGrammer\n");
  testParseGrammer();
  return 0;
}

void testRetrieve(void) {
  // This depends on testStore being run. because reasons!

  char names[FIELD_SIZE][NAME_LIMIT] = { "name4", "name2", "name3", "name1", };
  FieldType types[FIELD_SIZE][1] = { INTEGER, TEXT, DATE, INTEGER, };
  struct Field* projection = createFieldList(names, NULL, types, 4);
  struct ParseTree* selectCmd = createSelectParseTree("table", projection, NULL);

  struct Table* results = retrieve(selectCmd);

  assert(results->count == 1, "Did not retrieve correct number of records");
  assert(strcmp(results->name, "") == 0, "Table name was not set in the resultset");
}

void testCreateTable(void) {

  struct ParseTree* createDBCommand = createCreateDatabaseParseTree("foo");
  createDatabase(createDBCommand);
  assert(strcmp(currentDatabase, "foo") == 0, "currentDatabase should be set!");
  char tableFolderPath[1000];

  char names[FIELD_SIZE][NAME_LIMIT] = { "name1", "name2", "name3", "name4", };

  char values[FIELD_SIZE][VALUE_LIMIT] = { "1", "value2", "1/1/2015", "3", };

  FieldType types[FIELD_SIZE][1] = { INTEGER, TEXT, DATE, INTEGER, };
  struct Field* fields = createFieldList(names, values, types, 4);

  struct ParseTree* createTableCmd = createCreateTableParseTree("bar", fields);
  createTable(createTableCmd);
  sprintf(tableFolderPath, "%s/foo/bar", DATABASE_DIR);
  assert(access(tableFolderPath, F_OK) != -1, "Table file was not constructed!");

  char fileContents[RECORD_SIZE];
  FILE* file = fopen(tableFolderPath, "r");
  fgets(fileContents, RECORD_SIZE, file);

  char* header = "name1[I]|name2[T]|name3[D]|name4[I]\n";
  assert(strcmp(fileContents, header) == 0, "Table was not written correctly!");

  // cleanup garbage
  fclose(file);
  destroyParseTree(createDBCommand);
  destroyParseTree(createTableCmd);
}

void testParseGrammer(void) {
  struct ParseTree* parseTree = parseGrammer("SELECT id from table1");

  assert(parseTree != 0, "Should not contain a null pointer!");
  assert(parseTree->commandType == SELECT, "Command type should equal select!");
  assert(strcmp("table1", parseTree->table) == 0, "The table was not set propertly!");
  assert(parseTree->whereConstraints != NULL, "WhereConstraints should have been specified!");
  assert(parseTree->fields != NULL, "Field should not be null!");
  assert(parseTree->fields+1 == NULL, "Field list should be NULL terminated!");
}

void testStore(void) {

  // setup
  struct ParseTree* createDatabaseCommand = createCreateDatabaseParseTree("test_store");
  createDatabase(createDatabaseCommand);

  char names[FIELD_SIZE][NAME_LIMIT] = { "name1", "name2", "name3", "name4", };

  char values[FIELD_SIZE][VALUE_LIMIT] = { "1", "value2", "1/1/2015", "3", };

  FieldType types[FIELD_SIZE][1] = { INTEGER, TEXT, DATE, INTEGER, };

  struct Field* fields = createFieldList(names, values, types, 4);
  struct ParseTree* createTableCmd = createCreateTableParseTree("table",
      fields);
  createTable(createTableCmd);

  // test
  struct ParseTree* insertCmd = createInsertParseTree("table", fields);
  insertTuple(insertCmd);

  // teardown
  destroyParseTree(createDatabaseCommand);
  destroyParseTree(createTableCmd);
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
