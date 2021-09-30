/*
 * touch command:
 * create a file
 */

#include "TouchCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "PasswordProxy.h"
#include "util.h"
#include <iostream>

/*
 * constructor
 */
TouchCommand::TouchCommand(AbstractFileSystem *fs, AbstractFileFactory *ff):
  file_system(fs), file_factory(ff) {}

/*
 * touch <filename>
 * touch <filename> -p : create a password protected file
 */
int TouchCommand::execute(string argstr)
{
  if (argstr.empty()) return COMMAND_SYNTAX_ERR;

  auto args = splitBySpace(argstr);
  if (args.size() == 0 || args.size() > 2) return COMMAND_SYNTAX_ERR;

  // parse 
  bool hasPassword;
  string filename;
  if (args.size() == 1) {  // touch <filename>
    if (args[0] == "-p") return COMMAND_SYNTAX_ERR;

    hasPassword = false;
    filename = args[0];
  } else {                 // touch -p <filename>
    bool flag0 = args[0] == "-p";
    bool flag1 = args[1] == "-p";
    if (flag0 == flag1) return COMMAND_SYNTAX_ERR;
    
    hasPassword = true;
    filename = flag0 ? args[1] : args[0];
  }

  // create the file
  AbstractFile* internal_file = file_factory->createFile(filename);
  if (!internal_file) return FILENAME_EXT_ERR; // the only kind of error for now
  
  // add to the file system
  int err = file_system->addFile(filename, internal_file);
  if (err != OK) {
    delete internal_file;
    return err;
  }

  // if it is password protected, replace the file with a password proxy
  if (hasPassword) {
    file_system->deleteFile(filename); // internal_file is deleted!
    PasswordProxy *password_file = new PasswordProxy(
        file_factory->createFile(filename), PasswordProxy::enterPassword());
    err = file_system->addFile(filename, password_file);
    if (err != OK) {
      delete password_file;
      return err;
    }
  }

  return OK;
}

void TouchCommand::displayInfo()
{
  static const char usage[] = "touch <filename>: create a single file\n"
    "touch <filename> -p: create a password protected file";
  cout << usage << endl;
}
