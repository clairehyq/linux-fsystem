/*
 * declaration of MetadataDisplayVisitor here
 */
#pragma once
#include "AbstractFileVisitor.h"

class MetadataDisplayVisitor : public AbstractFileVisitor
{
public:
  void visitTextFile(TextFile*) override;
  void visitImageFile(ImageFile*) override;
  void visitPasswordProxy(PasswordProxy*) override;
};
