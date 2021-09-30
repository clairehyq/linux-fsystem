/*
 * touch command:
 * create a file
 */

#pragma once
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class AbstractFileFactory;
class TouchCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;   /* for storing the files created */
  AbstractFileFactory* file_factory; /* for creating files */ 
public:
  TouchCommand(AbstractFileSystem*, AbstractFileFactory*);
  int execute(string) override;
  void displayInfo() override;
};
