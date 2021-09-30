/*
 * unlike the cat in linux,
 * this cat is responsible for writing to a file
 */

#include <iostream>
#include <vector>
#include <string>
#include "CatCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "CloseGuard.h"
#include "util.h"
using namespace std;

/* constructor */
CatCommand::CatCommand(AbstractFileSystem *fs):
  file_system(fs) {}

/*
 * cat <filename>     : overwrite
 * cat <filename> -a  : append
 */
int CatCommand::execute(string argstr)
{
  if (argstr.empty()) return COMMAND_SYNTAX_ERR;

  auto args = splitBySpace(argstr);
  if (args.size() == 0 || args.size() > 2) return COMMAND_SYNTAX_ERR;

  // parse 
  bool intentToAppend;
  string filename;
  if (args.size() == 1) {  // cat <filename>
    if (args[0] == "-a") return COMMAND_SYNTAX_ERR;

    intentToAppend = false;
    filename = args[0];
  } else {                 // cat -a <filename>
    bool flag0 = args[0] == "-a";
    bool flag1 = args[1] == "-a";
    if (flag0 == flag1) return COMMAND_SYNTAX_ERR;
    
    intentToAppend = true;
    filename = flag0 ? args[1] : args[0];
  }

  // open file
  AbstractFile *file = file_system->openFile(filename);
  if (!file) return CANT_OPEN_FILE;
  CloseGuard guard(file_system, file);

  if (intentToAppend) cout << file->read();

  // get user input
  vector<char> input;
  bool intentToSave = false;
  for (string line; getline(cin, line); ) {
    if (line == ":wq") {
      intentToSave = true;
      if (input.size()) input.pop_back(); // get rid of the last \n
      break;
    }
    else if (line == ":q") {
      intentToSave = false;
      break;
    }
    else {
      input.insert(input.end(), line.begin(), line.end());
      input.push_back('\n');
    }
  }

  // save
  if (intentToSave) {
    int err = intentToAppend
      ? file->append(input)
      : file->write(input);
    if (err != OK) return err;
  }

  return OK;
}

void CatCommand::displayInfo()
{
  static const char usage[] = "cat <filename>: overwrite a file\n"
    "cat <filename> -a: append a file\n"
    "the input is read line by line, util either of these is read\n"
    "  :wq\tsave and quit\n"
    "  :q\tquit, discard all changes";
  cout << usage << endl;
}
