/*
 * extra credit: grep command
 * find which file(s) contain a pattern
 * our grep will ignore the password protected files
 */

#pragma once
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class GrepCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  GrepCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
