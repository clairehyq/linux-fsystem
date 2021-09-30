/*
 * declaration of the interface all file systems provide goes here
 * file system: open/close, create/delete files
 */

#pragma once
#include <string>
#include <vector>
#include <set>
using namespace std;

class AbstractFile;
class AbstractFileSystem
{
public:
  virtual ~AbstractFileSystem() = default;
  virtual void clear() = 0; 
  virtual int addFile(string, AbstractFile*) = 0;
  virtual int deleteFile(string) = 0;
  virtual AbstractFile* openFile(string) = 0;
  virtual int closeFile(AbstractFile*) = 0;
  virtual const set<string>& getFileNames() const = 0;
};
