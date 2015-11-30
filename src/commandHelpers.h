/*
 * The following functions are just helpers to create
 * sample valid Command structures with vales you can
 * override.
 */
struct Where* createWhere(struct Field* field, whereType compareType);
struct Command* createWSelectCommand(char* table, struct Field* projection[50], struct Where* whereConstraints);
struct Command* createSelectCommand(char* table, struct Field* fields[50], struct Where* whereConstraints);
struct Command* createCreateDatabaseCommand(char* databaseName);
struct Command* createCreateTableCommand(char*, struct Field*[50]);
struct Field* createFieldList(char names[FIELD_LIMIT][NAME_LIMIT], char values[FIELD_LIMIT][VALUE_LIMIT], FieldType[FIELD_LIMIT][1], int count);
struct Field* createField(char* name, char* value, FieldType type);
struct Command* createInsertCommand(char*, struct Field*[50]);
struct Tuple* createTuple(struct Field* fields);
struct Tuple* createTupleList(struct Field* fields, int count);
void destroyCommand(struct Command*);
void insertTuple(struct Command* cmd);
