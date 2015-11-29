#include "common.h"

struct Field* createField(char* name, char* value) {

  // MUST USE CALLOC, not MALLOC!
  struct Field* field = (struct Field*) calloc(2, sizeof(struct Field));

  if(name) {
    field->name = name;
  } else {
    field->name = "field_name";
  }

  if(value) {
    field->value = value;
  } else {
    field->value = "field_value";
  }

  return field;
}

struct Field* createFieldList(char* names, char* values, FieldType types[FIELD_SIZE][1], int count) {
  // Must use CALLOC instead of MALLOC
  // because field list should be NULL TERMINATED!
  struct Field* fieldList = calloc(count+1, FIELD_SIZE);
  for(int i = 0; i < count; i++) {
    (fieldList+i)->name = (names+(i*NAME_LIMIT));

    if(values) {
      (fieldList+i)->value = (values+(i*VALUE_LIMIT));
    }
    (fieldList+i)->fieldType = types[i][0];
  }

  return fieldList;
}

struct Where* createWhere(struct Field* field, whereCompare compareType) {
  struct Where* whereCondition = malloc(WHERE_SIZE);

  if(field) {
    whereCondition->field = field;
  } else {
    whereCondition->field = createField("WhereCondname", "WhereCondValue");
  }
  return whereCondition;
}

struct Command* createSelectCommand(char* table, struct Field* projection, struct Where* whereConstraints) {
  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = SELECT;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    cmd->fields = projection;
  } else {
    cmd->fields = createField("selectName", "selectVal");
  }

  return cmd;
}

struct Command* createWSelectCommand(char* table, struct Field* projection, struct Where* whereConstraints) {

  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = wSELECT;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    cmd->fields = projection;
  } else {
    cmd->fields = createField("selectName", "selectVal");
  }
  return cmd;
}

struct Command* createCreateDatabaseCommand(char* databaseName) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_DATABASE;
  cmd->table = databaseName;
  return cmd;
}

struct Command* createCreateTableCommand(char* table,
    struct Field* fields) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_TABLE;
  cmd->fields = fields;
  cmd->table = table;
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

  for(int i = 0; i < count; i++) {
    if(fields) {
      results[i].fields = fields;
    } else {
      results[i].fields = createField("createTuple", "createValue1");
    }
  }

  return results;
}

struct Command* createInsertCommand(char* table, struct Field* fields) {
  struct Command* command = malloc(sizeof(struct Command));
  command->commandType = INSERT;
  command->fields = fields;
  command->table = table;

  return command;
}

void destroyCommand(struct Command* cmd) {

  assert(cmd, "Cannot destroy invalid cmd");

  switch(cmd->commandType) {
    case CREATE_TABLE:
      if(cmd->fields) {
        free(cmd->fields);
      }
    case CREATE_DATABASE:
    default:
      free(cmd);
  }
  return;
}

void insertTuple(struct Command* cmd) {
  assert(cmd->commandType == INSERT, "Incompatible command type to function insert");
  assert(currentDatabase, "CurrentDatabase must be set!");
  assert(cmd->table, "Table must be provied!");
  char tablePath[PATH_SIZE];

  snprintf(tablePath, sizeof(tablePath), "%s/%s/%s", DATABASE_DIR, currentDatabase, cmd->table);

  FILE* file = fopen(tablePath, "a");

  int i = 0;
  while(cmd->fields[i].name != NULL) {
    fputs((char*) cmd->fields[i].value, file);
    if(cmd->fields[i+1].name != NULL) {
      fputs("|", file);
    }
    i++;
  }
  fputs("\n", file);

  fclose(file);
  return;
}

