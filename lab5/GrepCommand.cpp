/*
 * extra credit: grep command
 * find which file(s) contain a pattern
 * our grep will ignore the password protected files
 */

#include "GrepCommand.h"
#include "AbstractFileSystem.h"
#include "GrepVisitor.h"
#include "ErrorCodes.h"
#include "AbstractFile.h"
#include "CloseGuard.h"
#include <iostream>

/*
 * constructor
 */
GrepCommand::GrepCommand(AbstractFileSystem* fs):
  file_system(fs) {}

/*
 * find which file(s) contain a pattern
 */
int GrepCommand::execute(string pattern)
{
  if (pattern.empty()) return COMMAND_SYNTAX_ERR;

  /* visit each file, if found, print out the filename */
  GrepVisitor grep_visitor(pattern);
  for (const string& filename : file_system->getFileNames()) {
    AbstractFile* file = file_system->openFile(filename);
    if (!file) return CANT_OPEN_FILE;
    CloseGuard guard(file_system, file);
    
    grep_visitor.reset();  /* reset the state, so that this visitor 
                              can be used for other files */
    file->accept(&grep_visitor);
    if (grep_visitor.foundQ()) {
      cout << filename << endl;
    }
  }
  return OK;
}

void GrepCommand::displayInfo()
{
  static const char USAGE[] = "grep <string_to_search_for>";
  cout << USAGE << endl;
}
