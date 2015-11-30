
void applyWhere(struct Table* table, struct Command* cmd, int fieldCount);

int comparator(const void *, const void*);
bool textLt(char* a, char* b);
bool textGt(char* a, char* b);
bool textEq(char* a, char* b);
bool intEq(char* a, char* b);
bool intLt(char* a, char* b);
bool intGt(char* a, char* b);
