/*
 * for macro commands:
 *  when a macro command is fed with an input,
 *  the input will be transformed into a vector of inputs
 *  each of which will be fed into every command inside that macro command
 */

#pragma once
#include <vector>
#include <string>
using namespace std;

class AbstractParsingStrategy
{
public:
  virtual ~AbstractParsingStrategy() = default;
  virtual vector<string> parse(string) = 0;
};
