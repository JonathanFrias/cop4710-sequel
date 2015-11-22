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

struct Field* createFieldList(char* names, char* values, int count) {
  // Must use CALLOC instead of MALLOC
  // because field list should be NULL TERMINATED!
  struct Field* fieldList = calloc(count+1, FIELD_SIZE);
  for(int i = 0; i < count; i++) {
    (fieldList+i)->name = (names+(i*NAME_LIMIT));
    (fieldList+i)->value = (values+(i*VALUE_LIMIT));
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
