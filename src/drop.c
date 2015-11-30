#include "common.h"
#include "commandHelpers.h"
/*SCostello 11/28/15 - start*/
/*modified 11/29*/

void dropDatabase(struct Command * removeCommand)
{

  assert(removeCommand->commandType == DROP_DATABASE, "Incompatible Command commanType to function dropDatabase");
  //create a pathname buffer
  char folderPath[NAME_LIMIT];
  //getcwd(folderPath, sizeof(folderPath));
  //format pathname for directory and "table" name
  sprintf(folderPath, "out/%s", removeCommand->table);
  //call remove directory with pathname to table
  rmdir(folderPath);
} 

void dropTable(struct Command* removeTableCommand)
{

  assert(removeTableCommand->commandType == DROP_TABLE, "Incompatible Command commandType to function dropTable");

  char folderPath[NAME_LIMIT];
  //getcwd(folderPath, sizeof(folderPath));
//uses current database directory to drop a table
  sprintf(folderPath, "%s/%s", DATABASE_DIR, removeTableCommand->table);

  rmdir(folderPath);
}
