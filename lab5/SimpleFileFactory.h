/*
 * Studio 18 - simplefilefactory class declaration goes here
 */

#pragma once
#include "AbstractFileFactory.h"

class SimpleFileFactory : public AbstractFileFactory
{
  public:
  AbstractFile* createFile(string);
};
