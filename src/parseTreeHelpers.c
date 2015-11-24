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
    (fieldList+i)->value = (values+(i*VALUE_LIMIT));
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

struct ParseTree* createSelectParseTree(char* table, struct Field* projection, struct Where* whereConstraints) {
  struct ParseTree* tree = malloc(PARSETREE_SIZE);

  tree->commandType = SELECT;

  if(table) {
    tree->table = table;
  } else {
    tree->table = "default_table";
  }

  if(projection) {
    tree->fields = projection;
  } else {
    tree->fields = createField("selectName", "selectVal");
  }

  return tree;
}

struct ParseTree* createWSelectParseTree(char* table, struct Field* projection, struct Where* whereConstraints) {

  struct ParseTree* tree = malloc(PARSETREE_SIZE);

  tree->commandType = wSELECT;

  if(table) {
    tree->table = table;
  } else {
    tree->table = "default_table";
  }

  if(projection) {
    tree->fields = projection;
  } else {
    tree->fields = createField("selectName", "selectVal");
  }
  return tree;
}

struct ParseTree* createCreateDatabaseParseTree(char* databaseName) {
  struct ParseTree* tree = malloc(PARSETREE_SIZE);
  tree->commandType = CREATE_DATABASE;
  tree->table = databaseName;
  return tree;
}

struct ParseTree* createCreateTableParseTree(char* table,
    struct Field* fields) {
  struct ParseTree* tree = malloc(PARSETREE_SIZE);
  tree->commandType = CREATE_TABLE;
  tree->fields = fields;
  tree->table = table;
  return tree;
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

struct ParseTree* createInsertParseTree(char* table, struct Field* fields) {
  struct ParseTree* command = malloc(sizeof(struct ParseTree));
  command->commandType = INSERT;
  command->fields = fields;
  command->table = table;

  return command;
}

void destroyParseTree(struct ParseTree* tree) {

  assert(tree, "Cannot destroy invalid tree");

  switch(tree->commandType) {
    case CREATE_TABLE:
      if(tree->fields) {
        free(tree->fields);
      }
    case CREATE_DATABASE:
    default:
      free(tree);
  }
  return;
}

void insertTuple(struct ParseTree* cmd) {
  assert(cmd->commandType == INSERT, "Incompatible command type to function insert");
  assert(currentDatabase, "CurrentDatabase must be set!");
  assert(cmd->table, "Table must be provied!");
  char tablePath[1000];

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

