#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "assert.h"

#define PARSETREE_SIZE sizeof(struct ParseTree)
#define WHERE_SIZE sizeof(struct Where)
#define FIELD_SIZE sizeof(struct Field)
#define TUPLE_SIZE sizeof(struct Tuple)
#define FIELD_LIMIT 100 // max num of columns
#define NAME_LIMIT 30 // Max length for user-provided names
#define VALUE_LIMIT 50 // Max length for user-provided values

#define DATABASE_DIR "out/databases"

// Defines what database we're currently working on
char* currentDatabase;

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

struct Where {
  struct Field* field;
  void* target;
  whereCompare compareType;
};

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

<<<<<<< HEAD
struct Table* retrieve(struct ParseTree* tree);
struct Table* createTable(int count);
void SqlRun();
=======
struct Table* retrieve(struct ParseTree* tree); // Tuple list returned must be NULL terminated.
void createDatabase(struct ParseTree* createCommand);
void createTable(struct ParseTree* parseTree);
void setDatabase(char*);
>>>>>>> refs/remotes/JonathanFrias/store
