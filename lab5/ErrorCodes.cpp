/*
 * descriptions of all the return values
 */

#include "ErrorCodes.h"

const char *ErrorStrings[] =
{
  "OK - no error",
  "FILE_EXISTS - file already exists",
  "NULL_ERR - argument to a function is null",
  "FILENAME_EXT_ERR - filename must contain .img or .txt",
  "FILE_NOT_OPEN - file is not open",
  "FILE_NOT_FOUND - file is not found",
  "FILE_OPEN - file is open",
  "PASSWORD_MISMATCH - password mismatch",
  "COMMAND_EXISTS - command already exists",
  "IMAGE_NOT_APPENDABLE - image files does not support appending",
  "IMAGE_DIM_ERR - image dimension error\n"
    "\tthe last character of the input must be a single digit integer n\n"
    "\tindicating the image is n x n\n"
    "\tthe input must contain another n x n characters (either X or space)",
  "IMAGE_CONTENT_ERR - image contains invalid characters\n"
    "\tonly X and space are allowed",
  "CANT_OPEN_FILE - cannot open a file\n"
    "\tfile not found or file is already open",
  "COMMAND_SYNTAX_ERR",
  "USER_QUIT",
};

/* get a description given errno */
const char* getErrorString(int err)
{
  if (err < 0 || err >= __ERRORCODE_COUNT) return "INVALID_ERRNO";
  return ErrorStrings[err];
}
