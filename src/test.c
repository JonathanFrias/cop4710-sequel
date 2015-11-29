#include "common.h"
#include "commandHelpers.h"

// Test functions!
void testStore(void);
void testParseGrammer(void);
void testCreateTable(void);
void testRetrieve(void);

// The following method stubs are not implemented!
// When they are implemented, you can remove them
// from here and link to the full function using our
// common header file!
struct Command* parseGrammer(char* sql) {
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
  struct Command* selectCmd = createSelectCommand("table", projection, NULL);

  struct Table* results = retrieve(selectCmd);

  assert(results->count == 2, "Did not retrieve correct number of records");
  assert(strcmp(results->name, "table") == 0, "Table name was not set in the resultset");

  assert(strcmp(results->tuples[0].fields[0].name, "name1") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[0].fields[1].name, "name2") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[0].fields[2].name, "name3") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[0].fields[3].name, "name4") == 0 , "Problem with resultset");
  assert(results->tuples[0].fields[4].name == 0 , "Problem with resultset"); // make sure null terminated

  assert(strcmp((char*) results->tuples[0].fields[0].value, "1") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[0].fields[1].value, "value2") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[0].fields[2].value, "1/1/2015") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[0].fields[3].value, "3") == 0 , "Problem with resultset");
  assert(results->tuples[0].fields[4].name == 0 , "Problem with resultset");


  assert(strcmp(results->tuples[1].fields[0].name, "name1") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[1].fields[1].name, "name2") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[1].fields[2].name, "name3") == 0 , "Problem with resultset");
  assert(strcmp(results->tuples[1].fields[3].name, "name4") == 0 , "Problem with resultset");
  assert(results->tuples[1].fields[4].name == 0 , "Problem with resultset"); // make sure null terminated

  assert(strcmp((char*) results->tuples[1].fields[0].value, "1") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[1].fields[1].value, "value2") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[1].fields[2].value, "1/1/2015") == 0 , "Problem with resultset");
  assert(strcmp((char*) results->tuples[1].fields[3].value, "3") == 0 , "Problem with resultset");
  assert(results->tuples[1].fields[4].name == 0 , "Problem with resultset");

}

void testCreateTable(void) {

  struct Command* createDBCommand = createCreateDatabaseCommand("foo");
  createDatabase(createDBCommand);
  assert(strcmp(currentDatabase, "foo") == 0, "currentDatabase should be set!");
  char tableFolderPath[PATH_SIZE];

  char names[FIELD_SIZE][NAME_LIMIT] = { "name1", "name2", "name3", "name4", };

  char values[FIELD_SIZE][VALUE_LIMIT] = { "1", "value2", "1/1/2015", "3", };

  FieldType types[FIELD_SIZE][1] = { INTEGER, TEXT, DATE, INTEGER, };
  struct Field* fields = createFieldList(names, values, types, 4);

  struct Command* createTableCmd = createCreateTableCommand("bar", fields);
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
  destroyCommand(createDBCommand);
  destroyCommand(createTableCmd);
}

void testParseGrammer(void) {
  struct Command* command = parseGrammer("SELECT id from table1");

  assert(command != 0, "Should not contain a null pointer!");
  assert(command->commandType == SELECT, "command type should equal select!");
  assert(strcmp("table1", command->table) == 0, "The table was not set propertly!");
  assert(command->whereConstraints != NULL, "WhereConstraints should have been specified!");
  assert(command->fields != NULL, "Field should not be null!");
  assert(command->fields+1 == NULL, "Field list should be NULL terminated!");
}

void testStore(void) {

  // setup
  struct Command* createDatabaseCommand = createCreateDatabaseCommand("test_store");
  createDatabase(createDatabaseCommand);

  char names[FIELD_SIZE][NAME_LIMIT] = { "name1", "name2", "name3", "name4", };

  char values[FIELD_SIZE][VALUE_LIMIT] = { "1", "value2", "1/1/2015", "3", };

  FieldType types[FIELD_SIZE][1] = { INTEGER, TEXT, DATE, INTEGER, };

  struct Field* fields = createFieldList(names, values, types, 4);
  struct Command* createTableCmd = createCreateTableCommand("table",
      fields);
  createTable(createTableCmd);


  // test
  struct Command* insertCmd = createInsertCommand("table", fields);
  insertTuple(insertCmd);
  insertTuple(insertCmd);

  // teardown
  destroyCommand(createDatabaseCommand);
  destroyCommand(createTableCmd);
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
  snprintf(table->name, sizeof(table->name), "exampleTable");
  return table;
}
