/*
 * The following functions are just helpers to create
 * sample valid parseTree structures with vales you can
 * override.
 */
struct Where* createWhere(struct Field* fields, whereCompare compareType);
struct ParseTree* createWSelectParseTree(char* table, struct Field* projection, struct Where* whereConstraints);
struct ParseTree* createSelectParseTree(char* table, struct Field* fields, struct Where* whereConstraints);
struct ParseTree* createCreateDatabaseParseTree(char* databaseName);
struct ParseTree* createCreateTableParseTree(char*, struct Field*);
struct Field* createFieldList(char* names, char* values, int count);
