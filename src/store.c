#include "common.h"
#include <sys/stat.h>

/*
 * This function creates a folder.
 * The folder name is the name of the database
 */
void createDatabase(struct ParseTree* createCommand) {

  assert(createCommand->commandType == CREATE_DATABASE,
      "Incompatible parseTree commandType to function createDatabase");
  mkdir(DATABASE_DIR, 0700);

  char folderPath[NAME_LIMIT];
  getcwd(folderPath, sizeof(folderPath));

  sprintf(folderPath, "%s/%s", DATABASE_DIR, createCommand->table);
  mkdir(folderPath, 0700);


  setDatabase(createCommand->table);
}

/*
 * Sets the global currentDatabase variable
 */
void setDatabase(char* database) {
  if(currentDatabase == NULL) {
    currentDatabase = calloc(1, NAME_LIMIT);
  }
  snprintf(currentDatabase, NAME_LIMIT,
     "%s", database);
}

/**
 * Creates the table structure on disk.
 * Assumes that field list is NULL terminated.
 */
void createTable(struct ParseTree* parseTree) {

  // validations!
  assert(parseTree->commandType == CREATE_TABLE,
    "Expectd parseTree commandType to be CREATE_TABLE");
  assert(parseTree->fields, "Fields must be provided!");
  assert(parseTree->table, "Table name must be provided");
  assert(currentDatabase, "Please select a database!");

  // Create a table file in the default database directory
  char tablePath[1000];
  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, parseTree->table);
  FILE* tableFile = fopen(tablePath, "w");

  int i = 0;

  struct Field* fields[FIELD_LIMIT];
  char headerLine[HEADER_SIZE];
  char tmpLine[HEADER_SIZE];
  struct Field* providedFields = parseTree->fields;

  while((*(parseTree->fields+i)).name != NULL) {
    char name[NAME_LIMIT] = "";
    char type = parseTree->fields[i].fieldType;
    snprintf(name, sizeof(name), parseTree->fields[i].name);
    snprintf(tmpLine, sizeof(headerLine), headerLine);
    snprintf(headerLine, sizeof(headerLine), "%s|%s[%c]", tmpLine, name, type);
    i++;
  }
  char line[RECORD_SIZE];
  computePadding(headerLine+1, line, RECORD_SIZE); // +1 to ignore leading '|'

  fputs(line, tableFile);
  fputs("\n", tableFile);
  fclose(tableFile);
}

/**
 *
 * Computes the padding for a given input, forcing the resulting
 * string to be of the given size.
 * This function pads the begining with a spaces, and the end with
 * a new line character
 * The result is stored in the result pointer.
 */
void computePadding(char* input, char* result, int size) {
  int length = strlen(input) + 1;
  int padding = size - length;

  assert(padding >= 0, "Padding cannot be negative!");
  int i = 0;
  for(; i < padding-1; i++) {
    result[i] = ' ';
  }

  int j = 0;
  for(; i < size-1; i++, j++) {
    result[i] = input[j];
  }
  result[size-2] = '\n';
  result[size-1] = '\0';

  assert(result[size-2] == '\n', "Newline not set!");
  // The +1 is to count the '\0'
  assert(strlen(result)+1 == size, "Record size is not correct!");
}
