#pragma once

/*
 * The following functions are just helpers to create
 * sample valid Command structures with vales you can
 * override.
 */
struct Where* createWhere(char fields[30], enum whereCompare compareType);

struct Command* createWSelectCommand(char* table, struct Field* projection[50], struct Where* whereConstraints);

struct Command* createSelectCommand(char* table);

struct Command* createCreateDatabaseCommand(char* databaseName);

struct Command* createCreateTableCommand(char*, struct Field*[50]);

struct Field* createFieldList(char names[FIELD_LIMIT][NAME_LIMIT], char values[FIELD_LIMIT][VALUE_LIMIT], struct FieldType[FIELD_LIMIT][1], int count);

struct Field* createField(char* name, char* value, struct FieldType type);

struct Command* createInsertCommand(char*, struct Field*[50]);

struct Tuple* createTuple(struct Field* fields);

struct Tuple* createTupleList(struct Field* fields, int count);

void destroyCommand(struct Command*);

void insertTuple(struct Command* cmd);
struct FieldType* createFieldType(enum field_t ft, int ml, int mr);
