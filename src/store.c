#include "common.h"
#include <sys/stat.h>

/*
 * This function creates a folder.
 * The folder name is the name of the database
 */
void createDatabase(char* database) {
  mkdir(DATABASE_DIR, 0700);

  char folderPath[NAME_LIMIT];
  getcwd(folderPath, sizeof(folderPath));

  sprintf(folderPath, "%s/%s", DATABASE_DIR, database);
  mkdir(folderPath, 0700);

  sprintf(currentDatabase, "%s", database);
}

void createTable(struct ParseTree* parseTree) {

  // validations!
  assert(parseTree->commandType == CREATE_TABLE,
    "Expectd parseTree commandType to be CREATE_TABLE");
  assert(parseTree->fields, "Fields must be provided!");
  assert(parseTree->table, "Table name must be provided");
  assert(currentDatabase, "Please select a database!");

  // Create a table file in the default database directory
  char tablePath[NAME_LIMIT];
  sprintf(tablePath, "%s/%s", DATABASE_DIR, parseTree->table);
  FILE* tableFile = fopen(tablePath, "w");

  int i = 0;

  struct Field* fields[FIELD_LIMIT];
  char firstLine[FIELD_LIMIT*NAME_LIMIT+FIELD_LIMIT-1];

  while(parseTree->fields+i != NULL) {
    char name[NAME_LIMIT];
    fields[i] = parseTree->fields+i;
    sprintf(firstLine, "%s|%s", firstLine, parseTree->fields[i].name);
    i += 1;
  }
  fputs(firstLine, tableFile);
}
