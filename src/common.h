#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../out/lexer.h"
#include "assert.h"

#define COMMAND_SIZE sizeof(struct Command)
#define WHERE_SIZE sizeof(struct Where)
#define FIELD_SIZE sizeof(struct Field)
#define TUPLE_SIZE sizeof(struct Tuple)
#define FIELD_LIMIT 100 // max num of columns
#define NAME_LIMIT 30 // Max length for user-provided names
#define VALUE_LIMIT 50 // Max length for user-provided values
#define HEADER_SIZE FIELD_LIMIT*(NAME_LIMIT+4) // +4 (1 delimeter, 3 type chars)
#define RECORD_SIZE FIELD_LIMIT*(VALUE_LIMIT+1) // +1 for delimeter
#define PATH_SIZE 1000
#define DATABASE_DIR "out/databases"

// Defines what database we're currently working on
char* currentDatabase;

typedef enum {
  INTEGER_t = 'I', // Integer [(max_left)]
  DATE_t = 'D', // Date mm/dd/yyyy
  TEXT_t = 'T' // Character (max_left)
} FieldType;

/*
struct FieldType {
  enum field_t ft;
  int max_left; // max allowed characters (left of decimal if number)
  int max_right; // max allowed characters to the right of decimal (only for number)
};
*/ 

struct Field {
  char* name;
  char* value;
  FieldType fieldType;
};

struct Tuple {
  struct Field* primaryKey;
  struct Field* fields;
  int updatedAt;
};

typedef enum whereType {
  LESS_THAN,
  LESS_THAN_OR_EQ,
  GREATER_THAN,
  GREATER_THAN_OR_EQ,
  EQUAL, 
  NOT_EQUAL,
} whereType;

struct Where {
  struct Field* field;
  void* target;
  enum whereType compareType;
};

/*
 * The most important struct
 * in this whole program.
 * Please note, by conventions
 * Field pointers should be NULL
 * terminated
 */
struct Command {
  enum {
    CREATE_DATABASE_t,
    CREATE_TABLE_t,
    DROP_DATABASE_t,
    DROP_TABLE_t,
    SAVE_t,
    LOAD_DATABASE_t,
    SELECT_t,
    wSELECT_t,
    INSERT_t,
    UPDATE_t,
    DELETE_t
  } commandType;
  char* table; // name of table
  struct Field* fields[50];
  struct Where* whereConstraints;
};

struct Table {
  struct Tuple* tuples;
  int count;
  char name[NAME_LIMIT];
};

struct Command* parseGrammer(char* sql);

// Store/Retrieve
bool store(struct Command* tuples);

struct Table* retrieve(struct Command* tree); // Tuple list returned must be NULL terminated.

void setDatabase(char*);
void createDatabase(struct Command* createCommand);
void createTable(struct Command* Command);
void setDatabase(char*);
void computePadding(char*, char*, int);
int getRecordCount(FILE* file);
int getFieldCount(char* buffer, int size);
int yyparse(void);
