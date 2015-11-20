#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"

void setupStorage(void) {
  struct stat st = {0};

  char folderPath[100];
  getcwd(folderPath, sizeof(folderPath));

  sprintf(folderPath, "%s/out/%s/%s", folderPath, DATABASE_DIR);

  mkdir(DATABASE_DIR, 0700);

}

void createDatabase(char* database) {
  setupStorage();
  exit(2);
  struct stat st = {0};

  char folderPath[100];
  getcwd(folderPath, sizeof(folderPath));

  sprintf(folderPath, "%s/out/%s/%s", folderPath, DATABASE_DIR, database);

  mkdir(DATABASE_DIR, 0700);
  printf("\n%s\n", folderPath);
  if (stat(folderPath, &st) == -1) {
    mkdir(folderPath, 0700);
  }
}
