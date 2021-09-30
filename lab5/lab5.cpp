/*
 * contains main() for this lab
 * sets up the commandline with all commands
 */

#include "CommandPrompt.h"
#include "ErrorCodes.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"

#include "TouchCommand.h"
#include "RemoveCommand.h"
#include "CatCommand.h"
#include "LSCommand.h"
#include "CopyCommand.h"
#include "RenameCommand.h"
#include "DisplayCommand.h"
#include "GrepCommand.h"

#include <iostream>
using namespace std;

int main()
{
  CommandPrompt cmd;
  SimpleFileSystem fs;
  SimpleFileFactory ff;
  cmd.setFileSystem(&fs);
  cmd.setFileFactory(&ff);

  TouchCommand touchCommand(&fs, &ff);
  cmd.addCommand("touch", &touchCommand);

  LSCommand ls(&fs);
  cmd.addCommand("ls", &ls);

  RemoveCommand rm(&fs);
  cmd.addCommand("rm", &rm);

  CatCommand cat(&fs);
  cmd.addCommand("cat", &cat);

  DisplayCommand ds(&fs);
  cmd.addCommand("ds", &ds);

  CopyCommand cp(&fs);
  cmd.addCommand("cp", &cp);

  RenameCommand rn(&cp, &rm);
  cmd.addCommand("rn", &rn);

  GrepCommand grep(&fs);
  cmd.addCommand("grep", &grep);

  int ret = cmd.run();
  cout << "shell exited with status " << ret
       << ": " << getErrorString(ret) << endl;

  fs.clear();
  
  return OK;
}
