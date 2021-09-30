/*
 * definition of BasicDisplayVisitor here
 * used in DisplayCommand
 * will format the image file
 */

#include "BasicDisplayVisitor.h"
#include "AbstractFileVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"
#include "PasswordProxy.h"
#include "ErrorCodes.h"
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

/* txtfiles are printed directly */
void BasicDisplayVisitor::visitTextFile(TextFile* file)
{
  auto content = file->read();
  copy(content.begin(), content.end(), 
      ostream_iterator<char>(cout));
}

/* format image, using regular Euclidean axes 
   lowerleft is (0,0) */
void BasicDisplayVisitor::visitImageFile(ImageFile* file)
{
  auto content = file->read();
  auto n = file->getDim();
  for (int y = n-1; y >= 0; --y) {
    copy_n(content.begin() + y * n, n, ostream_iterator<char>(cout));
    cout << endl;
  }
}

/* prompt password and then delegate */
void BasicDisplayVisitor::visitPasswordProxy(PasswordProxy* file)
{
  AbstractFile* internal_file = file->getFile(PasswordProxy::enterPassword());
  if (!internal_file) {
    cout << getErrorString(PASSWORD_MISMATCH) << endl;
    return;
  }
  internal_file->accept(this);
}
