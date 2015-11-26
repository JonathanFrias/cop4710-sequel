#include "common.h"

struct Table* retrieve(struct ParseTree* command) {

  // get table location
  char tablePath[1000];
  char fields[FIELD_LIMIT*FIELD_SIZE];
  int fieldCount = 0;
  struct Table* result = malloc(sizeof(struct Table));

  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, command->table);

  // open file and get record count
  // each line is a new record
  FILE* file = fopen(tablePath, "r");
  int recordCount = getRecordCount(file);
  struct Tuple* tuples = malloc(sizeof(struct Tuple)*recordCount);

  char buffer[FIELD_LIMIT*VALUE_LIMIT];
  fgets(buffer, sizeof(buffer), file);

  fieldCount = getFieldCount(buffer, sizeof(buffer));
  char* fieldName = strtok(buffer, "|");

  struct Field* recordFields = malloc(sizeof(struct Field)*fieldCount*recordCount);

  int i = 0;
  // This loops though the header lines of the table
  do {
    char type = fieldName[strlen(fieldName)-2];
    if(type == ']') {
      type = fieldName[strlen(fieldName)-3];
      fieldName[strlen(fieldName)-4] = '\0';
    } else {
      fieldName[strlen(fieldName)-3] = '\0';
    }

    char* name = malloc(NAME_LIMIT);
    snprintf(name, NAME_LIMIT, "%s", fieldName);
    (recordFields+i)->name = name;
    (recordFields+i)->fieldType = type;
    i++;
  } while((fieldName = strtok(NULL, "|")) != NULL);

  // Now loop through the actual records.
  int currentRecord = 1; // 1 is for header offset

  while(fgets(buffer, sizeof(buffer), file)) {
    int currentField = 0;
    char* value = strtok(buffer, "|");
    do {
      int fieldIndex = fieldCount*currentRecord+currentField;
      char* valueStorage = malloc(VALUE_LIMIT);
      snprintf(valueStorage, VALUE_LIMIT, "%s", buffer);

      (recordFields+fieldIndex)->name = (recordFields+currentField)->name;
      (recordFields+fieldIndex)->fieldType = (recordFields+currentField)->fieldType;
      (recordFields+fieldIndex)->value = valueStorage;
      currentField++;
    } while((value = strtok(NULL, "|")) != NULL);
    currentField++;
    currentRecord += 2;
  }
  fclose(file);
  return result;
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
  return lines;
}
