/*
 * display command:
 * display a file through ASCII
 */

#include <iostream>
#include <vector>
#include <string>
#include "DisplayCommand.h"
#include "AbstractFileVisitor.h"
#include "BasicDisplayVisitor.h"
#include "UnformattedDisplayVisitor.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "util.h"
#include "CloseGuard.h"
using namespace std;

/* constructor */
DisplayCommand::DisplayCommand(AbstractFileSystem *fs):
  file_system(fs) {}

/*
 * ds <filename>     : print formatted bytes
 * ds <filename> -d  : print the raw bytes
 */
int DisplayCommand::execute(string argstr)
{
  if (argstr.empty()) return COMMAND_SYNTAX_ERR;

  auto args = splitBySpace(argstr);
  if (args.size() == 0 || args.size() > 2) return COMMAND_SYNTAX_ERR;

  // parse 
  bool intentToUnformat;
  string filename;
  if (args.size() == 1) {  // cat <filename>
    if (args[0] == "-d") return COMMAND_SYNTAX_ERR;

    intentToUnformat = false;
    filename = args[0];
  } else {                 // cat -a <filename>
    bool flag0 = args[0] == "-d";
    bool flag1 = args[1] == "-d";
    if (flag0 == flag1) return COMMAND_SYNTAX_ERR;
    
    intentToUnformat = true;
    filename = flag0 ? args[1] : args[0];
  }

  // open file
  AbstractFile *file = file_system->openFile(filename);
  if (!file) return CANT_OPEN_FILE;
  CloseGuard guard(file_system, file);

  // display
  AbstractFileVisitor* formatter = intentToUnformat
    ? new UnformattedDisplayVisitor
    : new BasicDisplayVisitor;
  file->accept(formatter);
  delete formatter;

  return OK;
}

void DisplayCommand::displayInfo()
{
  static const char usage[] = "ds <filename>: display a file\n"
    "cat <filename> -d: display the raw bytes of a file (unformatted)\n"
    "eg. an image file would not be reprensted as a nxn grid "
    "if -d is specified";
  cout << usage << endl;
}

