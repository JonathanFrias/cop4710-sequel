#include "common.h"


/*
 * The following functions are just helpers to create
 * sample valid parseTree structures with vales you can
 * override.
 */
struct ParseTree* createSelectParseTree(char* table, struct Field* fields, struct Where* whereConstraints);
struct Where* createWhere(struct Field* fields, whereCompare compareType);

struct Field* createField(char* name, char* value) {
  struct Field* field = (struct Field*) malloc(sizeof(struct Field));

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

struct Where* createWhere(struct Field* field, whereCompare compareType) {
  struct Where* whereCondition = malloc(WHERE_SIZE);

  if(field) {
    whereCondition->field = field;
  } else {
    whereCondition->field = createField("WhereCondname", "WhereCondValue");
  }
  return whereCondition;
}

struct ParseTree* createSelectParseTree(char* table, struct Field* fields, struct Where* whereConstraints) {
  struct ParseTree* tree = malloc(PARSETREE_SIZE);

  if(table) {
    tree->table = table;
  } else {
    tree->table = "default_table";
  }

  if(fields) {
    tree->fields = fields;
  } else {
    tree->fields = createField("selectName", "selectVal");
  }

  return tree;
}

