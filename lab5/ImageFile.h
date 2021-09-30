/*
 * .img files
 */
#pragma once

#include "AbstractFile.h"
#include <vector>
#include <string>
using namespace std;

/* image must contain only X and space 
   the last char in the image encoding indicates the dimension */
enum ImageContent
{
  IMG_F = 'X',
  IMG_T = ' ',
  IMG_MINLEN = 0,
  IMG_MAXLEN = 9,
};

class ImageFile : public AbstractFile
{
  string name;           /* file name */
  vector<char> content;  /* image encoding */
  char n;                /* dimension */

  ImageFile(const ImageFile&);

  public:
  explicit ImageFile(string);
  ~ImageFile() = default;
  AbstractFile* clone(string = "") const override;
  
  virtual int getDim() const;
  int getSize() const override;
  string getName() const override;
  int write(vector<char>) override;
  int append(vector<char>) override;
  vector<char> read() const override;
  void accept(AbstractFileVisitor*) override;
};

