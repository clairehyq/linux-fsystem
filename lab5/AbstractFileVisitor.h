/*
 * declaration of the file visitor interface here
 * visitor pattern
 */

#pragma once
class TextFile;
class ImageFile;
class PasswordProxy;
class AbstractFileVisitor
{
public:
  virtual ~AbstractFileVisitor() = default;

  /* double dispatches */
  virtual void visitTextFile(TextFile*) = 0;
  virtual void visitImageFile(ImageFile*) = 0;

  /* some visitors have does something special to password protected files */
  /* for example: GrepVisitor ignores password protected files */
  virtual void visitPasswordProxy(PasswordProxy*) = 0;
};
