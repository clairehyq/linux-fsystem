/*
 * TextFile declaration goes here
 */
#pragma once

#include <vector>
#include <string>
#include "AbstractFile.h"
using namespace std;

class TextFile : public AbstractFile
{
  string name;          /* file name */
  vector<char> content; /* file content */

  TextFile(const TextFile&);

  public:
  explicit TextFile(string);
  ~TextFile() = default;
  AbstractFile* clone(string = "") const override;

  int getSize() const override;
  string getName() const override;
  int write(vector<char>) override;
  int append(vector<char>) override;
  vector<char> read() const override;
  void accept(AbstractFileVisitor*) override;
};

