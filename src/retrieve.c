#include "common.h"
#include "retrieve.h"

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

  struct Tuple* tuples = calloc(recordCount+1, sizeof(struct Tuple));

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
  struct Table* table = calloc(1, sizeof(struct Table));
  table->tuples = tuples;
  table->count = recordCount;
  snprintf(table->name, sizeof(table->name), "%s", command->table);
  fclose(file);
  applyWhere(table, command, fieldCount);
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

int tupleComparator(const void* first, const void* second) {
  struct Tuple* t1 = (struct Tuple*) first;
  struct Tuple* t2 = (struct Tuple*) second;

  if(t1->fields == 0 || t2->fields == 0) {
    return 1;
  } else {
    return -1;
  }
}

bool whereCompare(struct Where* compare) {

  char* fieldValue = (char*) compare->target;
  char* compareValue = (char*) compare->field->value;

  if(compare->field->fieldType == INTEGER) {
    if(compare->compareType == EQUAL) {
      return intEq(fieldValue, compareValue);
    }

    if(compare->compareType == LESS_THAN) {
      return intLt(fieldValue, compareValue);
    }

    if(compare->compareType == LESS_THAN_OR_EQ) {
      return intLt(fieldValue, compareValue) || intEq(fieldValue, compareValue);
    }

    if(compare->compareType == GREATHER_THAN) {
      return intGt(fieldValue, compareValue);
    }

    if(compare->compareType == GREATHER_THAN_OR_EQ) {
      return intGt(fieldValue, compareValue) || intEq(fieldValue, compareValue);
    }

    if(compare->compareType == NOT_EQUAL) {
      return !intEq(fieldValue, compareValue);
    }
  }

  if(compare->field->fieldType == TEXT) {
    if(compare->compareType == EQUAL) {
      return textEq(fieldValue, compareValue);
    }

    if(compare->compareType == LESS_THAN) {
      return textLt(fieldValue, compareValue);
    }

    if(compare->compareType == LESS_THAN_OR_EQ) {
      return textLt(fieldValue, compareValue) || textEq(fieldValue, compareValue);
    }

    if(compare->compareType == GREATHER_THAN) {
      return textGt(fieldValue, compareValue);
    }

    if(compare->compareType == GREATHER_THAN_OR_EQ) {
      return textGt(fieldValue, compareValue) || textEq(fieldValue, compareValue);
    }

    if(compare->compareType == NOT_EQUAL) {
      return !textEq(fieldValue, compareValue);
    }
  }
  return false;
}


bool textLt(char* a, char* b) {
  return strcmp(a, b) < 0;
}

bool textGt(char* a, char* b) {
  return strcmp(a, b) > 0;
}

bool textEq(char* a, char* b) {
  return strcmp(a, b) == 0;
}

bool intEq(char* a, char* b) {
  return atoi(a) == atoi(b);
}

bool intLt(char* a, char* b) {
  return atoi(a) < atoi(b);
}

bool intGt(char* a, char* b) {
  return atoi(a) > atoi(b);
}

void applyWhere(struct Table* table, struct Command* cmd, int fieldCount) {
  if(!cmd->whereConstraints) {
    return;
  }
  int size = table->count;
  // compare every field of every record, against every whereConstraint
  for(int i = 0; i < table->count; i++) {
    for(int j = 0; j < fieldCount; j++) {
      struct Where* where = NULL;
      int k = 0;
      while((where = &cmd->whereConstraints[k])->field != NULL) {

        char* name = table->tuples[i].fields[j].name;
        char* value = table->tuples[i].fields[j].value;
        if(strcmp(name, where->field->name) == 0) {
          if(strcmp(value, where->field->value) != 0) {
            // exclude record and skip the rest of fields
            // TODO: Fix the huge memory leak here!
            j = fieldCount;
            table->count -= 1;
            table->tuples[i].fields[j].name = 0;
            table->tuples[i].fields[j].value = 0;
            table->tuples[i].fields = 0;
            break;
          }
        }
        k++;
      }
    }
  }
  qsort(table->tuples, size, sizeof(struct Tuple), tupleComparator);
}

