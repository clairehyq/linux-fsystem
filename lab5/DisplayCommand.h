/*
 * display command:
 * display a file through ASCII
 */

#pragma once
#include <string>
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class DisplayCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  DisplayCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
