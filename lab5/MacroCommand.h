/*
 * A MacroCommand is implemented using other Commands
 */

#pragma once
#include "AbstractCommand.h"
#include <vector>
using namespace std;

class AbstractFileSystem;
class AbstractFileFactory;
class AbstractParsingStrategy;
class MacroCommand : public AbstractCommand
{
  vector<AbstractCommand*> commands; /* command chain */

  /* A parser transitions one input to the MacroCommand to 
     multiple inputs, one for each command in the command chain */
  AbstractParsingStrategy* parser;   

public:
  MacroCommand() = default;
  virtual ~MacroCommand() = default;

  /* to pass the piazza tests,
     MacroCommand doesn't need a file system */
  MacroCommand(AbstractFileSystem*);

  /* add command to the command chain */
  void addCommand(AbstractCommand*);

  /* setter for parser */
  void setParseStrategy(AbstractParsingStrategy*);

  /* transform the input and then execute each command in order */
  int execute(string) override;

  /* this method should be overriden */
  void displayInfo() override;
};
