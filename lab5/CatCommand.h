/*
 * unlike the cat in linux,
 * this cat is responsible for writing to a file
 */

#pragma once
#include <string>
#include "AbstractCommand.h"
using namespace std;

class AbstractFileSystem;
class CatCommand : public AbstractCommand
{
  AbstractFileSystem* file_system;
public:
  CatCommand(AbstractFileSystem*);
  int execute(string) override;
  void displayInfo() override;
};
