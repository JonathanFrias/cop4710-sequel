#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define WHERE_SIZE sizeof(struct Where)
#define PARSETREE_SIZE sizeof(struct ParseTree)
#define FIELD_SIZE sizeof(struct Field)
#define FIELD_LIMIT 100 // max num of columns
#define NAME_LIMIT 100 // Max length for user-provided names

#define DATABASE_DIR "out/databases"

// Defines what database we're currently working on
static char currentDatabase[NAME_LIMIT];

struct Field {
  char* name;
  void* value;
};

struct Tuple {
  struct Field* primaryKey;
  struct Field* fields;
  int updatedAt;
};

typedef enum {
  LESS_THAN,
  GREATHER_THAN,
  // ...
} whereCompare;

struct {
  struct Field field;
  void* target;
  whereCompare compareType;
} Where;

/*
 * The most important struct
 * in this whole program.
 * Please note, by conventions
 * Field pointers should be NULL
 * terminated
 */
struct ParseTree {
  enum {
    CREATE_DATABASE,
    CREATE_TABLE,
    DROP_DATABASE,
    DROP_TABLE,
    COMMIT,
    SAVE,
    LOAD_DATABASE,
    SELECT,
    wSELECT,
    INSERT,
    UPDATE,
    wUPDATE,
    DELETE
  } commandType;
  char* table; // name of table
  struct Field* fields;
  struct Where* whereConstraints;
  struct Field* updateFields;
  struct Field* insertFields;
};

struct Table {
  struct Tuple* tuples;
  int count;
  char* name;
};

struct ParseTree* parseGrammer(char* sql);

// Store/Retrieve

bool storeTuple(struct Tuple* tuples, int count);
bool storeTable(struct Table* table);

struct Table* retrieve(struct ParseTree* tree); // Tuple list returned must be NULL terminated.
void createDatabase(char* database);
void createTable(struct ParseTree* parseTree);
