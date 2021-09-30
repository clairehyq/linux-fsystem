/*
 * used in unformatted display
 * password files and textfiles are treated 
 *   the same way as BasicDisplayVisitor
 */

#include "UnformattedDisplayVisitor.h"
#include "util.h"
#include "ImageFile.h"
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

void UnformattedDisplayVisitor::visitImageFile(ImageFile* file)
{
  auto content = file->read();
  cout << content << endl;
}
