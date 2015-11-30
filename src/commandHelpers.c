#include "common.h"

struct Field* createField(char name[30], char value[120]) {
  // MUST USE CALLOC, not MALLOC!
  struct Field* field = (struct Field*) calloc(2, sizeof(struct Field));

  if(name) {
    strcpy(field->name, name);
  } else {
    strcpy(field->name, "field_name");
  }

  if(value) {
    strcpy(field->value, value);
  } else {
    strcpy(field->value, "field_value");
  }

  return field;
}

/*
struct Field* createFieldList(char* names, char* values, struct FieldType types[FIELD_SIZE][1], int count) {
  // Must use CALLOC instead of MALLOC
  // because field list should be NULL TERMINATED! 
  int i;
  struct Field* fieldList = calloc(count+1, FIELD_SIZE);
  for(i = 0; i < count; i++) {
    (fieldList+i)->name = (names+(i*NAME_LIMIT));

    if(values) {
      (fieldList+i)->value = (values+(i*VALUE_LIMIT));
    }
    (fieldList+i)->fieldType = types[i][0];
  }

  return fieldList;
}
*/

struct Where* createWhere(char field[30], enum whereCompare compareType) {
  struct Where* whereCondition = malloc(WHERE_SIZE);

  if(field) {
    strcpy(whereCondition->field, field);
  } else {
    strcpy(whereCondition->field, "WhereCondname");
  }
  return whereCondition;
}

// projection is array of field names. Need to create a helper to retrieve the field type
struct Command* createSelectCommand(char* table) {
  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = SELECT_t;

  if(table) {
    strcpy(cmd->table, table);
  } else {
    strcpy(cmd->table, "default_table");
  }

/*
  if(projection) {
    cmd->fields = projection;
  } else {
    cmd->fields = createField("selectName", "selectVal");
  }
*/

  return cmd;
}

struct Command* createWSelectCommand(char* table, struct Field* projection[50], struct Where* whereConstraints) {

  struct Command* cmd = malloc(COMMAND_SIZE);
  int i;
  cmd->commandType = wSELECT_t;

  if(table) {
    strcpy(cmd->table, table);
  } else {
    strcpy(cmd->table, "default_table");
  }

  if(projection) {
    for(i=0; i<50; i++)
      cmd->fields[i] = projection[i];
  } else {
    for(i=0; i<50; i++)
      cmd->fields[i] = createField("selectName", "selectVal");
  }
  return cmd;
}

struct Command* createCreateDatabaseCommand(char* databaseName) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_DATABASE_t;
  strcpy(cmd->table, databaseName);
  return cmd;
}

struct Command* createCreateTableCommand(char* table,
    struct Field* fields[50]) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  int i;

  cmd->commandType = CREATE_TABLE_t;
  for(i=0; i<50; i++)
    cmd->fields[i] = fields[i];
  strcpy(cmd->table, table);
  return cmd;
}

struct Tuple* createTuple(struct Field* fields) {
  struct Tuple* result = malloc(sizeof(struct Tuple));

  if(fields) {
    result->fields = fields;
  } else {
    result->fields = createField("createTuple", "createValue1");
  }

  return result;
}

struct Tuple* createTupleList(struct Field* fields, int count) {
  struct Tuple* results = calloc(count+1, sizeof(struct Tuple));
  
  int i;
  for(i = 0; i < count; i++) {
    if(fields) {
      results[i].fields = fields;
    } else {
      results[i].fields = createField("createTuple", "createValue1");
    }
  }

  return results;
}

struct Command* createInsertCommand(char* table, struct Field* fields[50]) {
  struct Command* command = malloc(sizeof(struct Command));
  int i;

  command->commandType = INSERT_t;
  for(i=0; i<50; i++)
    command->fields[i] = fields[i];
  strcpy(command->table, table);

  return command;
}

void destroyCommand(struct Command* cmd) {
  int i;
  assert(cmd, "Cannot destroy invalid cmd");

  switch(cmd->commandType) {
    case CREATE_TABLE_t:
      if(cmd->fields) {
        for(i=0; i<50; i++)
          free(cmd->fields[i]);
      }
    case CREATE_DATABASE_t:
    default:
      free(cmd);
  }
  return;
}

void insertTuple(struct Command* cmd) {
  assert(cmd->commandType == INSERT_t, "Incompatible command type to function insert");
  assert(currentDatabase, "CurrentDatabase must be set!");
  assert(cmd->table, "Table must be provied!");
  char tablePath[PATH_SIZE];

  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, cmd->table);

  FILE* file = fopen(tablePath, "a");

  int i = 0;
  while(cmd->fields[i]->name != NULL) {
    fputs((char*) cmd->fields[i]->value, file);
    if(cmd->fields[i+1]->name != NULL) {
      fputs("|", file);
    }
    i++;
  }
  fputs("\n", file);

  fclose(file);
  return;
}

struct FieldType* createFieldType(enum field_t this_ft, int ml, int mr)
{
  struct FieldType* fldtyp = malloc(sizeof(struct FieldType));
  fldtyp->ft = this_ft;
  fldtyp->max_left = ml;
  fldtyp->max_right = mr;

  return fldtyp;
}



