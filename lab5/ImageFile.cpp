/*
 * definition of ImageFile class here
 */

#include "ImageFile.h"
#include "ErrorCodes.h"
#include "AbstractFileVisitor.h"
#include <algorithm>
#include <iostream>

/* constructor */
ImageFile::ImageFile(string _name):
  name(_name),
  n(0) {}

/* copy constructor */
ImageFile::ImageFile(const ImageFile& that):
  name(that.name),
  content(that.content),
  n(that.n) {}

/* prototype pattern: clone */
AbstractFile* ImageFile::clone(string new_name) const
{
  ImageFile* new_file = new ImageFile(*this);
  if (new_name.size()) new_file->name = new_name;
  return new_file;
}

/* getters */
int ImageFile::getDim() const
{
  return n;
}

int ImageFile::getSize() const
{
  return content.size();
}

string ImageFile::getName() const
{
  return name;
}

/* overwrite all contents */
int ImageFile::write(vector<char> new_content)
{
  // remove the newline at the back added by catCommand
  if (new_content.back() == '\n') new_content.pop_back();

  // then the last character should be the dimension n
  n = new_content.back() - '0';
  new_content.pop_back();
  if (n < IMG_MINLEN || n > IMG_MAXLEN || n*n != (int)new_content.size()) 
    return IMAGE_DIM_ERR;

  // the image content must be either X or space
  if (any_of(new_content.begin(), new_content.end(), 
        [](char c){ return c != IMG_T && c != IMG_F; })) {
    return IMAGE_CONTENT_ERR;
  }

  content = new_content;
  return OK;
}

/* append */
int ImageFile::append(vector<char>) 
{
  return IMAGE_NOT_APPENDABLE; // image does not support append
}

vector<char> ImageFile::read() const
{
  return content;
}

void ImageFile::accept(AbstractFileVisitor* visitor) 
{
  visitor->visitImageFile(this);
}
