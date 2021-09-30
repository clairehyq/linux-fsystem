/*
 * implement RenameCommand using copy and remove
 *   copy the original file, give it a new name
 *   and then remove the old file
 */

#include "RenameCommand.h"
#include "AbstractParsingStrategy.h"
#include "CopyCommand.h"
#include "RemoveCommand.h"
#include "RenameParsingStrategy.h"
#include <iostream>

/* constructor */
RenameCommand::RenameCommand
(CopyCommand* cp, RemoveCommand* rm)
{
  addCommand(cp);
  addCommand(rm);
  static RenameParsingStrategy parser;
  setParseStrategy(&parser);
}

void RenameCommand::displayInfo()
{
  static const char USAGE[] = 
    "rn <existing_file> <new_name_with_no_extension>\n"
    "example: rn cheetah.img lion\n"
    "  this will change cheetah.img to lion.img";
  cout << USAGE << endl;
}
