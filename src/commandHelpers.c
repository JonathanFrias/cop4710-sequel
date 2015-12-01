#include "common.h"


//sets command struct for type and tablename
struct Command* createDropTableCommand(char* tableName){
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = DROP_TABLE_t;
  cmd->table = tableName;
  return cmd;
}

//sets command struct for database name to be removed from "out" (using command->table as database name)
struct Command* createDropDatabaseCommand(char* databaseName)
{
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = DROP_DATABASE_t;
  cmd->table = databaseName;
  return cmd;
}



struct Field* createField(char* name, char* value, whereType type) {

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

  field->fieldType = type;
  return field;
}

/*
struct Field** createFieldList(char* names, char* values, FieldType types[FIELD_SIZE][1], int count) {
  // Must use CALLOC instead of MALLOC
  // because field list should be NULL TERMINATED!
  
  for (int i=0; i<50; i++) 
    struct Field* fieldList[i] = calloc(count+1, FIELD_SIZE);
  for(int i = 0; i < count; i++) {
    fieldList[i]->name = names;

    if(values) {
      fieldList[i]->value = values;
    }
    fieldList[i]->fieldType = types[i][0];
  }

  return fieldList;
}
*/


struct Where* createWhere(struct Field* field, whereType compareType) {
  struct Where* whereCondition = calloc(2, sizeof(struct Where));

  if(field) {
    whereCondition->field = field;
  } else {
    whereCondition->field = createField("WhereCondname", "WhereCondValue", TEXT_t);
  }
  whereCondition->target = field->value;
  whereCondition->compareType = compareType;
  return whereCondition;
}

struct Command* createSelectCommand(char* table, struct Field* projection[50], struct Where* whereConstraints) {
  int i;

  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = SELECT_t;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    for(i=0; i<50; i++)
      cmd->fields[i] = projection[i];
  } else {
      for(i=0; i<50; i++)
        cmd->fields[i] = createField("selectName", "selectVal", TEXT_t);
  }
  cmd->whereConstraints = whereConstraints;

  return cmd;
}

struct Command* createWSelectCommand(char* table, struct Field* projection[50], struct Where* whereConstraints) {
  int i;
  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = wSELECT_t;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    for(i=0; i<50; i++)
      cmd->fields[i] = projection[i];
  } else {
    for(i=0; i<50; i++)
      cmd->fields[i] = createField("selectName", "selectVal", TEXT_t);
  }
  return cmd;
}

struct Command* createCreateDatabaseCommand(char* databaseName) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_DATABASE_t;
  cmd->table = databaseName;
  return cmd;
}

struct Command* createCreateTableCommand(char* table,
    struct Field* fields[50]) {
  int i;

  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_TABLE_t;
  for(i=0; i<50; i++)
    cmd->fields[i] = fields[i];
  cmd->table = table;
  return cmd;
}

struct Tuple* createTuple(struct Field* fields) {
  struct Tuple* result = malloc(sizeof(struct Tuple));

  if(fields) {
    result->fields = fields;
  } else {
    result->fields = createField("createTuple", "createValue1", TEXT_t);
  }

  return result;
}

struct Tuple* createTupleList(struct Field* fields, int count) {
  struct Tuple* results = calloc(count+1, sizeof(struct Tuple));

  for(int i = 0; i < count; i++) {
    if(fields) {
      results[i].fields = fields;
    } else {
      results[i].fields = createField("createTuple", "createValue1", TEXT_t);
    }
  }

  return results;
}

struct Command* createInsertCommand(char* table, struct Field* fields[50]) {
  int i;

  struct Command* command = malloc(sizeof(struct Command));
  command->commandType = INSERT_t;
  for (i=0; i<50; i++)
    command->fields[i] = fields[i];
  command->table = table;

  return command;
}

void destroyCommand(struct Command* cmd) {

  assert(cmd, "Cannot destroy invalid cmd");

  switch(cmd->commandType) {
    case CREATE_TABLE_t:
      if(cmd->fields) {
        free(cmd->fields);
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
  
  printf("about to open file\n");
  FILE* file = fopen(tablePath, "a");
  printf("opened file\n");

  int i = 0;
  while(cmd->fields[i] != NULL && cmd->fields[i][0].name != NULL) {
    fputs((char*) cmd->fields[i]->value, file);
    if(cmd->fields[i+1] != NULL) {
      fputs("|", file);
    }
    i++;
  }
  fputs("\n", file);

  fclose(file);
  return;
}
