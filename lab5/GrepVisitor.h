/*
 * for extra credit: grep
 * if a pattern is found in a file, 
 *   GrepVisitor will set its own found to true
 */
#include "AbstractFileVisitor.h"
#include <string>
using namespace std;

class GrepVisitor : public AbstractFileVisitor
{
  bool found;   /* whether the pattern is found in a file just visited */
  const string pattern;
public:
  GrepVisitor(const string& pattern);
  bool foundQ() const;    /* getter for found */
  void reset();           /* reset the state so that 
                             this visitor can visit another file */

  void visitImageFile(ImageFile*);
  void visitTextFile(TextFile*);
  void visitPasswordProxy(PasswordProxy*);
};
