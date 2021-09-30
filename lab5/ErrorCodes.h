/*
 * all the return values
 */

enum ErrorCode
{
  OK = 0,
  FILE_EXISTS,
  NULL_ERR,
  FILENAME_EXT_ERR,
  FILE_NOT_OPEN,
  FILE_NOT_FOUND,
  FILE_OPEN,
  PASSWORD_MISMATCH,
  COMMAND_EXISTS,
  IMAGE_NOT_APPENDABLE,
  IMAGE_DIM_ERR,
  IMAGE_CONTENT_ERR,
  CANT_OPEN_FILE,
  COMMAND_SYNTAX_ERR,
  USER_QUIT,
  __ERRORCODE_COUNT,
};

/* get a description given errno */
const char* getErrorString(int err);
