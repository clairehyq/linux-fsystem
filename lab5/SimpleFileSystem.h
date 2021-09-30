/*
 * declaration of SimpleFileSystem class goes here
 */

#pragma once

#include "AbstractFileSystem.h"
#include <map>
#include <set>

class AbstractFile;
class SimpleFileSystem : public AbstractFileSystem
{
  map<string, AbstractFile*> file_map;
  set<string> filename_set;
  set<AbstractFile*> open_files; 

public:
  void clear() override; 
  int addFile(string, AbstractFile*) override;
  AbstractFile* openFile(string) override;
  int closeFile(AbstractFile*) override;
  int deleteFile(string) override;
  const set<string>& getFileNames() const override;
};

