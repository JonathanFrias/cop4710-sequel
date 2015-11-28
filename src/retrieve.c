#include "common.h"

struct Table* retrieve(struct Command* command) {

  // get table location
  char tablePath[PATH_SIZE];
  int fieldCount = 0;

  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, command->table);

  // open file and get record count
  // each line is a new record
  FILE* file = fopen(tablePath, "r");
  int recordCount = getRecordCount(file);

  char buffer[FIELD_LIMIT*VALUE_LIMIT];
  fgets(buffer, sizeof(buffer), file);

  fieldCount = getFieldCount(buffer, sizeof(buffer));
  // discard newline
  buffer[strlen(buffer)-1] = '\0';
  char* fieldName = strtok(buffer, "|");

  struct Field* recordFields = malloc(sizeof(struct Field)*fieldCount*recordCount*2+recordCount);

  struct Tuple* tuples = malloc(sizeof(struct Tuple)*recordCount);

  int i = 0;
  // This loops though the header lines of the table
  do {
    char type = fieldName[strlen(fieldName)-2];
    fieldName[strlen(fieldName)-3] = '\0';

    char* name = malloc(NAME_LIMIT);
    snprintf(name, NAME_LIMIT, "%s", fieldName);
    (recordFields+i)->name = name;
    (recordFields+i)->fieldType = type;
    i++;
  } while((fieldName = strtok(NULL, "|")) != NULL);

  // Now loop through the actual records.
  int currentRecord = 1; // 1 is for header offset
  int tupleCount = 0;
  while(fgets(buffer, sizeof(buffer), file)) {
    // discard newline
    buffer[strlen(buffer)-1] = '\0';

    int currentField = 0;
    char* value = strtok(buffer, "|");
    do {
      int fieldIndex = fieldCount*currentRecord+currentField;
      char* valueStorage = malloc(VALUE_LIMIT);
      snprintf(valueStorage, VALUE_LIMIT, "%s", value);

      (recordFields+fieldIndex)->name = (recordFields+currentField)->name;
      (recordFields+fieldIndex)->fieldType = (recordFields+currentField)->fieldType;
      (recordFields+fieldIndex)->value = valueStorage;
      currentField++;
    } while((value = strtok(NULL, "|")) != NULL);
    currentField++;
    tuples[tupleCount].fields = &(recordFields[fieldCount*currentRecord]);
    currentRecord+=2; // to force NULL delimited records!
    tupleCount++;
  }
  struct Table* table = malloc(sizeof(struct Table));
  table->tuples = tuples;
  table->count = recordCount;
  snprintf(table->name, sizeof(table->name), "%s", command->table);
  fclose(file);
  return table;
}

int getFieldCount(char* buffer, int size) {
  int fieldCount = 0;
  for(int i = 0; i < size; i++) {
    if(buffer[i] == '|') {
      fieldCount++;
    }
    if(buffer[i] == '\0') {
      break;
    }
  }
  return ++fieldCount;
}

int getRecordCount(FILE* file) {
  int ch;
  int lines = 0;

  while (EOF != (ch=fgetc(file))) {
    if (ch=='\n') {
      ++lines;
    }
  }
  rewind(file);
  return lines-1;
}
