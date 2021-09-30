/*
 * copy command:
 * copy a file and give it a new name
 */

#pragma once
#include <string>
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class CopyCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  CopyCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
