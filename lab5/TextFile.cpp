/*
 * Define the TextFile class here
 */

#include "TextFile.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include "AbstractFileVisitor.h"
#include "ErrorCodes.h"
using namespace std;

/*
 * constructor
 */
TextFile::TextFile(string _name): name(_name){}

/*
 * copy constructor
 */
TextFile::TextFile(const TextFile& that):
  name(that.name),
  content(that.content) {}

/*
 * clone: prototype pattern
 */
AbstractFile* TextFile::clone(string new_name) const
{
  TextFile* new_file = new TextFile(*this);
  if (new_name.size()) new_file->name = new_name;
  return new_file;
}

/*
 * getters
 */
int TextFile::getSize() const
{
  return content.size();
}

string TextFile::getName() const
{
  return name;
}

int TextFile::write(vector<char> new_content) 
{
  content = new_content;
  // Anything previously in the member variable is overwritten. 
  // Write should return 0 if the write was successful. 
  // Later as we add additional file types to our program, 
  // a write may fail and will return a non zero value.
  return OK;
}

int TextFile::append(vector<char> new_content)
{
  content.insert(content.end(), new_content.begin(), new_content.end());
  return OK;
}

vector<char> TextFile::read() const
{
  return content;
}

/* double dispatch */
void TextFile::accept(AbstractFileVisitor* visitor) 
{
  visitor->visitTextFile(this);
}
