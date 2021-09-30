/*
 * password protected wrapper of normal files
 */

#pragma once
#include <string>
#include "AbstractFile.h"
using namespace std;

class PasswordProxy : public AbstractFile
{
  AbstractFile* file;
  string password;

public:
  PasswordProxy(AbstractFile*, string);
  ~PasswordProxy();
  AbstractFile* clone(string = "") const override;

  /* prompt password
     public due to testing */
  static string enterPassword();
  string passwordPrompt() const;

  /* returns the protected file, if the password matches */
  AbstractFile* getFile(const string&) const;

  /* delegations */
  vector<char> read() const override;
  int write(vector<char>) override;
  int append(vector<char>) override;
  int getSize() const override;
  string getName() const override;
  void accept(AbstractFileVisitor*) override;
};
