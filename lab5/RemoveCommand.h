/*
 * remove command:
 * remove a file from the filesystem
 */

#pragma once
#include <string>
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class RemoveCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  RemoveCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
