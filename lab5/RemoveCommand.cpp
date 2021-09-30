/*
 * remove command:
 * remove a file from the filesystem
 */

#include <iostream>
#include "RemoveCommand.h"
#include "AbstractFileSystem.h"
#include "FileExtensions.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
using namespace std;

/* constructor */
RemoveCommand::RemoveCommand(AbstractFileSystem *fs):
  file_system(fs) {}

int RemoveCommand::execute(string file)
{
  if (file.empty()) return COMMAND_SYNTAX_ERR;
  return file_system->deleteFile(file);
}

void RemoveCommand::displayInfo()
{
  static const char usage[] = "rm <filename>: remove a single file";
  cout << usage << endl;
}
