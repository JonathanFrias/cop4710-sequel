#include "common.h"
#include "commandHelpers.h"
/*SCostello 11/28/15 - start*/
/*modified 11/29*/

void dropDatabase(struct Command * removeCommand)
{

  assert(removeCommand->commandType == DROP_DATABASE, "Incompatible Command commanType to function dropDatabase");
  //create a pathname buffer
  char folderPath[NAME_LIMIT];
  //format pathname for directory and "table" name
  sprintf(folderPath, "%s/%s", DATABASE_DIR, removeCommand->table);
  assert(rmdir(folderPath) == 0, "directory drop failed, directory not empty or does not exist");
  
} 

void dropTable(struct Command* removeTableCommand)
{

  assert(removeTableCommand->commandType == DROP_TABLE, "Incompatible Command commandType to function dropTable");

  char folderPath[NAME_LIMIT];
  //getcwd(folderPath, sizeof(folderPath));
//uses current database directory to drop a table
  sprintf(folderPath, "%s/%s/%s", DATABASE_DIR, currentDatabase, removeTableCommand->table);

 assert(unlink(folderPath) == 0, "failed to remove table");
}
