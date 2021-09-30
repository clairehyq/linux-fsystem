/*
 * RenameCommand is implemented using copy and remove:
 *   copy the original file, give it a new name
 *   and then remove the old file
 */

#pragma once
#include "AbstractCommand.h"
#include "MacroCommand.h"
using namespace std;

class CopyCommand;
class RemoveCommand;
class RenameCommand : public MacroCommand
{
public:
  RenameCommand(CopyCommand*, RemoveCommand*);
  void displayInfo() override;
  
  /* the execute function is defined in MacroCommand 
     which is to execute copy and remove in order */
};
