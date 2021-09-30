/*
 * for extra credit: grep
 * if a pattern is found in a file, 
 *   GrepVisitor will set its own found to true
 */

#include "GrepVisitor.h"
#include "TextFile.h"

/* constructor */
GrepVisitor::GrepVisitor(const string& _pattern):
  found(false),
  pattern(_pattern) {}

/* returns whether a pattern is found in the file just visited */
bool GrepVisitor::foundQ() const
{
  return found;
}

/* reset the state so that this visitor can visit another file */
void GrepVisitor::reset()
{
  found = false;
}

/* images are ignored in grep */
void GrepVisitor::visitImageFile(ImageFile*) {}

/*
 * password protected files are ignored
 */
void GrepVisitor::visitPasswordProxy(PasswordProxy*) {}

/*
 * search the text file
 */
void GrepVisitor::visitTextFile(TextFile *file)
{
  auto content = file->read();
  string str(content.begin(), content.end());
  found = str.find(pattern) != string::npos;
}

