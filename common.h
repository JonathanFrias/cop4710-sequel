#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PARSETREE_SIZE sizeof(struct ParseTree)
#define FIELD_SIZE sizeof(struct Field)

struct Field {
  char* name;
  void* value;
};

struct Tuple {
  struct Field* primaryKey;
  struct Field* fields;
  int updatedAt;
};

struct {
  struct Field field;
  void* target;
  enum {
    LESS_THAN,
    GREATHER_THAN,
    // ...
  } compareType;
} Where;

// parse 

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
  char* table;
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

struct Table* retrieve(struct ParseTree* tree);
struct Table* createTable(int count);
void SqlRun();
