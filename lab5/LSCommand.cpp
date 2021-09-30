/*
 * ls command:
 * list all files
 */

#include <iostream>
#include "LSCommand.h"
#include "AbstractFileSystem.h"
#include "FileExtensions.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "CloseGuard.h"
using namespace std;

/* constructor */
LSCommand::LSCommand(AbstractFileSystem *fs):
  file_system(fs) {}

/*
 * ls    : just the file names
 * ls -m : like -l in linux
 */
int LSCommand::execute(string option)
{
  auto file_set = file_system->getFileNames();
  
  // verbose option
  if (option == "-m") {
    static const int WIDTH = 12;
    for (const auto& str : file_set) {
      AbstractFile* file = file_system->openFile(str);
      if (!file) return CANT_OPEN_FILE;
      CloseGuard guard(file_system, file);

      int len = str.size();
      cout << str << (len < WIDTH ? string(WIDTH-len, ' ') : "")
           << "\t" << getExtInfo(getExt(str))
           << "\t" << file->getSize() << endl;
    }
  }

  // no option: just filenames
  else if (option.empty()) {
    static const int WIDTH = 20;
    int cnt = 0;
    for (const auto& str : file_set) {
      int len = str.length();
      if (len >= WIDTH) {
        cout << str << endl;
        cnt = 0;
      } else {
        cout << str << string(WIDTH-len, ' ');
        if (++cnt == 2) {
          cout << endl;
          cnt = 0;
        }
      }
    }
    if (cnt) cout << endl;
  }
  else return COMMAND_SYNTAX_ERR;

  return OK;
}

void LSCommand::displayInfo()
{
  static const char usage[] = "ls: list all files\n"
    "ls -m: list all files vertically with extra information";
  cout << usage << endl;
}
