#include "common.h"

struct Table* retrieve(struct ParseTree* command) {

  char tablePath[1000];
  char fields[FIELD_LIMIT*FIELD_SIZE];
  int fieldCount = 0;

  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, command->table);
  FILE* file = fopen(tablePath, "r");

  int records = getRecordCount(file);
  struct Tuple* tuples = malloc(sizeof(struct Tuple)*records);

  char buffer[FIELD_LIMIT*VALUE_LIMIT];
  fgets(buffer, sizeof(buffer), file);

  char* fieldName = strtok(buffer, "|");

  for(int i = 0; i < sizeof(buffer); i++) {
    if(buffer[i] == '|') {
      fieldCount++;
    }
    if(buffer[i] == '\0') {
      break;
    }
  }
  fieldCount++;

  struct Table* result = malloc(sizeof(struct Table));
  struct Field* header = malloc(sizeof(struct Field)*fieldCount);

  int i = 0;
  while((fieldName = strtok(NULL, "|")) != NULL) {
    char type = fieldName[strlen(fieldName)-2];
    if(type == ']') {
      type = fieldName[strlen(fieldName)-1];
      fieldName[strlen(fieldName)-1] = '\0';
    } else {
      fieldName[strlen(fieldName)-1] = '\0';
    }

    (header+i)->name = fieldName;
    (header+i)->fieldType = type;
  }

  fclose(file);
  return result;
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
