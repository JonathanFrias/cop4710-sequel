#include "common.h"
#include "commandHelpers.h"
#include "retrieve.h"
#include <sys/stat.h>

/*
 * This function creates a folder.
 * The folder name is the name of the database
 */
void createDatabase(struct Command* createCommand) {

  assert(createCommand->commandType == CREATE_DATABASE_t,
      "Incompatible Command commandType to function createDatabase");
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
void createTable(struct Command* command) {

  // validations!
  assert(command->commandType == CREATE_TABLE_t,
    "Expectd command commandType to be CREATE_TABLE");
  assert(command->fields, "Fields must be provided!");
  assert(command->table, "Table name must be provided");
  assert(currentDatabase, "Please select a database!");

  // Create a table file in the default database directory
  char tablePath[PATH_SIZE];
  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, command->table);
  FILE* tableFile = fopen(tablePath, "w");

  writeHeaderLine(tableFile, command->fields);

  fclose(tableFile);
}

void writeHeaderLine(FILE* tableFile, struct Field* fields) {
  int i = 0;

  char headerLine[HEADER_SIZE];
  char tmpLine[HEADER_SIZE];
  while((*(fields+i)).name != NULL) {
    char name[NAME_LIMIT] = "";
    char type = fields[i].fieldType;
    snprintf(name, sizeof(name), "%s", fields[i].name);
    snprintf(tmpLine, sizeof(headerLine), "%s", headerLine);
    snprintf(headerLine, sizeof(headerLine), "%s|%s[%c]", tmpLine, name, type);
    i++;
  }
  fputs(headerLine+1, tableFile); // +1 to ignore leading '|'
  fputs("\n", tableFile); // newline after header line
}

/*
 * Updates a table. Can insert and remove records
 *
 * Step 1. Read the whole table into memory.
 * Step 2. Write the column information back to the file.
 * Step 3. Update the records in memory.
 * Step 4. Write the entire table back into the file.
 * Step 5. Cleanup
 */
void update(struct Command* command) {
  // Step 1.
  char tableFile[PATH_SIZE];
  struct Command* selectAll = createSelectCommand(command->table, NULL, NULL);
  struct Table* entireTable = retrieve(selectAll, NULL);
  snprintf(tableFile, sizeof(tableFile), "%s/%s/%s", DATABASE_DIR,
      currentDatabase, command->table);

  // Step 2.
  FILE* f = fopen(tableFile, "w");
  writeHeaderLine(f, entireTable->tuples[0].fields);
  fclose(f);
  // Step 3.
  struct Tuple* filtered = calloc(entireTable->count, sizeof(struct Tuple));
  applyWhere(entireTable, command, filtered, entireTable->fieldCount);
  // Step 4.

  for(int i = 0; i < entireTable->count; i++) {
    for(int j = 0; j < entireTable->fieldCount; j++) {
      for(int k = 0; command->fields[k].value != NULL; k++) {
        if(strcmp(entireTable->tuples[i].fields[j].name, command->fields[k].name) == 0) {
          snprintf(entireTable->tuples[i].fields[j].value,
              VALUE_LIMIT, "%s", (char*)command->fields[k].value);
        }
      }
    }
    struct Command* tmpCommand = createInsertCommand(command->table, entireTable->tuples[i].fields);
    insertTuple(tmpCommand);
    free(tmpCommand);
  }

  if(command->commandType != DELETE_t) {
    for(int i = 0; filtered[i].fields != NULL; i++) {
      insertTuple(createInsertCommand(command->table, filtered[i].fields));
    }
  }

  // Step 5.
  destroyCommand(selectAll);
  free(filtered);
}


void  delete(struct Command* command) {
  assert(command->commandType == DELETE_t, "Incompatible command type!");
  update(command);
}
