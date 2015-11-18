
#include "common.h"

int main(void) {
  struct ParseTree* p = (struct ParseTree*) malloc(PARSETREE_SIZE);
  p->commandType = SELECT;
  p->table = "table1";
  p->fields = malloc(FIELD_SIZE * 10);

  printf("%s\n", p->table);
  return 0;
}
