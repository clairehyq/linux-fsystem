/*
 * A MacroCommand is implemented using other Commands
 */

#include "MacroCommand.h"
#include "AbstractParsingStrategy.h"
#include "ErrorCodes.h"
#include <iostream>

/* to pass the piazza tests,
   MacroCommand doesn't need a file system */
MacroCommand::MacroCommand(AbstractFileSystem*){}

/* add command to the command chain */
void MacroCommand::addCommand(AbstractCommand* command)
{
  commands.push_back(command);
}

/* setter for parser */
void MacroCommand::setParseStrategy(AbstractParsingStrategy* _parser)
{
  parser = _parser;
}

/* transform the input and then execute each command in order */
int MacroCommand::execute(string raw_input)
{
  auto inputs = parser->parse(raw_input);
  if (inputs.size() != commands.size()) return COMMAND_SYNTAX_ERR;

  auto input = inputs.begin();
  for (auto command : commands) {
    int err = command->execute(*(input++));
    if (err != OK) return err;
  }

  return OK;
}

void MacroCommand::displayInfo()
{
  cout << "MacroCommand: the macro commands should override"
          "this method" << endl;
}
