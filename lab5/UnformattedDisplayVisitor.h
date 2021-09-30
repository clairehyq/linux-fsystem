/*
 * used in unformatted display
 * password files and textfiles are treated 
 *   the same way as BasicDisplayVisitor
 */

#include "BasicDisplayVisitor.h"
class UnformattedDisplayVisitor : public BasicDisplayVisitor
{
  void visitImageFile(ImageFile*) override;
};
