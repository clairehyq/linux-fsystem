/*
 * the REPL
 */

#pragma once
#include <map>
using namespace std;

class AbstractFileSystem;
class AbstractFileFactory;
class AbstractCommand;
class CommandPrompt
{
  /* dynamic addition of commands */
  map<string, AbstractCommand*> command_map;

  AbstractFileSystem* file_system;
  AbstractFileFactory* file_factory;
public:
  void listCommands() const;
  ~CommandPrompt() = default;
  string prompt();
  CommandPrompt();

  /* setters */
  void setFileSystem(AbstractFileSystem*);
  void setFileFactory(AbstractFileFactory*);
  int addCommand(string, AbstractCommand*);

  /* run the REPL */
  int run();
};
