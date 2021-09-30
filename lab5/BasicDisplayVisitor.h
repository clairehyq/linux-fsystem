/*
 * declaration of BasicDisplayVisitor here
 * used in DisplayCommand
 * will format the image file
 */

#pragma once

#include "AbstractFileVisitor.h"
class BasicDisplayVisitor : public AbstractFileVisitor
{
  void visitImageFile(ImageFile*) override;
  void visitTextFile(TextFile*) override;
  void visitPasswordProxy(PasswordProxy*) override;
};
