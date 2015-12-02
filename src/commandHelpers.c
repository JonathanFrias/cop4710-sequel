#include "common.h"


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




struct Field* addField(char* name, char* value, FieldType type, 
  			struct Field* old_fields) {
   
  //struct Field* field = (struct Field*) calloc(2, sizeof(struct Field));
        int i;

        for(i=0; (old_fields+i)->name != NULL; i++)
                ;

        struct Field* new_fields = (struct Field*)calloc(i+2, FIELD_SIZE);

        for(i=0; (old_fields+i)->name != NULL; i++) {
                (new_fields+i)->name = (old_fields+i)->name;
                (new_fields+i)->value = (old_fields+i)->value;
                (new_fields+i)->fieldType = (old_fields+i)->fieldType;
        }

        (new_fields+i)->name = name;
        (new_fields+i)->value = value;
        (new_fields+i)->fieldType = type;

        /*
        (new_fields+i+1)->name = NULL;
        (new_fields+i+1)->value = NULL;
        (new_fields+i+1)->fieldType = 'D';
        */

        /*
        if (name) {
                field->name = name;
        } else {
                field->name = "field_name";
        }

        if (value) {
                field->value = value;
        } else {
                field->value = "field_value";
        }
        field->fieldType = type;
	*/

        /*
        // free memory
        for(i=0; (old_fields+i)->name != NULL; i++) {
                free((old_fields+i)->name);
                free((old_fields+i)->value);
        } 
        free(old_fields);
        */

        return new_fields;

} // end addField()

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

struct Where* createWhere(struct Field* field, whereType compareType) {
  struct Where* whereCondition = calloc(2, sizeof(struct Where));

  if(field) {
    whereCondition->field = field;
  } else {
    whereCondition->field = addField("WhereCondname", "WhereCondValue", TEXT_t, field);
  }
  whereCondition->target = field->value;
  whereCondition->compareType = compareType;
  return whereCondition;
}

struct Command* createSelectCommand(char* table, struct Field* projection, struct Where* whereConstraints) {
  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = SELECT_t;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    cmd->fields = projection;
  } else {
    cmd->fields = addField("selectName", "selectVal", TEXT_t, projection);
  }
  cmd->whereConstraints = whereConstraints;

  return cmd;
}

struct Command* createUpdateCommand(char* table,
    struct Field* fieldsToUpdate,
    struct Where* whereConstraints) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = UPDATE_t;

  assert(table, "table is required");

  cmd->table = table;
  cmd->fields = fieldsToUpdate;
  cmd->whereConstraints = whereConstraints;
  return cmd;
}

struct Command* createWSelectCommand(char* table, struct Field* projection, struct Where* whereConstraints) {

  struct Command* cmd = malloc(COMMAND_SIZE);

  cmd->commandType = wSELECT_t;

  if(table) {
    cmd->table = table;
  } else {
    cmd->table = "default_table";
  }

  if(projection) {
    cmd->fields = projection;
  } else {
    cmd->fields = addField("selectName", "selectVal", TEXT_t, projection);
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
    struct Field* fields) {
  struct Command* cmd = malloc(COMMAND_SIZE);
  cmd->commandType = CREATE_TABLE_t;
  cmd->fields = fields;
  cmd->table = table;
  return cmd;
}

struct Tuple* createTuple(struct Field* fields) {
  struct Tuple* result = malloc(sizeof(struct Tuple));

  if(fields) {
    result->fields = fields;
  } else {
    result->fields = addField("createTuple", "createValue1", TEXT_t, fields);
  }

  return result;
}

struct Tuple* createTupleList(struct Field* fields, int count) {
  struct Tuple* results = calloc(count+1, sizeof(struct Tuple));

  for(int i = 0; i < count; i++) {
    if(fields) {
      results[i].fields = fields;
    } else {
      results[i].fields = addField("createTuple", "createValue1", TEXT_t, fields);
    }
  }

  return results;
}

struct Command* createInsertCommand(char* table, struct Field* fields) {
  struct Command* command = malloc(sizeof(struct Command));
  command->commandType = INSERT_t;
  command->fields = fields;
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

