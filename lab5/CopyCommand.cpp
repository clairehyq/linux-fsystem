/*
 * copy command:
 * copy a file and give it a new name
 */

#include <iostream>
#include <vector>
#include <string>
#include "CopyCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "util.h"
#include "FileExtensions.h"
#include "CloseGuard.h"
using namespace std;

/* constructor */
CopyCommand::CopyCommand(AbstractFileSystem *fs):
  file_system(fs) {}

/* cp <file_to_copy> <new_name_with_no_extension> */
int CopyCommand::execute(string argstr)
{
  if (argstr.empty()) return COMMAND_SYNTAX_ERR;

  auto args = splitBySpace(argstr);
  if (args.size() != 2) return COMMAND_SYNTAX_ERR;

  string src_filename = args[0], dest_filename_no_ext = args[1];

  // src should be different frome dest
  string src_filename_no_ext, ext;
  int err = splitExt(src_filename, src_filename_no_ext, ext);
  if (err != OK) return err;
  if (src_filename_no_ext == dest_filename_no_ext) return COMMAND_SYNTAX_ERR;
  string dest_filename = dest_filename_no_ext + "." + ext;

  // src should exists
  // src should not be opened already
  AbstractFile* src_file = file_system->openFile(src_filename);
  if (!src_file) return CANT_OPEN_FILE;
  CloseGuard guard(file_system, src_file);

  // dest should not be taken
  AbstractFile* dest_file = src_file->clone(dest_filename);
  err = file_system->addFile(dest_filename, dest_file);
  if (err != OK) {
    delete dest_file;
    return err;
  }

  return OK;
}

void CopyCommand::displayInfo()
{
  static const char usage[] = "cp <file_to_copy> <new_name_with_no_extension>";
  cout << usage << endl;
}
