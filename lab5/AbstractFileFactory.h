/*
 * studio 18 - file factory interface declared here
 * a class responsible for creating files given a filename
 */

#pragma once
#include <string>
using namespace std;

class AbstractFile;
class AbstractFileFactory
{
public:
  virtual ~AbstractFileFactory() = default;
  virtual AbstractFile* createFile(string) = 0;
};
