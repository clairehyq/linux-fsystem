/*
 * inspired by std::lockguard
 * when this object goes out of scope
 * the destructor will close a file opened
 */

#include "CloseGuard.h"
#include "AbstractFileSystem.h"

/* constructor */
CloseGuard::CloseGuard(AbstractFileSystem* _fs, AbstractFile* _file):
  fs(_fs),
  file(_file) {}

/* destructor */
CloseGuard::~CloseGuard()
{
  fs->closeFile(file);
}
