struct Field {
  char* name;
  void* value;
};

struct Tuple {
  struct Field* id;
  struct Field* fields;
  int updatedAt;
};

struct {
  struct Field field;
  void* target;
  enum {
    LESS_THAN,
    GREATHER_THAN,
    // ...
  } compareType;
} Where;

// parse 

struct ParseTree {
  enum {
    CREATE_DATABASE,
    CREATE_TABLE,
    DROP_DATABASE,
    DROP_TABLE,
    COMMIT,
    SAVE,
    LOAD_DATABASE,
    SELECT,
    wSELECT,
    INSERT,
    UPDATE,
    wUPDATE,
    DELETE
  } commandType;
  char* table;
  struct Field* fields;
  struct Where* whereConstraints;
  struct Field* updateFields;
  struct Field* insertFields;
};

struct ParseTree* parseGrammer(char* sql);

// Store/Retrieve

void store(struct Tuple* tuples, int count);

struct Tuple* retrieve(struct ParseTree tree); // Tuple list returned must be NULL terminated.
