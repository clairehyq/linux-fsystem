/*
 * ls command:
 * list all files
 */

#pragma once
#include <string>
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class LSCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  LSCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
