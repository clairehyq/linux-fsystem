/*
 * utils for file extensiosn
 */

#include "FileExtensions.h"
#include "ErrorCodes.h"

/*
 * given a filename, extract the extension, and the part before extension
 * if no dot is found, returns error
 */
int splitExt(const string &str, string&name, string&ext)
{
  size_t i = str.find_last_of(".");
  if (i == string::npos) return FILENAME_EXT_ERR;
  name = str.substr(0, i);
  ext = str.substr(i+1);
  return OK;
}

/* just getting the extension
   pre condition: the filename contains a dot */
static const char INVALID[] = "INVALID";
string getExt(const string& str)
{
  string _, ext = INVALID;
  splitExt(str, _, ext);
  return ext;
}

/* get the full name of an extension */
string getExtInfo(const string& ext)
{
  if (ext == EXT_IMG) return "image";
  else if (ext == EXT_TXT) return "text";
  
  return INVALID;
}
