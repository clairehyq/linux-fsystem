/*
 * the REPL
 */

#include "CommandPrompt.h"
#include "ErrorCodes.h"
#include "AbstractCommand.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <sstream>

/* constructor */
CommandPrompt::CommandPrompt():
  file_system(nullptr),
  file_factory(nullptr){}

/* setters */
void CommandPrompt::setFileSystem(AbstractFileSystem* fs)
{
  file_system = fs;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* ff)
{
  file_factory = ff;
}

int CommandPrompt::addCommand(string name, AbstractCommand* command)
{
  auto p = command_map.insert(make_pair(name, command));
  if (p.second == false) return COMMAND_EXISTS;
  return OK;
}

/* help will list all the commads  */
void CommandPrompt::listCommands() const
{
  for (auto& p : command_map) {
    cout << p.first << endl;
  }
}

/* ugly sample prompt */
string CommandPrompt::prompt()
{
  static const char HELP[] = "Enter a command, q to quit, "
    "help for a list of commands, "
    "or help followed by a command name for "
    "more information about that command.";
  cout << "\n" << HELP << endl << "$ ";
  string ret;
  getline(cin, ret);
  return ret;
}

/* REPL */
int CommandPrompt::run()
{
  for (;;) {
    bool invalidCommand = false;
    string raw_input = prompt();
    string input = trim(raw_input);

    // quit
    if (cin.eof() || input == "q") return USER_QUIT;

    // empty command
    else if (input.empty()) invalidCommand = true;

    // help
    else if (input == "help") listCommands();

    // just one word
    else if (none_of(input.begin(), input.end(), 
          [](char c){return isspace(c);})) {

      auto p = command_map.find(input);
      if (p != command_map.end()) {
        auto command = p->second;
        int err = command->execute("");
        if (err != OK) {
          cout << getErrorString(err) << endl;
          if (err == COMMAND_SYNTAX_ERR) command->displayInfo();
        }
      } 
      else {
        invalidCommand = true;
      }
    }

    // multiple words
    else {
      
      istringstream iss{input};

      string first_word;
      iss >> first_word;
      
      // help <command>
      if (first_word == "help") {
        string command_name;
        iss >> command_name;

        auto p = command_map.find(command_name);
        if (p != command_map.end()) {
          p->second->displayInfo();
        }
        else {
          cout << "command '" << command_name << "' does not exist" << endl;
        }
      }

      // command with arguments
      else {
        auto p = command_map.find(first_word);
        if (p != command_map.end()) {
          string remaining;
          getline(iss, remaining);
          remaining = trim(remaining);

          auto command = p->second;
          int err = command->execute(remaining);
          if (err != OK) {
            cout << getErrorString(err) << endl;
            if (err == COMMAND_SYNTAX_ERR) command->displayInfo();
          }
        } 
        else {
          invalidCommand = true;
        }
      }
    }

    if (invalidCommand) {
      cout << "not a valid command: " << input << endl;
    } 
  }
}
