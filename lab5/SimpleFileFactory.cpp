/*
 * studio 18 - simple file factory definitions
 */

#include "SimpleFileFactory.h"
#include "ErrorCodes.h"
#include "ImageFile.h"
#include "TextFile.h"
#include "FileExtensions.h"

/* use the filename to determine the type of file to create */
AbstractFile* SimpleFileFactory::createFile(string name)
{
  string pre, ext;
  if (OK != splitExt(name, pre, ext)) return nullptr;

  if (ext == EXT_IMG) return new ImageFile(name);
  else if (ext == EXT_TXT) return new TextFile(name);
  else return nullptr;
}

