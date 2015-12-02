/*
 * The following functions are just helpers to create
 * sample valid Command structures with vales you can
 * override.
 */
struct Where* createWhere(struct Field* field, whereType compareType);
struct Command* createWSelectCommand(char* table, struct Field* projection, struct Where* whereConstraints);
struct Command* createSelectCommand(char* table, struct Field* fields, struct Where* whereConstraints);
struct Command* createCreateDatabaseCommand(char* databaseName);
struct Command* createCreateTableCommand(char*, struct Field*);
struct Field* createFieldList(char names[FIELD_LIMIT][NAME_LIMIT], char values[FIELD_LIMIT][VALUE_LIMIT], FieldType[FIELD_LIMIT][1], int count);
struct Field* addField(char* name, char* value, FieldType type, struct Field* old_fields);
struct Command* createInsertCommand(char*, struct Field*);
struct Tuple* createTuple(struct Field* fields);
struct Tuple* createTupleList(struct Field* fields, int count);
void destroyCommand(struct Command*);
void insertTuple(struct Command* cmd);
void writeHeaderLine(FILE* tableFile, struct Field* list);
struct Command* createUpdateCommand(char* table, struct Field* fieldsToUpdate, struct Where* whereConstraints);
struct Command* createDropDatabaseCommand(char* databaseName);
struct Command* createDropTableCommand(char*);
