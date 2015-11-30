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

enum field_t {
  INTEGER_t = 'I', // Integer [(max_left)]
  NUMBER_t = 'N', // Number [(max_left[,max_right])]
  DATE_t = 'D', // Date mm/dd/yyyy
  TEXT_t = 'T' // Character (max_left)
};

struct FieldType {
  enum field_t ft;
  int max_left; // max allowed characters (left of decimal if number)
  int max_right; // max allowed characters to the right of decimal (only for number)
}; 

struct Field {
  char name[30];
  char value[120];
  struct FieldType* field_type;
};

struct Tuple {
  struct Field* primaryKey;
  struct Field* fields;
  int updatedAt;
};

enum whereCompare {
  LESS_THAN,
  LESS_THAN_EQUALS,
  GREATER_THAN,
  GREATER_THAN_EQUALS,
  EQUALS, 
  NOT_EQUALS,
};

struct Where {
  char field[30];
  char target[140];
  enum whereCompare compareType;
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
  char table[23]; // name of table
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

void createDatabase(struct Command* createCommand);
void createTable(struct Command* Command);
void setDatabase(char*);
void computePadding(char*, char*, int);
int getRecordCount(FILE* file);
int getFieldCount(char* buffer, int size);
int yyparse(void);
