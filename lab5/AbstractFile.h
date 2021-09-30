/*
 * interface for a file in our filesystem
 */

#pragma once
#include <string>
#include <vector>
using namespace std;

class AbstractFileVisitor;
class AbstractFile
{
  public:
  virtual ~AbstractFile() = default;
  virtual AbstractFile* clone(string = "") const = 0;

  virtual vector<char> read() const = 0;
  virtual int write(vector<char>) = 0;
  virtual int append(vector<char>) = 0;
  virtual int getSize() const = 0; /* file size */
  virtual string getName() const = 0;
  virtual void accept(AbstractFileVisitor*) = 0;
};
