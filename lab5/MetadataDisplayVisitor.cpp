/*
 * definitions of metadata visitor here
 */

#include "MetadataDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "PasswordProxy.h"
#include "FileExtensions.h"
#include <iostream>
using namespace std;

static void printMetadata(AbstractFile* file)
{
  cout << "filename:\t" << file->getName() << endl
       << "type:\t" << getExtInfo(getExt(file->getName())) << endl
       << "size:\t" << file->getSize() << endl;
}

void MetadataDisplayVisitor::visitTextFile(TextFile* file) 
{
  printMetadata(file);
}

void MetadataDisplayVisitor::visitImageFile(ImageFile* file)
{
  printMetadata(file);
}

void MetadataDisplayVisitor::visitPasswordProxy(PasswordProxy* file)
{
  printMetadata(file);
}
