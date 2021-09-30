/*
 * password protected wrapper of normal files
 */

#include "PasswordProxy.h"
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "ErrorCodes.h"
#include <iostream>

/* constructor */
PasswordProxy::PasswordProxy(AbstractFile* _file, string _password):
  file(_file), password(_password){}

/* clone */
AbstractFile* PasswordProxy::clone(string new_name) const
{
  return new PasswordProxy(file->clone(new_name), password);
}

/* does the proxy manages the memory of the protected file */
PasswordProxy::~PasswordProxy()
{
  delete file; 
}

/* password prompts */
string PasswordProxy::enterPassword()
{
  cout << "please enter the password: " << endl;
  string ret;
  getline(cin, ret);  // TODO hide the password with *
  return ret;
}
string PasswordProxy::passwordPrompt() const
{
  return enterPassword();
}

/* all read/write requires passwords */
vector<char> PasswordProxy::read() const
{
  string entered_password = passwordPrompt();
  if (entered_password != password) {
    cout << getErrorString(PASSWORD_MISMATCH) << endl;
    return {};
  }

  return file->read();
}

int PasswordProxy::write(vector<char> new_content) 
{
  string entered_password = passwordPrompt();
  if (entered_password != password) return PASSWORD_MISMATCH;

  return file->write(new_content);
}

int PasswordProxy::append(vector<char> new_content)
{
  string entered_password = passwordPrompt();
  if (entered_password != password) return PASSWORD_MISMATCH;

  return file->append(new_content);
}

AbstractFile* PasswordProxy::getFile(const string &entered_password) const
{
  return entered_password == password ? file : nullptr;
}

void PasswordProxy::accept(AbstractFileVisitor* visitor)
{
  visitor->visitPasswordProxy(this);
}

/* metadata can be read without passwords */
int PasswordProxy::getSize() const
{
  return file->getSize();
}

string PasswordProxy::getName() const
{
  return file->getName();
}
