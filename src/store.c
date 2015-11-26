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
    snprintf(name, sizeof(name), "%s", parseTree->fields[i].name);
    snprintf(tmpLine, sizeof(headerLine), "%s", headerLine);
    snprintf(headerLine, sizeof(headerLine), "%s|%s[%c]", tmpLine, name, type);
    i++;
  }
  fputs(headerLine+1, tableFile); // +1 to ignore leading '|'
  fputs("\n", tableFile); // newline after header line
  fclose(tableFile);
}
