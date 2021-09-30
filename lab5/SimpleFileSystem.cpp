/*
 * define methods of SimpleFileSystem class here
 */

#include "SimpleFileSystem.h"
#include "AbstractFile.h"
#include "ErrorCodes.h"
#include "ImageFile.h"
#include "TextFile.h"

/* deleting all files */
void SimpleFileSystem::clear() 
{
  for (auto& p: file_map) delete p.second;
}

/* add a file to simplefile system */
int SimpleFileSystem::addFile(string name, AbstractFile* file)
{
  if (file_map.count(name)) return FILE_EXISTS;
  if (!file) return NULL_ERR;     // should never reach this case
  file_map.insert(make_pair(name, file));
  filename_set.insert(name);
  return OK;
}

/* open a file */
AbstractFile* SimpleFileSystem::openFile(string name) 
{
  auto p = file_map.find(name);
  if (p == file_map.end()) return nullptr;
  
  AbstractFile* file = p->second;
  if (open_files.count(file)) return nullptr;

  open_files.insert(file);
  return file;
}

/* close a file */
int SimpleFileSystem::closeFile(AbstractFile* file)
{
  if (open_files.count(file) == 0) return FILE_NOT_OPEN;

  open_files.erase(file); 
  return OK;
}

/* delete a file */
int SimpleFileSystem::deleteFile(string name) 
{
  auto p = file_map.find(name);
  if (p == file_map.end()) return FILE_NOT_FOUND;

  AbstractFile* file = p->second;
  if (open_files.count(file)) return FILE_OPEN;

  file_map.erase(p);
  filename_set.erase(name);
  delete file;
  return OK;
}

/* returns a read-only set of filenames */
const set<string>& SimpleFileSystem::getFileNames() const
{
  return filename_set;
}
